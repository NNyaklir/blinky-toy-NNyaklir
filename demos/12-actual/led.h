#ifndef led_included
#define  led_included

#include <msp430.h>

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)


// Function prototypes
void led_init();
void led_on(unsigned int led);
void led_off(unsigned int led);
void led_toggle(unsigned int led);


#endif
