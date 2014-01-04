#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

/*  defines */
#define PORT_RD     (1 << PORTB3)
#define PORT_GN     (1 << PORTB1)
#define PORT_BL     (1 << PORTB4)
#define PORT_MASK   (PORT_RD | PORT_GN | PORT_BL);

/*  main    */
int main (void) {
    uint8_t pwm_count = 0, pwm_should = 0, pwm_phase = 0;

    /*  set port pins to output and value 0 */
    DDRB = (1 << DDB3) | (1 << DDB1) | (1 << DDB4);
    PORTB = 0;

    while ( 1 ) {
        /*  turn off    */
        if ( pwm_should == pwm_phase ) {
            PORTB &= ~PORT_RD;
        }

        /*  turn on on overflow */
        pwm_phase++;
        if ( pwm_phase == 0 ) {
            PORTB |= PORT_RD;

            pwm_count++;
            if ( pwm_count == 0 ) {
                pwm_should++;
            }
        }
    }

    return 0;
}
