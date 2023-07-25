#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles; 
  CCR1 = cycles >> 1;		/* one half cycle */
}

void buzzer_play_for_duration(unsigned int duration_ms) {
    // Calculate the number of cycles required for the given duration
    unsigned int cycles = duration_ms * 2; // Assuming buzzer clock = 2MHz

    // Set the buzzer to the desired frequency for the specified duration
    buzzer_set_period(cycles);

    // Wait for the specified duration
    __delay_cycles(duration_ms * 2000); // Delay for duration_ms milliseconds

    // Turn off the buzzer after the specified duration
    buzzer_set_period(0);
}


    
    
  

