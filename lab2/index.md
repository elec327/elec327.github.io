---
title: Lab 2
lab: 2
layout: default
group: labs-navigation
description: First Launchpad Project
---

{::options parse_block_html="true" /}

### Lab #2: First Launchpad Project (100 pts)

<div class="alert alert-info" role="alert">
#### **There is one goal for this assignment:**

  - To write your first microcontroller code, interacting with the world via GPIOs
  
</div>

<div class="alert alert-danger" role="alert">
#### Due Date: 1/31/2025
#### **What should be turned in?**

  1. Your **commented** encode_morse.c file. Your grade will be assigned based on
     functionality as defined in the Detailed Specifications below.


</div>

### High level overview

This lab follows the theme begun in [Lab 1](../lab1), except now, instead of using
`printf()` to output text to a terminal screen, you will flash a Morse code message 
on one of the LEDs on your MSPM0 Launchpad. 

The Autograder will be configured to record the digital output of your Launchpad, 
and your grade will be based on the details below. To test precise timing details of
your outputs, we are providing a firmware that you can upload that will display
the duration of on pulses through the serial port.

### Detailed specification

  1. As in Lab 1, the message will be specified as a C-string using the macro 
  `MESSAGE` during compilation. 
  2. (__Simplified alphabet.__) In this lab, dots will again be specified by the `'.'` 
  (period) character and dashes will ONLY be specified by the `'-'` (dash) character, 
  and inter-word gaps will ONLY be specified by the
`';'` (semicolon) characer. 
  3. (__No special cases.__) In addition, you do not need to worry about the special cases 
  from Lab 1 of unspecified characters, or sequences of inter-character and inter-word gaps. 
  (For example, you will never see `";;"`, `" ;"`, `"  "`, or `"; "`). In addition, every 
  message will be concluded with an inter-word character (`";"`).

  **Scoring criteria**
  4. Following the example code, you should set your system oscillator to 4 MHz. (10 pts)
  5. You should produce the correct output patterns for the 10 test case messages. At the
     end of each message, you should loop infinitely. You may assume that the first character 
     will be either a dot or a dash (not a space). **(40 pts)**
  6. Your code should flash either the blue or red LED on the launchpad. The led color
     will be specified as either `#define REDCOLOR 1` for red or `#define BLUECOLOR 1` for blue.
     One or the other will be set, but not both. **(20 pts)**
  7. Your "dot" unit should be precisely 100 ms long, or 3200000 clock cycles. **(20 pts)**
  8. Your morse code output should be cycle precise for arbitrary messages. **(10 pts)**
  9. The projects that achieve 100 pts will be ranked based on the time from processor
     reset until the first dot or dash is produced. Bonus points will be assigned 
     based on latency rankings.
  
### Getting started

A Code Composer Studio project which sets up the clocks and initializes the M0+ microcontroller
can be found in the zip file [Lab2.zip](Lab2.zip). Unzip this into your CCS workspace folder,
then use the `Import` command from the `File` menu to add it to your workspace. If everything
is configured properly, you should be able to click the build button and see it compile without
errors. If you click the load button, it should load to your connected Launchpad.

In class, we will go through the process of how we interface to a GPIO in the ARM M0+ family.
Initiallizing the system for a GPIO output involves 5 steps that are described in comments
(but without code) in the `lab2.c` file in the starter project. In addition, we'll talk about
the 3 registers used to effect outputs to GPIOs - `DOUTSET31_0`, `DOUTCLR31_0`, `DOUTTGL31_0`.
Helpful text references for this Lab can be found in Section 2.2 of the textbook 
([Chapter 2](https://users.ece.utexas.edu/~valvano/mspm0/ebook/Ch2_IntroToInterfacing.html) in 
the online version.)
