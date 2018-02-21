---
title: Lab 6
lab: 6
layout: default
group: labs-navigation
description: Soldering Redux and Finalizing Thermodot Firmware
---

{::options parse_block_html="true" /}

## Lab #6: Building and programing the Thermodot PCB with randomness

_This lab builds on Lab 4 to make a device that flashes an RGB LED in an interesting pattern in
a way that depends on the ambient temperature. The goal is for you to continue to master
combining multiple elements of embedded system architecture._


<div class="alert alert-danger" role="alert">
#### What should be turned in?

  1. Your **commented** `thermodot.c` file (_Canvas_, but different from PCB files)

#### What should be demo'd live?
  1. Showing how your device changes color depending on temperature.
  2. Describing how you achieve a nice rainbow of colors.
  3. The code for this demonstration.

#### The lab will be due Feb 23, 2018

</div>

#### Part 0: Building and programming the Thermodot PCB

Begin by assembling your mood ring PCB and programming it with the code you developed for Lab
3. PAY ATTENTION to the values of resistance you use with the RGB LED. If you make them too
*big*, it may be fine when running from USB power, but cause problems when running from the
battery.

#### Part 1: Firmware Requirements

Unlike Lab 5, in this lab, the colors for your Thermodot should range throughout
the color spectrum including red, green, and blue and shades in between. Bright red
should correspond to hot and bright blue should be cold. For inspiration about
the colors in between you can look at the [wikipedia page on color temperature](https://en.wikipedia.org/wiki/Color_temperature) (though note that
for us, hot and cold are reversed from black body radiation).

**Specific Requirements** It is not enough to just vary the PWM levels as many
of you did for Lab 5. Different colors have different perceptual brightnesses,
and many of you also noted that the perceptual variation in brightness from 0
to 50% duty cycle is much larger than 50% to 100%. **You will be graded on whether
your colors go through a perceptually-nice rainbow.** Be prepared to modify your
code to sweep through the possible range of temperatures automatically for
visualization purposes. You must demo your actual device **working from battery
power**. Note that this will mean different currents flowing through the LED than
when driven from USB power!

**Your code** should be well commented and modular.

Save your firmware as `thermodot.c`. Turn this in on Canvas and demo your
device to the lab staff.
