/*
   ELEC327 Lab 6 Buzzer Example Code.
   Drive a piezo buzzer connected between Pins 2.1 and 2.5.
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

  P2DIR |= BIT5 + BIT1; // We need 2.5 and 2.1 connected!
  P2SEL |= BIT5; // P2.5 is TA1.2 PWM output
  P2OUT = 0; // Set 2.1 to GND

  TA1CCR0 = periods[which_period];
  TA1CCR2 = periods[which_period]>>2; // divde by 2
  TA1CCTL2 = OUTMOD_6;
  TA1CTL = TASSEL_2 + MC_1; // SMCLK, upmode

  WDTCTL = WDT_ADLY_250;  // Set Watchdog Timer to ~3 s with VLO
  IE1 |= WDTIE;
  __bis_SR_register(CPUOFF + GIE);
}

#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  which_period = (which_period + 1) % 4;
  TA1CCR2 = periods[which_period]>>2;
  TA1CCR0 = periods[which_period];
}
