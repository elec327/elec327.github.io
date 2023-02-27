#include <msp430.h> 
#include <stdint.h>
#include <stdbool.h>
#include "rgb_interface.h"

/**
 * main.c
 */

void init_wdt(void){
    BCSCTL3 |= LFXT1S_2;     // ACLK = VLO
    WDTCTL = WDT_ADLY_250;    // WDT 16ms (~43.3ms since clk 12khz), ACLK, interval timer
    IE1 |= WDTIE;            // Enable WDT interrupt
}

uint8_t blue[] = {0xF0, 10, 0, 0};
uint8_t green[] = {0xF0, 0, 10, 0};
uint8_t red[] = {0xF0, 0, 0, 10};
uint8_t yellow[] = {0xF0, 0, 10, 10};
uint8_t off[] = {0xE0, 0, 0, 0};

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	init_wdt();
	rgb_init_spi();

	_enable_interrupts();

	while (1) {
        rgb_send_start();
        rgb_send_frame(&blue, false);
        rgb_send_frame(&green, false);
        rgb_send_frame(&red, false);
        rgb_send_frame(&yellow, false);
        rgb_send_end();
        LPM3;
        rgb_send_start();
        rgb_send_frame(&off, false);
        rgb_send_frame(&off, false);
        rgb_send_frame(&off, false);
        rgb_send_frame(&off, false);
        rgb_send_end();
        LPM3;
	}

	return 0;
}

// Watchdog Timer interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(WDT_VECTOR))) watchdog_timer (void)
#else
#error Compiler not supported!
#endif
{
    __bic_SR_register_on_exit(LPM3_bits); // exit LPM3 when returning to program (clear LPM3 bits)
}
