#include <msp430.h>

int main(void)
{

  BCSCTL3 |= LFXT1S_2;                    // ACLK = VLO
//  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  WDTCTL = WDT_ADLY_1_9;               // Stop WDT
  IE1 |= WDTIE;                             // Enable WDT interrupt

  TA1CTL = TASSEL_1 + MC_1;// ACLK, upmode
  TA1CCR0 = 50;            // Set PWM frequency ~12 kHz / 20
  TA1CCR1 = 0;             // Count to 40
  TA1CCTL1 = OUTMOD_3;     // Set PWM mode

  P2DIR = 0x02;
  P2SEL = 0x02;

  while(1)
  {
    TA1CCR1++;
    if (TA1CCR1 == 50)
        TA1CCR1 = 0;
    __bis_SR_register(LPM3_bits + GIE);     // Enter LPM3
  }
}


#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(WDT_VECTOR))) watchdog_timer (void)
#else
#error Compiler not supported!
#endif
{
  __bic_SR_register_on_exit(LPM3_bits);     // Clear LPM3 bits from 0(SR)
}

