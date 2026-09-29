/**
 * @file main.c
 * @brief Day 04 Bare-Metal AVR C Firmware (Custom Wokwi Wiring).
 * @details Controls Green LED (PB5/Pin 13), Red LED (PB2/Pin 10), and Pushbutton (PB4/Pin 12)
 *          using raw ATmega328P Port Registers and Read-Modify-Write bitwise macros.
 * @author Mahfujur Rahman Talha
 */

#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz Clock Speed for Arduino Uno ATmega328P
#endif

#include <avr/io.h>
#include <util/delay.h>

// Bit Manipulation Macros
#define BIT(n)               (1UL << (n))
#define SET_BIT(reg, bit)    ((reg) |= BIT(bit))
#define CLEAR_BIT(reg, bit)  ((reg) &= ~BIT(bit))
#define TOGGLE_BIT(reg, bit) ((reg) ^= BIT(bit))
#define READ_BIT(reg, bit)   (((reg) >> (bit)) & 1U)

int main(void) {
    
    // 1. Configure Pin Directions via DDRB
    SET_BIT(DDRB, PB5);   // Set PB5 (Pin 13) as Output -> Green LED
    SET_BIT(DDRB, PB2);   // Set PB2 (Pin 10) as Output -> Red LED
    CLEAR_BIT(DDRB, PB4); // Set PB4 (Pin 12) as Input  -> Pushbutton

    // 2. Enable Internal Pull-Up Resistor on PB4
    SET_BIT(PORTB, PB4);  // Enable internal 20k pull-up resistor on Pin 12

    while (1) {
        // 3. Read Input Pin State on PB4 (Active-LOW Pushbutton)
        if (READ_BIT(PINB, PB4) == 0) {
            // Button Pressed: Turn ON Red LED (PB2), Turn OFF Green LED (PB5)
            SET_BIT(PORTB, PB2);
            CLEAR_BIT(PORTB, PB5);
        } else {
            // Button Released: Turn OFF Red LED (PB2), Toggle Green LED (PB5) every 500ms
            CLEAR_BIT(PORTB, PB2);
            TOGGLE_BIT(PORTB, PB5);
            _delay_ms(500);
        }
    }

    return 0;
}
