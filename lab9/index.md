---
title: Lab 9
lab: 9
layout: default
group: labs-navigation
description: Digital to Analog Conversion
---

{::options parse_block_html="true" /}

### Lab #9: SPI Accelerometer Read-Write  (100 pts)

<div class="alert alert-info" role="alert">
#### **The goals for this assignment:**

  - To learn to use SPI in read and write mode
  - To interface with a peripheral using SPI
  - To read a datasheet
  
</div>

<div class="alert alert-danger" role="alert">

#### Due Date: 4/19/2025

#### What should be turned in?
Your code files and a text README file.

</div>

A template project is given in [lab9_template.zip](lab9_template.zip). In the template 
project, the data from the accelerometer is read in via SPI and copied to a local
struct variable on line 100. If you set a breakpoint on this line, and creatae a
watch expression for "currentAccel", you will see the value of the acceleration
which has been read in.

[Data sheet for ST Microelectronics LIS2HH12 SPI Accelerometer](lis2hh12.pdf)
[Application Note for LIS2HH12 SPI Accelerometer](an4662-lis2hh12-mems-digital-output-motion-sensor-ultralowpower-highperformance-3axis-pico-accelerometer-stmicroelectronics)

#### Your task
Your goal is to write code so that the 4 LEDs on the Simon PCB "point downward".
This takes advantage of the fact that we are always experiencing the earth's
gravitational pull downward. You can see this by sitting the PCB flat, in
which case the z component of the acceleration will be large and positive.

You have 3 options for implementation.

##### Option 1 - grade 90/100
The simplest option for your code is to detect the direction of the acceleration 
vector and illuminate the one LED which is closest to the ground.

##### Option 2 - grade 95/100
The second simplest option is to make a graded illumination of the bottom-most
two LEDs such that their intensity shows which angle the gravity vector
is pointing. If the PCB is aligned such that two of the LEDs are parallel to the
ground and equally bottom-most, they would both be half intensity. Otherwise,
their relative intensity should change depending on which is closest.

Note that if you are using the global brightness bit of the SPI LEDs, it's 
probably safest not to go above level 16 (i.e., the first byte is 0xEF).
Otherwise, you may draw too much current.

##### Option 3 - grade 100/100
Satisfy the Option 2 code, and additionally, set the COLOR of the LEDs to
indicate whether the PCB is facing upward or downward. Perfectly upward should
be pure green for the LEDs which are illuminated and perfectly downward
should be pure red.


##### Bonus options:

  - 5% Bonus - Set up accelerometer to signal when data is available and poll for this GPIO input
  - 10% Bonus - Implement a button push to calibrate the PCB orientation, using the accelerometers built in calibration features
  - 15% Bonus -  Implement the data available signal and use MSPM0+ GPIO interrupt to detect it.

  _Note that the calibration and signal bonuses are additive._
