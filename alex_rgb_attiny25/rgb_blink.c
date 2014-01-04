#include <avr/io.h>
#include <util/delay.h>

#define WAIT_MS 500

int main (void) {
    int t = 0;

    DDRB = (1 << DDB3) | (1 << DDB1) | (1 << DDB4);
    // DDRB = (1 << DDB1) | (1 << DDB2) | (1 << DDB0);
    PORTB = 0;

    while ( 1 ) {
        PORTB = (unsigned char) t++ &
            ( (1<<PORTB1) | (1<<PORTB3) | (1<<PORTB4) );
        _delay_ms( WAIT_MS );
    }
    // PORTB = (1 << PORTB3) | (1 << PORTB1) | (1 << PORTB4);
    // PORTB = (1 << PORTB3);
    // PORTB = (1 << PORTB1);
    // PORTB = 0xFF;
    // PORTB = ~(1 << PORTB0);

    return 0;
}
