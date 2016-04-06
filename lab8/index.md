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

<img src="./location_5V.png" width="400">

**Task 1:** Wire up your motor to your launchpad:
  1. Connect the two inputs of the motor to your breadboard. Tape/glue a circle of cardboard to the
  drive pin of the motor so that you can see the motor rotating.
  2. The N-channel MOSFET transistor will act as a switch on the "low-end" of the motor. Thus,
  you should connect the Drain of the transistor to one wire of the motor, and +5V to the other
  wire. The Source of the transistor should be connected to ground, and the Gate should be
  connected to a PWM drive pin of the MSP430.
  3.  Use PWM to drive the motor at different speeds.

### Showing information via an LCD display

<img src="./181-04.jpg" width="400">

The product page for the LCD display is [here](https://www.adafruit.com/products/181). You will
also find two data sheets - [the primary one](./p181.pdf) and [one with more detail about the
character maps](./HD44780.pdf). 

**Task 2:** Display a message on the LCD display.
  1. Wire up the LCD display either in 4 pin or 8 pin mode.
  2. Display the message "000 RPM".
  3. Write a function to send out an arbitrary RPM message.

### Measuring rotation speed using a Hall-effect sensor

<img src="./158-00.jpg" width="400">

The product page for the LCD display is [here](https://www.adafruit.com/products/158).
[Datasheet](US5881_rev007.pdf).

**Task 3:** Integrate the Hall sensor.
  1. Add the Hall sensor to your breadboard with the input connected to a MSP430 pin.
  2. Implement a magnetic switch where bringing a magnet close to the sensor turns off/on the
  LED. (This will help you understand the effect of magnet distance and orientation.)


### Final device

Now, put it all together. Add the magnet to the carboard being driven by the motor. Count the
sensed magnetic switches and use this to set the PWM level to achieve a particular level of
RPMs. **Film a video where the motor runs at 10 RPM for 30 s and then 30 RPM for 30 s. Turn in
your video and code!**



