---
title: Lab 3
layout: default
group: navigation
---

# Lab #3: Coding up the mood ring

## Part 1: Multiple Timers, Program Structure

For Lab 2, you figured out how to run your MSP430 in Low Power Mode. In order to make your mood ring, you'll need to properly architect your code. To begin with, think about the different time scales at which you want to act:

1. 1)For optimal power, which clock should you use for PWM? Ideally the PWM control frequency should be one or two orders of magnitude higher than the minimum (let's say > 5 kHz). How would you set the PWM control clock to run at 6 kHz?&nbsp;
2. 2)The MSP430G2553 has 3 timer modules –two are the TimerA type, and one is the Watchdog Timer (WDT+). Unlike the TimerA module, the WDT+ module cannot control PWM outputs and has less flexibility in general. However, it is very useful as a tool to trigger low level state changes. How would you configure the WDT+ module to generate periodic (maskable) interrupts?&nbsp;
3. 3)If your main() function contains an instruction which puts the CPU into a low power mode, what are the minimal interrupt service routine instructions required to wake the CPU and return function to the main() function? &nbsp;

You can either use two separate LEDs or an RGB LED unit soldered to a breakout board for the rest of Part 1. Modify your code from Lab 2 so that the main() function adjusts the PWM parameters to increase the brightness of the blue LED and decrease the brightness of the red LED through 16 levels (so that maximum blue corresponds with minimum red and vice versa). Your main() function should be an infinite loop, with a command to go into low power mode at the end of each color shift cycle. Set up the WDT+ module to generate an interrupt every second to wake up the CPU, so that the shifts in color happen every second.

1. 4)Assuming you use the VLO to control the WDT and TimerA modules, what is the lowest LPM which will allow your device to continue to function?&nbsp;

Save this code as timer\_shift\_PWM.c. You will create a demo video which contains both the timer-shifted colors and temperature shifted colors.

## Part 2: Making a Mood Ring

In this part, we'll put together Part 1 and add in ADC to make a "mood ring" with the RGB LED (ignoring the green part) controlled by the on board temperature sensor. We'll start off with a few questions that should guide learning how to use ADC:

1. 5)How would you turn on the ADC10 module and tell it to sample from the internal temperature sensor? What is the default voltage range for conversion? &nbsp;
2. 6)What are two ways of discovering when the ADC10 module has finished a conversion? Which method will be more efficient from a power perspective? &nbsp;
3. 7)What is the minimum sampling period for the internal temperature sensor on the ADC10 module? Assuming that you run the ADC10 using the VLO at 12 kHz, what is the maximum sampling rate for temperature?&nbsp;

Modify your main() function so that the code goes into low power mode twice: after enabling the ADC10 to sample and after changing the PWM parameters for the LEDs. Set up your ISRs for the ADC10 and WDT interrupts to return control to the main() function, with the WDT interrupt executing at 4 Hz. Once you receive a sample temperature, you should scale your LED output so that cold will be fully blue and hot will be fully red. (You can play around with "hot" and "cold" values, try to get them to a range where if you warm your hands and touch the MSP it's "hot" and if you don't touch it for a while or actively cool it it's "cold".) &nbsp;This is now the code for your "mood ring" on your breadboard. Make sure to comment your code in detail, such that any design decisions you made are easily available (which components are on which pins, label interval for timers in ms, etc). Save this code as mood\_ring.c. Create a demo video that shows the timer-shifting colors from Part 1 and temperature shifting color from Part 2. For Part 2, you should start with your device at one extreme, change it to the other, and then let it return.


**Bonus:** Add a "heart-beat" functionality to your mood ring where the LEDs flash at 0.5 Hz, but rather than flashing, become dimmer and brighter smoothly, with the color corresponding to the temperature.

