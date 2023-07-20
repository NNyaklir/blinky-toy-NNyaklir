#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "led.c"

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

void main(void){
    configureClocks();
    
    
    // Set button pins as inputs with pull-up resistors enabled
    P2DIR &= ~(SW1|SW2|SW3|SW4);
    P2REN |= SW1|SW2|SW3|SW4;
    P2OUT |= SW1|SW2|SW3|SW4;

    P1DIR |= LED_GREEN | LED_RED;  //led pins as out puts
    P1OUT &= ~LEDS; //LEDs initially off

    while(1){

        int b1STATE =(P2IN & SW1) ? 1 : 0;
        int b2STATE =(P2IN & SW2) ? 1 : 0;
        int b3STATE =(P2IN & SW3) ? 1 : 0;
        int b4STATE =(P2IN & SW4) ? 1 : 0;


        //@TODO implement buzzer to make noise when button is pressed
        switch (currentState){
            case STATE_OFF:
                P1OUT &= ~LEDS;
                greenState=0;
                redState=0;
                if(b1STATE){
                    currentState=LED_GREEN_ON;  
                }
                else if(b2STATE){
                    currentState=LED_RED_ON;
                    
                }
                break;
            case LED_GREEN_ON:
                greenState =1;
                P1OUT ^= BIT6;
                redState=0;
                P1OUT &= ~BIT0;
                if(b3STATE){
                    currentState=STATE_OFF;
                    
                }
                else if(b2STATE){
                    currentState=BOTH_LED_ON;
                    
                }
                break;
            case LED_RED_ON:
                redState=1;
                P1OUT ^=Bit0;
                greenState=0;
                P1OUT &= ~BIT6;
                if(b1STATE){
                    currentState=BOTH_LED_ON;
                   
                    greenState= !greenState;
                }
                if(b4STATE){
                    currentState=STATE_OFF;
                    
                }
                break;
            case BOTH_LED_ON:
                P1OUT ^= LEDS;
                if(b3STATE){
                    currentState=LED_RED_ON;
                    
                }
                else if(b4STATE){
                    currentState=LED_GREEN_ON;
                    
                }
                break;
        }
    }
}