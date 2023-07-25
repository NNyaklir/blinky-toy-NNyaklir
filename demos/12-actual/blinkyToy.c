#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"

#define SW1 BIT0		
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES SW1 SW2 SW3 SW4		



typedef enum{
    STATE_OFF,LED_GREEN_ON,LED_RED_ON,BOTH_LED_ON
}State;

    int greenState =0;
    int redState = 0;

    State currentState= STATE_OFF;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer

    configureClocks();
    buzzer_init();
    led_init();

    // Turn off both LEDs initially
    led_off(LED_GREEN);
    led_off(LED_RED);

    while (1) {
        

        int prevB1State = 1; // Previous state of button 1
        int prevB2State = 1; // Previous state of button 2
        int prevB3State = 1; // Previous state of button 3
        int prevB4State = 1; // Previous state of button 4

        while (1) {
        // Read the current button states
        int b1State = (P2IN & SW1) ? 1 : 0;
        int b2State = (P2IN & SW2) ? 1 : 0;
        int b3State = (P2IN & SW3) ? 1 : 0;
        int b4State = (P2IN & SW4) ? 1 : 0;

        // Check for button 1 press
        if (b1State == 0 && prevB1State == 1) {
            currentState = LED_GREEN_ON;
            led_on(LED_GREEN);
            greenState = !greenState;
            buzzer_play_for_duration(1);
        }

        // Check for button 2 press
        if (b2State == 0 && prevB2State == 1) {
            currentState = LED_RED_ON;
            led_on(LED_RED);
            redState = !redState;
            buzzer_play_for_duration(1);
        }

        // Check for button 3 press
        if (b3State == 0 && prevB3State == 1) {
            if (currentState == LED_GREEN_ON) {
                currentState = STATE_OFF;
                led_off(LED_GREEN);
            } else if (currentState == LED_RED_ON || currentState == BOTH_LED_ON) {
                currentState = LED_RED_ON;
                led_off(LED_GREEN);
            }
            buzzer_play_for_duration(1);
        }

        // Check for button 4 press
        if (b4State == 0 && prevB4State == 1) {
            if (currentState == LED_RED_ON) {
                currentState = STATE_OFF;
                led_off(LED_RED);
            } else if (currentState == LED_GREEN_ON || currentState == BOTH_LED_ON) {
                currentState = LED_GREEN_ON;
                led_off(LED_RED);
            }
            buzzer_play_for_duration(1);
        }

        // Update the previous button states
        prevB1State = b1State;
        prevB2State = b2State;
        prevB3State = b3State;
        prevB4State = b4State;

        // Add a delay to avoid button bounce issues
        __delay_cycles(200000);
        }
    }
}