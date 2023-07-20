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

    State currentState= STATE_OFF;

void main(void){
    configureClocks();
    
    
    // Set button pins as inputs with pull-up resistors enabled
    P2DIR &=~(SW1|SW2|SW3|SW4);
    P2REN = (SW1|SW2|SW3|SW4);
    P2OUT = (SW1|SW2|SW3|SW4);

    P1DIR |= LED_GREEN | LED_RED;  //led pins as out puts

    while(1){

        int b1STATE =(BIT3 & SW1) ? 1 : 0;
        int b2STATE =(BIT4 & SW2) ? 1 : 0;
        int b3STATE =(BIT5 & SW3) ? 1 : 0;
        int b4STATE =(BIT6 & SW4) ? 1 : 0;


        //@TODO implement buzzer to make noise when button is pressed
        switch (currentState){
            case STATE_OFF:
                if(b1STATE){
                    currentState=LED_GREEN_ON;  
                    P1OUT |= BIT6;
                }
                else if(b2STATE){
                    currentState=LED_RED_ON;
                    P1OUT |= BIT0;
                }
                break;
            case LED_GREEN_ON:
                if(b3STATE){
                    currentState=STATE_OFF;
                    P1OUT &= ~BIT6;
                }
                else if(b2STATE){
                    currentState=BOTH_LED_ON;
                    P1OUT |= BIT0;
                }
                break;
            case LED_RED_ON:
                if(b1STATE){
                    currentState=BOTH_LED_ON;
                    P1OUT |= BIT6;
                }
                if(b4STATE){
                    currentState=STATE_OFF;
                    P1OUT &=  ~BIT0;
                }
                break;
            case BOTH_LED_ON:
                if(b3STATE){
                    currentState=LED_RED_ON;
                    P1OUT &= ~BIT6;
                }
                else if(b4STATE){
                    currentState=LED_GREEN_ON;
                    P1OUT &= ~BIT0;
                }
                break;
        }
    }
}