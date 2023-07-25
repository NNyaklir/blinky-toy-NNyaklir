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
        int b1STATE = (P2IN & SW1) ? 1 : 0;
        int b2STATE = (P2IN & SW2) ? 1 : 0;
        int b3STATE = (P2IN & SW3) ? 1 : 0;
        int b4STATE = (P2IN & SW4) ? 1 : 0;

        switch (currentState) {
            case STATE_OFF:
                if (b1STATE) {
                    currentState = LED_GREEN_ON;
                    led_on(LED_GREEN);
                    greenState = !greenState;
                    buzzer_play_for_duration(5);
                } else if (b2STATE) {
                    currentState = LED_RED_ON;
                    led_on(LED_RED);
                    redState = !redState;
                    buzzer_play_for_duration(5);
                }
                break;
            case LED_GREEN_ON:
                if (b3STATE) {
                    currentState = STATE_OFF;
                    led_off(LED_GREEN);
                    buzzer_play_for_duration(5);
                } else if (b2STATE) {
                    currentState = BOTH_LED_ON;
                    led_on(LED_RED);
                    redState = !redState;
                    buzzer_play_for_duration(5);
                }
                break;
            case LED_RED_ON:
                if (b1STATE) {
                    currentState = BOTH_LED_ON;
                    led_on(LED_GREEN);
                    greenState = !greenState;
                    buzzer_play_for_duration(5);
                }
                if (b4STATE) {
                    currentState = STATE_OFF;
                    led_off(LED_RED);
                    buzzer_play_for_duration(5);
                }
                break;
            case BOTH_LED_ON:
                if (b3STATE) {
                    currentState = LED_RED_ON;
                    led_off(LED_GREEN);
                    buzzer_play_for_duration(5);
                } else if (b4STATE) {
                    currentState = LED_GREEN_ON;
                    led_off(LED_RED);
                    buzzer_play_for_duration(5);
                }
                break;
        }

        // Add a delay to avoid button bounce issues
        __delay_cycles(200000);
    }

    return 0;
}