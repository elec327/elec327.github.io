#include <msp430.h>
#define CNT R4
				.section .text,"ax",@progbits
_start:
				mov.w   #WDTPW|WDTHOLD,&WDTCTL
				bis.b   #0x01, &P1DIR

outerloop:
				mov.w   #50000,CNT
innerloop:
				dec.w   CNT
				cmp     #0, CNT
				jnz     innerloop
				xor.w   #0x01, &P1OUT
				jmp     outerloop

				.section ".resetvec","ax",@progbits
				.word _start            ;0xfffe (RESET_VECTOR)

				.end
