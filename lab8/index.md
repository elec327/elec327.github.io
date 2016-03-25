---
title: Lab 8
layout: default
group: labs-navigation
description: Motor Speed Control
---

{::options parse_block_html="true" /}

## Lab #8: Motor Speed Control
<div class="alert alert-info" role="alert">
#### **There are three goals for this assignment:**

  - To gain experience with motors, Hall-effect sensors, and LCD displays
  - To construct software which carries out feedback-control in real-time.
  
</div>

<div class="alert alert-danger" role="alert">
#### **What should be turned in?**

  1. Your **commented** code files. 
  2. Your answers to the questions. (Please submit in either PDF or TXT format.)
  3. A youtube link to a demo video showing speed control.

</div>

### Motor speed control with PWM

The motors in your Launchpad Sidekick kits require more than 3V to operate. Thus, you will need
to hook into a 5V supply in order to drive them. The test point to the right of the USB
connector on your g2553 Launchpads provides a 5V source. Use an N-channel mosfet to control the
motor, driving the gate with PWM.

### Showing information via an LCD display

<img src="./181-04.jpg" width="400">

The product page for the LCD display is [here](https://www.adafruit.com/products/181). You will
also find two data sheets - [the primary one](./p181.pdf) and [one with more detail about the
character maps](./HD44780.pdf). 

### Measuring rotation speed using a Hall-effect sensor

<img src="./158-00.jpg" width="400">

The product page for the LCD display is [here](https://www.adafruit.com/products/158).
[Datasheet](US5881_rev007.pdf).

label interval for timers in ms, etc). **Save this code as `mood_ring.c`. Create a demo video that
shows the timer-shifting colors from Part 1 and temperature shifting color from Part 2. For
Part 2, you should start with your device at one extreme, change it to the other, and then let
it return. Upload your answered questions, code and the video URL to owlspace.**

**Bonus:** Add a "heart-beat" functionality to your mood ring where the LEDs flash at 0.5 Hz,
but rather than flashing, become dimmer and brighter smoothly, with the color corresponding to
the temperature.

