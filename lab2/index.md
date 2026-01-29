---
title: Lab 2
lab: 2
layout: default
group: labs-navigation
description: Low Power Design
---

{::options parse_block_html="true" /}

### Lab #2: Using Timer Interrupts To Save Power (100 pts)

<div class="alert alert-info" role="alert">
#### **There is three goals for this assignment:**

  - To understand how sleep modes lower power consumption and more broadly how
    the power budget of an embedded system can be calculated.
  - To experience how persistence of vision enables digital control of LED brightness
  
</div>

<div class="alert alert-danger" role="alert">
#### Due Date: 1/31/2026
#### **What should be turned in?**

  1. A written report documenting (a) your estimates and (b) your measurements
     of the power consumption of the three different firmware Phases for the clock
     described below. The report should be in TXT or PDF format.
  2. Three zip files containing the all of the code files (.c and ,h) required to
     compile your firmware Phases. Specifically Lab1.zip (either the same as Lab 1, or revised if desired), 
     Phase2.zip (Lab 1 revised with interrupts), and Phase3.zip (Phase 2 revised with pulse-width-modulated LED intensity.)

To be precise, YOU SHOULD NOT MODIFY delay.c or delay.h or startup_mspm0g350x_ticlang.c.

Each zip file should include ONLY and EXACTLY the following 7 files:
  - initialize_leds.c
  - initialize_leds.h
  - lab2.c
  - state_machine_logic.h
  - state_machine_logic.c

One of the grading rubrics will be that your submission meets this specification.

</div>

### High level overview

This lab will eventually revisit the clock from Lab 1. We will modify this code in such a 
way that we save power and lower power consumption in one go. Specifically, we will enable 
the processor to go to sleep (into a low power mode) every cycle through our state 
machine loop. To wake up, we will leverage the ability of a Timer Module
peripheral to produce regular well-timed interrupts. We will also analyze our
project design, and modify the design to lower power even more. We will use the
EnergyTrace feature of the Launchpad to measure power consumption as a way of 
validating our work.


### Step 1: Estimating and measuring the power consumed by your Lab 1 firmware

The first step of this lab is to revisit the code that you have written for Lab 1.
Assuming that you roughly followed the suggested state machine pattern (i.e., calling 
`delay()` between each tick), everyone's estimated power consumption should be 
roughly the same. Datasheets for the 3 LEDs are found in the Github repository:
   + Larger 12 o'clock red LED -- [PCBs/Clock/Datasheets/C19171390.pdf]()
   + Smaller red LEDs - [PCBs/Clock/Datasheets/C25503345.pdf]()
   + Smaller yellow LEDs -- [PCBs/Clock/Datasheets/C25503856.pdf]()
From the schematic, you can see that the red LEDs are all paired with 470 ohm
current limiting resistors, while the yellow ones are paired with 330 ohm resistors.
You can assume that VCC is 3.3V.

Because Lab 1 did not attempt any special power modes, you can assume that
the current draw is dominated by the LEDs and the MSPM0+ on the clock PCB. Using the
datasheets of the LEDs and the MSPM0+, estimate the average current the device will
use while running through one complete cycle of time indications (i.e., noon to midnight).
This should be a few sentences, perhaps with depicting your caclculation.

Next, using the EnergyTrace functionality of Code Composer Studio 12.8, measure the
average device power. Report your measurement. Are your measurements the same as you
estimated?

### Firmware Phase 2: Improving the code - sleep rather than delay

Using the TimerG0 module code from the `blink_standby` project, modify your code
from Lab 1 to go into standby between clock ticks rather than calling delay. You
will need the code for (a) timer module initialization, (b) system control / sleep mode
initialization, (c) setting the timer module period (the `LOAD` register), (d)
starting the timer and enabling interrupts, and (e) going to sleep each cycle.

Now, consider the code that you have written. Considering only the code that is within
the infinite loop (ignoring the cost of initialization), what is the AVERAGE expected
current consumption of the MSPM0+. Note that this will depend on how long your firmware
is awake each tick cycle (i.e., how efficient your code is). As for Phase 1, document
your estimation process, then measure using EnergyTrace and report the measuements.

### Firmware Phase 3: Improving the code even further - using PWM for LED illumination

Power consumption for the clock firmware is dominated by the LEDs. Recognizing this fact,
and that the LEDs are quite bright, now modify your state machine to implement pulse
width modulation (PWM) of LED instensity.

PWM is quantified by the duty cycle and the frequency. For the purposes of this lab, we 
will fix the duty cycle to be 25%. You should pick the PWM frequency to jointly optimize
the power consumption and aesthetics of the clock. In particular, you should avoid a
PWM frequency that are so low that flashing can be perceived. Justify the choice of PWM
frequency in your documentation.

Maintaining the state machine discipline we adopted in Lab 1, you should code the PWM
modulation within the state machine context. Estimate the power of the PWM-modulated 
clock firmware, and then measure it. As for Phases 1 and 2, document your estimation
your estimation process and measurements.

### Grading Rubric

| Section | Criteria (Binary Assessment) |
|--------|------------------------------|
| **I. Firmware Phase 1 - Compiles** | Baseline Code Included: Did the student include the original Lab 1 firmware as a separate, buildable codebase? |
| **I. Firmware Phase 1 - Works** | Functional Correctness: Does the baseline firmware behave the same as Lab 1 (correct LED sequencing and timing)? |
| **I. Firmware Phase 1 - Documented** | Baseline Power Reported: Is baseline power consumption estimated or measured and documented? |
| **II. Firmware Phase 2 - Compiles** | Baseline Code Included: Did the student include the Phase 2 firmware as a separate, buildable codebase? |
| **II. Firmware Phase 2 - Architecture** | Hardware Timer Interrupt Used: Does the firmware use a timer interrupt rather than busy-wait delays? |
| **II. Firmware Phase 2 - Works** | Correct Behavior Preserved: Does the LED behavior match the baseline version? |
| **II. Firmware Phase 2 - Documented** | Sleep-Mode Power Reported: Is power consumption for the sleep-based version estimated or measured? |
| **II. Firmware Phase 2 - Documented** | Power Reduction Explained: Does the report explain *why* this version consumes less power than the baseline? |
| **II. Firmware Phase 23- Compiles** | Baseline Code Included: Did the student include the Phase 3 firmware as a separate, buildable codebase? |
| **III. Firmware Phase 3 - State Machine** | Code Architecture: Is the PWM implemented using a state machine? |
| **III. Firmware Phase 3 - PWM LED Control** | Reduced Brightness Achieved: Is LED brightness clearly reduced compared to always-on output? |
| **III. Firmware Phase 3 - Aesthetics** | No Visible Flicker: Do the LEDs appear steady with no visible flashing or strobing? |
| **III. Firmware Phase 3 - Documentation** | PWM Frequency Justified: Does the report clearly justify the chosen PWM frequency in terms of sleep time vs. perceptual flicker? |
| **III. Firmware Phase 3 - Documentation** | PWM Power Reported: Is power consumption measured or estimated for the PWM version? |
| **III. Firmware Phase 3 - Documentation** | Comparison to Other Phases: Does the report compare PWM power usage to both the baseline and sleep-only versions? |

