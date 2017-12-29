/* 
   ELEC327 Lab 6 Buzzer Example Code.
   Drive a piezo buzzer connected between ground and Pin 1.2.
   Plays a major C chord.
*/

#include "msp430g2553.h"

// Notes for a major C chord
int periods[] = {1000000/261.63, 
   1000000/329.63,
   1000000/392.00,
   1000000/523.5};
int which_period = 0;

void main(void){
  WDTCTL = WDTPW + WDTHOLD; // Stop WDT

  if (CALBC1_1MHZ == 0xFF || CALDCO_1MHZ == 0xff)
    while(1); // Erased calibration data? Trap!

  BCSCTL1 = CALBC1_1MHZ; // Set the DCO to 1 MHz
  DCOCTL = CALDCO_1MHZ; // And load calibration data

  P1DIR |= BIT2; //
  P1SEL |= BIT2; // BIT2 is TA0.1 PWM output  

  CCR0 = periods[which_period];
  CCR1 = periods[which_period]>>2; // divde by 2
  CCTL1 = OUTMOD_6;
  TACTL = TASSEL_2 + MC_1; // SMCLK, upmode

  WDTCTL = WDT_ADLY_250;  // Set Watchdog Timer to ~3 s with VLO
  IE1 |= WDTIE;
  __bis_SR_register(CPUOFF + GIE);
}

#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  which_period = (which_period + 1) % 4;
  CCR1 = periods[which_period]>>2;
  CCR0 = periods[which_period];
}
