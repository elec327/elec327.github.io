---
title: Lab 5
lab: 5
layout: default
group: labs-navigation
description: ADC, Software Architecture, Beginnings of the Thermodot Firmware
---

{::options parse_block_html="true" /}

## Lab #5: Writing the basic structure of the Thermodot firmware

<div class="alert alert-info" role="alert">
#### **There are two goals for this assignment:**

  - To learn and use the MSP430's analog-to-digital conversion circuitry
  - To create structured code which carries out multiple asynchronous/independent functions

</div>

<div class="alert alert-danger" role="alert">
#### **What should be turned in?**

  1. Your **commented** `timer_shift_PWM.c` and `mood_ring.c` files.
  2. Your answers to the questions. (_Canvas_)

#### **What should be demo'ed live?**
  1. Your timer-based and temperature-based RGB LED codes.

#### **Lab 5 will be due Feb 26.**

</div>

#### Part 1: Multiple Timers, Program Structure

For Lab 2, you figured out how to run your MSP430 in Low Power Mode. In order to make your mood
ring, you'll need to properly architect your code. To begin with, think about the different
time scales at which you want to act:

  1. For optimal power, which clock should you use for PWM? Ideally the PWM control frequency
  should be one or two orders of magnitude higher than the minimum (let's say > 5 kHz). How would
  you set the PWM control clock to run at 6 kHz?
  2. **[Not scored]** The MSP430G2553 has 3 timer modules –two are the TimerA
  type, and one is  the Watchdog Timer (WDT+). Unlike the TimerA module, the
  WDT+ module cannot control PWM outputs and has less flexibility in general.
  However, it is very useful as a tool to trigger low level state changes. How
  would you configure the WDT+ module to generate periodic (maskable)
  interrupts?
  3.  **[Not scored]** If your `main()` function contains an instruction which
  puts the CPU into a low power mode, what are the minimal interrupt service
  routine instructions required to wake the CPU and return function to the
  `main()` function?
  {: class="questions"}

You can either use three separate LEDs a through-hole RGB LED, or a SMD unit
soldered to a breakout board for the rest of Part 1. Modify your code from Lab 3
so that the `main()` function adjusts the PWM parameters to increase the
brightness of the green LED and decrease the brightness of the red LED through 100
levels (so that maximum green corresponds with minimum red and vice versa). Your
`main()` function should be an infinite loop, with a command to go into low
power mode at the end of each color shift cycle. Set up the WDT+ module to
generate an interrupts using the "16ms" scaling to wake up the CPU, so that the
shifts in color happen smoothly.

  4. Assuming you use the VLO to control the WDT and TimerA modules, what is the
  lowest LPM which will allow your device to continue to function?
  {: class="questions" start="4"}

**Save this code as timer\_shift\_PWM.c.** You will demo both this
timer-shifting colors as well as temperature shifted color from Part 2.

#### Part 2: Making a Mood Ring

In this part, we'll put together Part 1 and add in ADC to make a "mood ring"
with the RGB LED controlled by the on board temperature sensor. We'll start off
with a few questions that should guide learning how to use ADC:

  5. **[Not scored]** How would you turn on the ADC10 module and tell it to
  sample from the internal temperature sensor? What is the default voltage range
  for conversion?
  6. What are two ways of discovering when the ADC10 module has finished a
  conversion? Which method will be more efficient from a power perspective?
  7. **[Not scored]** What is the minimum sampling period for the internal
  temperature sensor on the ADC10 module? Assuming that you run the ADC10 using
  the VLO at 12 kHz, what is the maximum sampling rate for temperature?
  8. **[Not scored]** What kind of ADC is used in the MSP430? Take a look at the
  [datasheet for the Atmel (now Microchip!?!?) SAM
  D21](https://www.microchip.com/wwwproducts/en/ATSAMD10D14), which is
  used in the Arduino One. What type of ADC architecture do you think it uses
  (hint: take a look at the "Conversion Timing" in the ADC section)?
  9. Assume you've already maximized the sampling clock and minimized the hold
  time. If you could make an architectural change to increase the rate at which
  samples were acquired by the MSP430 ADC10, how could you do it? Is there a
  simple modification that would let users trade off bit depth for sampling rate
  (hint: the SAM D21 has this feature)? (I'm looking for one answer for both 
  questions!)
  10. **[Not scored]** In an oversampling ADC, what multiple of the sampling
  rate yields an additional bit of precision? In a sigma-delta ADC, what
  multiple of the sampling rate yields an additional bit of precision?
  {: class="questions" start="5"}

Modify your `main()` function so that the code goes into low power mode twice:
after enabling the ADC10 to sample temperature and after changing the PWM
parameters for the LEDs. Set up your ISRs for the ADC10 and WDT interrupts to
return control to the `main()` function, with the WDT interrupt executing at
1/16 ms. Once you receive a sample temperature, you should scale your LED output
so that cold will be fully blue and hot will be fully red. See the color chart
[here](https://en.wikipedia.org/wiki/Color_temperature). You can play around
with "hot" and "cold" values, try to get them to a range where if you warm your
hands and touch the MSP it's "hot" and if you don't touch it for a while or
actively cool it it's "cold". This is now the code for your "mood ring" on your
breadboard. Make sure to comment your code in detail, such that any design
decisions you made are easily available (which components are on which pins,
label interval for timers in ms, etc). **Save this code as `mood_ring.c`.** You
will demo this and the timer-based color shifting.
