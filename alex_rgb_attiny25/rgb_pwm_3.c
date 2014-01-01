#include <stdbool.h>
#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "gamma.h"

/*  defines */
#ifdef STARTERKIT
#define DIR_RD          (1 << DDB3)
#define DIR_GN          (1 << DDB1)
#define DIR_BL          (1 << DDB4)
#define PORT_RD         (1 << PORTB3)
#define PORT_GN         (1 << PORTB1)
#define PORT_BL         (1 << PORTB4)
#define INVERTED_LED    false
#define SET_MUX         0x01
#endif

#ifdef BREADBOARD_BIG
#define DIR_RD          (1 << DDB0)
#define DIR_GN          (1 << DDB1)
#define DIR_BL          (1 << DDB2)
#define PORT_RD         (1 << PORTB0)
#define PORT_GN         (1 << PORTB1)
#define PORT_BL         (1 << PORTB2)
#define INVERTED_LED    true
#define SET_MUX         0x03
#endif

#ifdef REFLOW_LITE
#define DIR_RD          (1 << DDB0)
#define DIR_GN          (1 << DDB1)
#define DIR_BL          (1 << DDB2)
#define PORT_RD         (1 << PORTB0)
#define PORT_GN         (1 << PORTB1)
#define PORT_BL         (1 << PORTB2)
#define INVERTED_LED    false
#define SET_MUX         0x03
#endif

#ifndef INVERTED_LED
#error "set some target"
#endif

#define PORT_MASK       (PORT_RD | PORT_GN | PORT_BL)

#define MASK_ADPS       0x07    /*  ADPS2:ADPS0 in ADCSRA           */
#define MASK_ADTS       0x07    /*  ADTS2:ADTS0 in ADCSRB           */
#define MASK_REFS       0xD0    /*  REFS1,REFS0 and REFS2 in ADMUX  */
#define MASK_MUX        0x0F    /*  MUX3:MUX0 in ADMUX              */

/*  globals */
volatile uint8_t adc_result;
volatile uint8_t comp_buf_R, comp_buf_G, comp_buf_B;

/*  declaration */
void init( void );

/*  ISR     */
ISR(ADC_vect) {
    adc_result = ADCH;
}

ISR(TIMER0_OVF_vect) {
    static uint8_t  pin_level = ( INVERTED_LED ? 0 : PORT_MASK );
    static uint8_t  led_status = 0;
    static uint8_t  comp_R, comp_G, comp_B;
    static uint8_t  soft_cnt_R = 0xFF;
    static uint8_t  soft_cnt_G = 0xFF - 85;
    static uint8_t  soft_cnt_B = 0xFF - 170;

    /*  set new pin level first for low jitter and do calculation
     *  afterwards  */
    PORTB = pin_level;

    /*  increment counter and if overflow update compare value from
     *  main loop buffer and set LED on */
    if ( ++soft_cnt_R == 0 ) {
        comp_R = comp_buf_R;
        led_status |= PORT_RD;
    }
    if ( ++soft_cnt_G == 0 ) {
        comp_G = comp_buf_G;
        led_status |= PORT_GN;
    }
    if ( ++soft_cnt_B == 0 ) {
        comp_B = comp_buf_B;
        led_status |= PORT_BL;
    }

    /*  on compare match set LED off (written to port on next
     *  interrupt)  */
    if ( comp_R == soft_cnt_R ) {
        led_status &= ~PORT_RD;
    }
    if ( comp_G == soft_cnt_G ) {
        led_status &= ~PORT_GN;
    }
    if ( comp_B == soft_cnt_B ) {
        led_status &= ~PORT_BL;
    }

    pin_level = ( INVERTED_LED ? ~led_status : led_status ) & PORT_MASK;
}

/*  main    */
int main (void) {
    init();

    /*  main loop   */
    while ( 1 ) {
        comp_buf_R = pgm_read_word( &(gammatbl[adc_result]) );
        comp_buf_G = pgm_read_word( &(gammatbl[adc_result]) );
        comp_buf_B = pgm_read_word( &(gammatbl[adc_result]) );
    }

    return 0;
}

/*  implementation  */
void init( void ) {
    /*  start values for PWM    */
    comp_buf_R = 10;
    comp_buf_G = 80;
    comp_buf_B = 170;

    /*  disable interrupts and ADC  */
    cli();
    ADCSRA &= ~(1 << ADEN);
    PRR &= ~(1 << PRADC);   /*  disable power reduction for ADC after
                                disabling ADC itself    */

    /*  set clock   */
    CLKPR = (1 << CLKPCE);  /*  enable clock prescaler update       */
    CLKPR = 0;              /*  set clock to maximum                */

    /*  set port pins to output and value 0 */
    DDRB = DIR_RD | DIR_GN | DIR_BL;
    PORTB = 0;

    /*  timer init  */
    TIFR &= ~(1 << TOV0);   /*  clear timer0 overflow interrupt flag    */
    TIMSK |= (1 << TOIE0);  /*  enable timer0 overflow interrupt        */

    /*  start timer0 by setting last 3 bits in timer0 control register B
     *  to any clock source */
    TCCR0B = (TCCR0B & 0xF8) | (0x01 & 0x07);

    /*  use VCC as voltage reference (disconnected from PB0/AREF)   */
    ADMUX = (ADMUX & ~MASK_REFS) | 0;   /*  REFS2:REFS0 all cleared */

    /*  put conversion result left bounded in ADCH/ADCL, so we only need
     *  to fetch ADCH for an 8-bit result   */
    ADMUX |= (1 << ADLAR);

    /*  set which ADC pin is used   */
    ADMUX = (ADMUX & ~MASK_MUX) | (SET_MUX & MASK_MUX);

    /*  set prescaler in a way the ADC clock gets between 50khZ and
     *  200 kHz. using a prescaler of 128 here yields a value in this
     *  interval for both 8MHz and 16MHz clock. */
    /*  TODO    check this for default 1 MHz or make dependent on cpu
     *          clock speed!    */
    ADCSRA = (ADCSRA & ~MASK_ADPS) | (0x07 & MASK_ADPS);

    /*  use ADC free running mode   */
    ADCSRA |= (1 << ADATE);
    ADCSRB = (ADCSRB & ~MASK_ADTS) | 0; /*  ADTS2:ADTS0 all cleared */

    /*  enable interrupts and ADC   */
    ADCSRA |= (1 << ADEN);
    ADCSRA |= (1 << ADIE);
    sei();

    /*  start ADC conversion    */
    ADCSRA |= (1 << ADSC);
}
