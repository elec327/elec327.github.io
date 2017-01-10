---
title: Lab 7
layout: default
group: labs-navigation
description: Software Debouncing
---

{::options parse_block_html="true" /}

## [NOT FINAL] Lab #7: Software Debouncing and the Simon PCB

<div class="alert alert-info" role="alert">
#### **There are three goals for this lab:**
  - To understand the effects of combining two PWM channels in one device.
  - To understand and implement software debouncing.
  
</div>

<div class="alert alert-danger" role="alert">
#### **What should you turn in?**

  1. Turn in your code as `debounce.c` and answered questions.
  2. Create a demo video that shows you playing and then resetting and playing again.

</div>

#### Part 1: Playing tones via PWM

<p class="bg-success">
While you don't need to turn in the code for this part, I still recommend you do it! The sample
uses the TimerA1 module for PWM and the watchdog timer as a "tick" generator, which is probably
a good framework.
</p>

Before implementing the full code for this lab, you should start by getting the sound aspect
set up. Wire a piezo buzzer between to 2 PWM-capable pins. By connecting the device in this
manner and enabling one or both channels, the volume of the sound can be changed. Write code
that plays a standard 8-note octave scale (or different pattern if you choose) starting from
middle C (see [Wikipedia table](https://en.wikipedia.org/wiki/Scientific_pitch_notation)). Each
note should be played for 1 second. The scale should then repeat. Every other scale should be a
higher volume. Sample code to get you going is in [piezo_sample.c](piezo_sample.c).


#### Part 2: Software Debouncing

*The point of this portion of the lab is to implement switch debouncing in software. The
switches provided to you in class are reasonable, but still bounce noticeably.*

Humans can control their fingers on timescales of hundreds of milliseconds. In the final
portion of this lab, you will build a system which trains you to tap your fingers as fast as
possible in a particular pattern. Wire two buttons on your breadboard to your MSP430. You will
learn to press them in the pattern **1, 2, 1, 1, 2, 2**. The system will mark your progress with an
LED and a tone-playing buzzer.  The LED should get progressively brighter and the tone
progressively higher frequency as pattern is entered faster and faster. You should choose the
values such that they are noticable and there are at least **8 levels**. If pattern is entered
incorrectly, LED and sound should go off.  At any time, you should be able to reset the
training by holding both buttons simultaneously for 2 s. Resetting should cause the LED to flash.

**Save this code as `debounce.c`. Create a demo video that shows you playing and then resetting
and playing again. Upload your answered questions, code and the video URL to owlspace.**

**Bonus:** Implement a system in which doing something (entering the reset pattern twice?)
causes the system to enter a "programming" mode, in which the pattern can be changed.

