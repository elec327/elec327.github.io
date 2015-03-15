---
title: Lab 6
layout: default
group: labs-navigation
description: Software Debouncing and the Simon PCB
---

{::options parse_block_html="true" /}

## Lab #6: Software Debouncing and the Simon PCB

#### Part 1: The Simon PCB

The game ["Simon"](https://en.wikipedia.org/wiki/Simon_(game)) is a classic toy which tests the
working memory of the player. In this lab, you will design the PCB for your implementation of
Simon and work on the code to process button presses. 

Parts:
- 4 buttons with 1206 capacitors in parallel
- 4 APA102 SPI RGB LEDs (probably either in a row or in a circle)
- Power switch
- AAA battery pack
- Piezo buzzer (wired up for PWM - see Part 2)

#### Part 2: Playing tones via PWM

Wire a piezo buzzer between to 2 PWM-capable pins. By connecting the device in this manner and
enabling one or both channels, the volume of the sound can be changed. Write code that plays a
standard 8-note octave scale (or different pattern if you choose) starting from middle C (see
[Wikipedia table](https://en.wikipedia.org/wiki/Scientific_pitch_notation)). Each note should
be played for 1 second. The scale should then repeat. Every other scale should be a higher
volume. Here is some sample code to get you going:

<code>
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

  P1OUT = 0;
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

</code>

#### Part 3: Software Debouncing

Two buttons which must be pressed in the pattern 1, 2, 1, 1, 2, 2. The LED should get
progressively brighter and the tone progressively higher frequency as pattern is entered faster
and faster. If pattern is entered incorrectly, LED should go off. Reset by holding both buttons
simultaneously for 2 s, which causes LED to flash.

**Save this code as `debounce.c`. Create a demo video that shows you playing and then resetting
and playing again. Upload your answered questions, code and the video URL to owlspace.**


