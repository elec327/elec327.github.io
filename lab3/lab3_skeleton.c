#include <msp430.h>

int main(void)
{
  int col = 0;
  int row = 0;
  int i;

  BCSCTL3 |= LFXT1S_2;                    // ACLK = VLO
  WDTCTL = WDTPW + WDTHOLD;               // Stop WDT
  TACTL = TASSEL_1 + MC_1;                // ACLK, upmode
  CCR0 = 1000;                            // Interrupt should happen every ~12 kHz / 1000
  CCTL0 = CCIE;                           // CCR0 interrupt enabled

  // Rows are P1.0 through P1.6
  // Columns are P2.0 through p2.4

  P1DIR = 0x7F;                          // Set rows as output
  P2DIR = 0x1F;                          // Set columns as output

  // Based on schematic, to light up, a column has to be high (1) and a row low (0).
  P1OUT = 0;                             // Default rows to on (low)
  P2OUT = 0;                             // Default columns to off (low)

  while(1)
  {
    col = 0x01; // start with the first column
    for (i = 0; i < 5; i++) {
        P2OUT = col;
        //P1OUT = row; // row = 0 -> all rows on
        P1OUT = ~col; // fun effect
        col = col << 1; // move to the next column
        __bis_SR_register(LPM3_bits + GIE);     // Enter LPM3
    }
  }
}

// Timer A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
  __bic_SR_register_on_exit(LPM3_bits);
}
