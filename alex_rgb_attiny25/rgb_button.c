#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*  defines */
#ifdef STARTERKIT
#define DIR_RD          (1 << DDB3)
#define DIR_GN          (1 << DDB1)
#define DIR_BL          (1 << DDB4)
#define PORT_RD         (1 << PORTB3)
#define PORT_GN         (1 << PORTB1)
#define PORT_BL         (1 << PORTB4)
#define PORT_BTN        (1 << PORTB0)
#define PIN_BTN         (1 << PINB0)
#define INVERTED_LED    false
#endif

#ifdef BREADBOARD_BIG
#define DIR_RD          (1 << DDB0)
#define DIR_GN          (1 << DDB1)
#define DIR_BL          (1 << DDB2)
#define PORT_RD         (1 << PORTB0)
#define PORT_GN         (1 << PORTB1)
#define PORT_BL         (1 << PORTB2)
#define INVERTED_LED    true
#endif

#ifdef REFLOW_LITE
#define DIR_RD          (1 << DDB0)
#define DIR_GN          (1 << DDB1)
#define DIR_BL          (1 << DDB2)
#define PORT_RD         (1 << PORTB0)
#define PORT_GN         (1 << PORTB1)
#define PORT_BL         (1 << PORTB2)
#define INVERTED_LED    false
#endif

#ifndef INVERTED_LED
#error "set some target"
#endif

#define PORT_MASK       (PORT_RD | PORT_GN | PORT_BL)

/*  constants   */
const unsigned char pwmtable[32] = {
    0, 1, 2, 2, 2, 3, 3, 4, 5, 6, 7, 8, 10, 11, 13, 16, 19, 23, 27, 32,
    38, 45, 54, 64, 76, 91, 108, 128, 152, 181, 215, 255
};

/*  globals */
volatile unsigned char  comp_buf_R, comp_buf_G, comp_buf_B;
unsigned char           key_state;  /*  debounced and inverted key
                                        state, bit = 1: key pressed */
unsigned char           key_press;  /*  key press detect    */

/*  declaration */
void init( void );

/*  ISR     */
ISR(TIMER0_OVF_vect) {
    static unsigned char    ct0, ct1;
    unsigned char           i;

    /*  TODO    make a 10ms timer instead of this one   */

    i = key_state ^ ~PINB;      /*  key changed             */
    ct0 = ~( ct0 & i );         /*  reset or count ct0      */
    ct1 = ct0 ^ (ct1 & i);      /*  reset or count ct1      */
    i &= ct0 & ct1;             /*  count until roll over   */
    key_state ^= i;             /*  toggle debounced state  */
    key_press |= key_state & i; /*  0→1: key press detect   */
}

/*  main    */
int main (void) {
    unsigned char color = 0, key_mask, led;

    init();

    /*  main loop   */
    while ( 1 ) {
        key_mask = PIN_BTN;
        cli();
        key_mask &= key_press;   /*  read key(s)     */
        key_press ^= key_mask;   /*  clear key(s)    */
        sei();
        if ( key_mask ) {
            /*  two statements because ++color and & have same precence */
            color++;
            color &= 0x07;

            led = 0;
            if ( color & 0x01 ) {
                led |= PORT_RD;
            }
            if ( color & 0x02 ) {
                led |= PORT_GN;
            }
            if ( color & 0x04 ) {
                led |= PORT_BL;
            }
            PORTB = ( INVERTED_LED ? ~led : led ) & PORT_MASK;
        }
    }

    return 0;
}

/*  initialization  */
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

    /*  set port pins to output and value 0, all other are inputs then,
     *  set pull-up on button input */
    DDRB = DIR_RD | DIR_GN | DIR_BL;
    PORTB = 0;
    MCUCR |= PUD;
    PORTB |= PORT_BTN;

    /*  timer init  */
    TIFR &= ~(1 << TOV0);   /*  clear timer0 overflow interrupt flag    */
    TIMSK |= (1 << TOIE0);  /*  enable timer0 overflow interrupt        */

    /*  start timer0 by setting last 3 bits in timer0 control register B
     *  to any clock source */
    TCCR0B = (TCCR0B & 0xF8) | (0x01 & 0x07);

    sei();
}
