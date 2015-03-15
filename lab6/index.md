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

<p class="text-success">
*While you don't need to turn in the code for this part, I still recommend you do it! The sample
uses the TimerA1 module for PWM and the watchdog timer as a "tick" generator, which is probably
a good framework.*
</p>

Before implementing the full code for this lab, you should start by getting the sound aspect
set up. Wire a piezo buzzer between to 2 PWM-capable pins. By connecting the device in this
manner and enabling one or both channels, the volume of the sound can be changed. Write code
that plays a standard 8-note octave scale (or different pattern if you choose) starting from
middle C (see [Wikipedia table](https://en.wikipedia.org/wiki/Scientific_pitch_notation)). Each
note should be played for 1 second. The scale should then repeat. Every other scale should be a
higher volume. Sample code to get you going is in [piezo_sample.c](lab6/piezosample.c).


#### Part 3: Software Debouncing

For the full Two buttons which must be pressed in the pattern 1, 2, 1, 1, 2, 2. The LED should get
progressively brighter and the tone progressively higher frequency as pattern is entered faster
and faster. If pattern is entered incorrectly, LED should go off. Reset by holding both buttons
simultaneously for 2 s, which causes LED to flash.

**Save this code as `debounce.c`. Create a demo video that shows you playing and then resetting
and playing again. Upload your answered questions, code and the video URL to owlspace.**


