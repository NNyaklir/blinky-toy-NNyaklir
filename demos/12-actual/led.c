#include <msp430.h>
#include "led.h"


// LED pin assignments
#define LED_GREEN BIT6
#define LED_RED BIT0

// Function to initialize the LEDs
void led_init() {
    // Set LED pins as outputs
    P1DIR |= LED_GREEN | LED_RED;

    // Turn off both LEDs initially
    led_off(LED_GREEN);
    led_off(LED_RED);
}

// Function to turn on the LED
void led_on(unsigned int led) {
    P1OUT |= led;
}

// Function to turn off the LED
void led_off(unsigned int led) {
    P1OUT &= ~led;
}

// Function to toggle the LED state
void led_toggle(unsigned int led) {
    P1OUT ^= led;
}
