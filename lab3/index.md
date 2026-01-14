---
title: Lab 3
lab: 3
layout: default
# group: labs-navigation
description: Using Interrupts for Precise Timing
---

{::options parse_block_html="true" /}

### Lab #3: Using Interrupts for Precise Timing
--- (100 pts)

<div class="alert alert-info" role="alert">
#### **There is one goal for this assignment:**

  - To write your first interrupt service routine in order to provide precise timing
  - To think about low power modes
  
</div>

<div class="alert alert-danger" role="alert">
#### Due Date: 2/7/2025
#### **What should be turned in?**

  1. Your **commented** lab3.c file. Your grade will be assigned based on
     functionality as defined in the Detailed Specifications below.

</div>

### High level overview

This lab follows the theme begun in [Lab 1](../lab1), except now, instead of using
`printf()` to output text to a terminal screen, you will flash a Morse code message 
on one of the LEDs on your MSPM0 Launchpad. Critically, now that you've suffered
through the process of trying to achieve precise timing with delays, we're going
to do it a better way -- using a Timer Module Interrupt!

The Autograder will be configured to record the digital output of your Launchpad, 
and your grade will be based on the details below. Unfortunately, using the SYSTICK
register to test precise timing details of your outputs will not work for this lab,
as the interrupt process makes it inaccurate. As demonstrated in class, one can use
a second timer module (i.e., TIMA1->CTR) rather than SYSTICK to observe proper timing
details. HOWEVER, if you follow the state machine approach, this should not be necessary.
You may also use another Launchpad configured to count clock edges
([project here](https://github.com/ckemere/ELEC327/tree/master/Code/ClockedPulseWidth)). 


### Detailed specification

  1. Message specification is as described in [Lab 2](../lab2/).

  2. Template code which enables the LFCLK output, and a timer interrupt 
     which yields precise 100 ms timing can be found in this zip archive  [Lab3.zip](Lab3.zip).
     Because we are using interrupts, if you follow the state machine pattern from
     the template, you do not need to worry about measuring the timing statistics of
     your code - it is produced for free!

  3. Your main task is to develop a state machine functional form for the morse code
     transmission problem. In this case, the state machine should have a structure
     where the next state is completely determined by the current state, and (potentially)
     the current/next symbol message string. 

  **Scoring criteria**
  4. You should produce the correct output patterns for the test case messages. At the
     end of each message, you should loop back to the beginning infinitely. 
     You may assume that the first character will be either a dot or a dash (not a space). **(70 pts)**
  5. Your code should flash the **green** LED on the launchpad.  **(10 pts)**
  6. Your "dot" unit should be roughly 100 ms long, or 3277 clock cycles. (Measuring this is
     difficult. You can assume it to be correct if you do not change the structure of the code.) **(10 pts)**
  7. Your morse code output should be cycle precise for arbitrary messages. **(20 pts)**
  8. The projects that achieve 100 pts will be ranked based on the time from processor
     reset until the first dot or dash is produced. Bonus points will be assigned 
     based on latency rankings. Note that the microcontroller must utilize STANDBY mode 
     to receive bonus credit here.


