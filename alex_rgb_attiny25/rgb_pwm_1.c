#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*  defines */
#define PORT_RD     (1 << PORTB3)
#define PORT_GN     (1 << PORTB1)
#define PORT_BL     (1 << PORTB4)
#define PORT_MASK   (PORT_RD | PORT_GN | PORT_BL);

/*  globals */
volatile unsigned char comp_buf_R, comp_buf_G, comp_buf_B;

/*  declaration */
void init( void );

/*  ISR     */
ISR(TIMER0_OVF_vect) {
    static unsigned char    pin_level = PORT_MASK;
    static unsigned char    comp_R, comp_G, comp_B;
    static unsigned char    soft_cnt_R = 0xFF;
    static unsigned char    soft_cnt_G = 0xFF - 85;
    static unsigned char    soft_cnt_B = 0xFF - 170;

    /*  set new pin level first for low jitter and do calculation
     *  afterwards  */
    PORTB = pin_level;

    /*  increment counter and if overflow update compare value from
     *  main loop buffer    */
    if ( ++soft_cnt_R == 0 ) {
        comp_R = comp_buf_R;
        pin_level |= PORT_RD;
    }
    if ( ++soft_cnt_G == 0 ) {
        comp_G = comp_buf_G;
        pin_level |= PORT_GN;
    }
    if ( ++soft_cnt_B == 0 ) {
        comp_B = comp_buf_B;
        pin_level |= PORT_BL;
    }

    /*  on compare match clear pin level (written to port on next
     *  interrupt   */
    if ( comp_R == soft_cnt_R ) {
        pin_level &= ~PORT_RD;
    }
    if ( comp_G == soft_cnt_G ) {
        pin_level &= ~PORT_GN;
    }
    if ( comp_B == soft_cnt_B ) {
        pin_level &= ~PORT_BL;
    }
}

/*  main    */
int main (void) {
    int i;

    init();

    /*  main loop   */
    while ( 1 ) {
        for ( i = 0; i < 3; i++ ) {
            comp_buf_R++;
            comp_buf_G++;
            comp_buf_B++;
        }
        _delay_ms( 100 );
    }

    return 0;
}

/*  implementation  */
void init( void ) {
    /*  start values    */
    comp_buf_R = 10;
    comp_buf_G = 80;
    comp_buf_B = 170;

    /*  disable interrupts  */
    cli();

    /*  set clock   */
    CLKPR = (1 << CLKPCE);  /*  enable clock prescaler update       */
    CLKPR = 0;              /*  set clock to maximum                */

    /*  set port pins to output and value 0 */
    DDRB = (1 << DDB0) | (1 << DDB1) | (1 << DDB2);
    PORTB = 0;

    /*  timer init  */
    TIFR &= ~(1 << TOV0);   /*  clear timer0 overflow interrupt flag    */
    TIMSK |= (1 << TOIE0);  /*  enable timer0 overflow interrupt        */

    /*  start timer0 by setting last 3 bits in timer0 control register B
     *  to any clock source */
    TCCR0B = (TCCR0B & 0xF8) | (0x01 & 0x07);

    sei();
}
