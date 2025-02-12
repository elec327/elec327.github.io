---
title: Lab 4
lab: 4
layout: default
group: labs-navigation
description: Uses of Timer Modules Beyond Interrupts
---

{::options parse_block_html="true" /}

### Lab #4: Uses of Timer Modules Beyond Interrupts (100 pts)

<div class="alert alert-info" role="alert">
#### **There is one goal for this assignment:**

  - To learn to leverage the PWM functionality of a Timer module  
</div>

<div class="alert alert-danger" role="alert">
#### Due Date: 2/14/2025
#### **What should be turned in?**

Because of the recess, in 2025, we did a Quiz instead of Lab 4.
</div>

### PWM RGB Rainbow
The Launchpad uses Pins PB22, PB26, and PB27 to control the 3 channels of an RGB LED. In this
lab, we will use PWM to cause this RGB LED to cycle through the colors of the rainbow.

The MSPM0+ timer modules come in two varieties, G and A. The A version can control 4 PWM outputs,
but the G version can only control two outputs. Unfortunately, on the Launchpad, the RGB LED is
not connected to pins that are fully accessible by a single TIMA instance, so we need to use two
modules for PWM.


### Detailed specification

  1. Template code which enables the 2 necessary Timer modules output, and a timer interrupt 
     which yields precise 100 ms timing can be found in this zip archive  [Lab4.zip](Lab4.zip).
     In addition, we recycle the timing code from Lab 3 to allow the colors to cycle every 100 ms.

  2. Your main task is a combination of aesthetics and coding. You need to develop a formula which
     produces pleasing values of PWM intensity that cycle through a rainbow of colors. 

  **Scoring criteria**
  4. You should produce at least 16 different colors.
  5. These should involve varying all 3 LEDs.
  6. The colors should cycle in an interesting, pleasing way.


