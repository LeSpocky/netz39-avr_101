#include <stdbool.h>
#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*  defines */
#define DIR_RD          (1 << DDB4)
#define DIR_GN          (1 << DDB3)
#define PORT_RD         (1 << PORTB4)
#define PORT_GN         (1 << PORTB3)
#define PORT_BTN        (1 << PORTB0)
#define PIN_BTN         (1 << PINB0)

/*  globals */
uint8_t key_state;  /*  debounced and inverted key state, bit = 1: key pressed */
uint8_t key_press;  /*  key press detect    */

/*  declaration */
void init( void );

/*  ISR     */
ISR(TIMER1_OVF_vect) {
    static uint8_t  ct0, ct1;
    uint8_t         i;

    /*  TODO    make a 10ms timer instead of this one   */

    i = key_state ^ ~PINB;      /*  key changed             */
    ct0 = ~( ct0 & i );         /*  reset or count ct0      */
    ct1 = ct0 ^ (ct1 & i);      /*  reset or count ct1      */
    i &= ct0 & ct1;             /*  count until roll over   */
    key_state ^= i;             /*  toggle debounced state  */
    key_press |= key_state & i; /*  0→1: key press detect   */
}

/*  main    */
int main ( void ) {
    uint8_t key_mask, state = 0;

    init();

    /*  main loop   */
    while ( 1 ) {
        key_mask = PIN_BTN;
        cli();
        key_mask &= key_press;   /*  read key(s)     */
        key_press ^= key_mask;   /*  clear key(s)    */
        sei();

        if ( key_mask ) {
            switch ( state ) {
            case 0:
                /*  out -> red  */
                PORTB = PORT_BTN | PORT_RD;
                state = 1;
                break;
            case 1:
                /*  red -> green    */
                PORTB = PORT_BTN | PORT_GN;
                state = 2;
                break;
            case 2:
                /*  green -> off    */
                PORTB = PORT_BTN;
                state = 0;
                break;
            default:
                state = 0;
                break;
            }
        }
    }

    return 0;
}

/*  initialization  */
void init( void ) {
    /*  disable interrupts  */
    cli();

    /*  set port pins to output and value 0, all other are inputs then,
     *  set pull-up on button input */
    MCUCR &= ~PUD;
    DDRB = DIR_RD | DIR_GN;
    PORTB = 0;
    PORTB |= PORT_BTN;

    /*  timer init  */
    TIFR &= ~(1 << TOV1);   /*  clear timer1 overflow interrupt flag    */
    TIMSK |= (1 << TOIE1);  /*  enable timer1 overflow interrupt        */

    /*  start timer1 by setting CS1 bits in timer1 control register to
     *  clk_I/O devided by 256. for 8 MHz internal oscillator
     *  the timer overflow comes every 256*256 cycles aka 8ms. */
    TCCR1 = (TCCR1 & 0xF0) | (0x09 & 0x0F);

    sei();
}
