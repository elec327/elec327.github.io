---
title: Lab 1
lab: 1
layout: default
group: labs-navigation
description: GPIO C Programming
---

{::options parse_block_html="true" /}

### Lab #1: Intro C Programming (100 pts)

<div class="alert alert-info" role="alert">
#### **There are three goals for this assignment:**


  - To get a taste for writing embedded code in the C programming language. 
  - To build a mental understanding for how GPIO works in the MSPMO+. 
  - To practice writing code for a custom PCB.
  
</div>

<div class="alert alert-danger" role="alert">
#### Due Date: Friday, January 23, 2026

We will do peer grading in class on Monday January 26, 2026, design and code will be assessed according
to the rubric described below. 

#### **What should be turned in?**

  1. A document in TXT or PDF format explaining your design. This might also include a diagram.
  2. Your **commented** code files.

</div>


#### The Task

You have been given a PCB designed by another engineer. The PCB is intended to function as a clock.
In future labs, we will focus on ensuring precise timing; in this lab your goal is to correctly
initialize the hardware and implement the passage of time.

The outer LED ring is intended to mark hours, and the inner ring is intended to mark minutes. On
the PCB design, these are labeled LEDA12, LEDA1, ..., LEDA11 (hours / outer ring) and 
LEDB12, LEDB1, ..., LEDB11 (seconds / inner ring).

The full KiCad project is available in the git repository in the [PCBs/Clock directory](https://github.com/ckemere/ELEC327/tree/master/PCBs/Clock).
Here is a screenshot of the block showing how the LEDs are connected to the MSPM0 pins.

![PCB Schematic Section](ClockSchematicRegion.png)

Note that each pin is labeled with its corresponding GPIO port and number (i.e., LED12A connects to PA0 and
LED7B connects to PA11).



##### 1. Initializing the hardware

As described in class, using simple GPIO requires correctly reseting and configuring several registers.
Specifically, the registers corresponding to the `GPIOA` and `GPIOB` modules, and those corresponding to
the IOMUX.

In class, we used the example of what needs to be configured in order to generate digital signals for the
pin labeled `PA0`. We described 3 basic steps:

   1. Reseting and powering on the GPIOA module
   2. Configuring the IOMUX
   3. Configuring the specific registers to set the value and enable channel 0

For PA0, the code looked like this:

```
/* 1. Reset and power on the GPIOA module */
*GPIOA->GPRCM.RSTCTL = 0xB100003;
*GPIOA->GPRCM.PWREN = 0x2600001;

/* 2. Configure the IOMUX */
IOMUX->SECCFG.PINCM[(IOMUX_PINCM1)] = (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001));

/* 3. Enable channel 0 with a specified initial value of 0
*GPIOA->DOUTCLR31_0 = (0x00000001);
*GPIOA->DOESET31_0 = (0x00000001);
```

To complete the initialization portion of the lab, you'll need to correctly complete step 1 for both the `GPIOA`
*and* `GPIOB` modules, as LEDs are connected to channels on both GPIOs.

**Helpful thought #1**
For each LED, there are TWO things that you need to know in order to make it light up (or turn off) and
ONE ADDITIONAL thing you need to know to initialize it for functionality. What are these three things?

  1. What GPIO peripheral is it connected to? (In the case of `PA0`, which is connected to LEDA12 or 
     the 12 o'clock hour hand outer ring, this is `GPIOA`.)

#### Development process

A critical part of any embedded system development project is to work in stages. Ideally each stage tests
specific portions of the code. Once a particular developmental stage is funcitoning correctly, you move on
to the next, more complex stage. A key part of being an embedded developer is to identify the requirements
for each of these stages and to plan your development process. By producing functional code at each step, you
can be confident in the function of the final system.

For this project, we would suggest at least the following 3 preliminary stages. 
  1. **Programming the PCB.** Wire up the PCB to the Launchpad debug section. Program the `blink` project
     and ensure that you see the 12 o'clock LED flashing. __Completion of this stage will give you confidence
     that you understand how to wire up the PCB for programming and that it functions correctly.__
  2. **Initializing the LEDs.** Write your initialization code, and then set the value of all 24 of the LEDs
     to blink. __This at least partially validates your initialization code and ensures that your PCB is
     functional in terms of LEDs being connected to known ports.__
  3. **Make the LEDs Flash in Sequence**. Write code to go through a loop of all of the LEDs one at a time.
     __This will ensure that you have correctly mapped LEDs to GPIO port/channels.__
