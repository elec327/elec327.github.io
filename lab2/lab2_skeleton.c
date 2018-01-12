/*
 * Minimum code needed to create a timer-based interrupt. The following code is
 * equivalent to (after all setup code):
 *
 * while(1){/Users/ckemere/Development/elec327.github.io/lab3/lab3_skeleton.c
 *   __delay_cycles(1000);
 *   i++;
 * }
 *
 * You should not, however, use __delay_cycles, as it locks the CPU to the cycles
 * during this time, and can't be used to compute anything else.
 *
 */

#include <msp430g2553.h>		//must include so compiler knows what each variable means

#define CLOCKWISE 1
#define COUNTERCLOCKWISE 0


/* -------------------------------------------- *
   next_led()

   Returns:
    - unsigned int - lower byte maps to Port 2 pins
        and upper byte maps to Port 1 pins.
 * -------------------------------------------- */

unsigned int next_led()
{
  static int led_value = 0x01;  // What does static mean?
  static int direction = CLOCKWISE;

  if (direction == CLOCKWISE) {
  }
  else {
  }
}


void main(void){
	WDTCTL = WDTPW + WDTHOLD;	//Stop WDT
  BCSCTL1 = CALBC1_1MHZ;    // Set range
  DCOCTL = CALDCO_1MHZ;     // Set DCO step + modulation */
  BCSCTL2 |= ;              // HINT - you probably want to divide the appropriate clock by 8 to
                            //    make it as slow as possible.


	CCTL0 = CCIE;				//Puts the timer control on CCR0
	CCR0 = 1000;				// 1000 cycles until first interrupt
	TACTL = TASSEL_2 + MC_1;	//right click and "Open Declaration" to find out about each variable
                            //(adding a specific setting applies it to that control variable)
                            // HINT - you may want to add a divider for the clock!

  P1DIR |= ;      // Refer to EAGLE cad file to set up the approriate pins
  P2DIR |= 0x01;  // This line must be changed!

  P1OUT = 0;  // Initialize all outputs to 0
  P2OUT = 0;

	__enable_interrupt();		//global interrupt enable


  unsigned int output;

  while (1) {
    __bis_SR_register(CPUOFF + GIE);
    output = next_led(direction);
    P1OUT = output && 0xFF00;  // There is an error in this line
    P2OUT = output && 0x00FF;
  }
}

#pragma vector = TIMER0_A0_VECTOR	//says that the interrupt that follows will use the "TIMER0_A0_VECTOR" interrupt
__interrupt void Timer_A(void){		//can name the actual function anything
  __bic_SR_register_on_exit(CPUOFF);
}
