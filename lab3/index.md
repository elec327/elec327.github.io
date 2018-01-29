---
title: Lab 3
layout: default
group: labs-navigation
description: PWM, LPM, and PCB Design
---


{::options parse_block_html="true" /}


## Lab #3: PWM, Low Power Modes and PCB Design

<div class="alert alert-info" role="alert">
#### **There are three goals for this assignment:**

  - To learn and use PWM to modulate signal insensity
  - To learn and carry out various aspects of printed circuit board design
  - To learn more about low power modes and especially LPM3
  
</div>

<div class="alert alert-danger" role="alert">
#### **What should be turned in?**

  1. The EAGLE CAD .sch and .brd files for your design. (_Canvas_)
  2. The manufacturing files - `your-file-name.GBL` (bottom layer), `your-file-name.GML` (board
  outline), `your-file-name.GTL` (top layer) and `your-file-name.TXT` (drill locations).
  **Don't zip, compress, or otherwise combine these files!** (_Canvas_)
  3. Your **commented** `PWM_test.c` file (_Canvas_, but different from PCB files)
  4. Your answers to the questions (_Google Form_)

#### **What should be demo'd live?**
  1. A demonstration of an LED with intensity being modulated using PWM.
  2. The code for this demonstration.
  3. Your EAGLE CAD design.

#### Part 1 of the lab will be due Feb 2, Part 2 will be due 

</div>

#### Part 1: Different Clocks, Low Power Mode, and PWM
For Lab 2, you learned how to switch the timer interrupt from the DCO to the VLO by, in part,
changing its source from the SMCLK to the ACLK. As discussed in class, the primary advantage of
the VLO is **much lower power** consumption than the DCO. It also is lower frequency, which can
be convenient if you want infrequent timer interrupts.

  1. **(Review, not scored)** Using the DCO, what is the minimum frequency for a timer
  interrupt? What is the typical default frequency of the VLO? How do you turn on the VLO, and
  how do you change code from last week to run off the VLO instead of the DCO?
  {: class="questions"}

LPM4 consumes very little power. I noticed, playing around with my Lab 2 pendant, that if I
removed the battery while in LPM4, the capacitory between power and ground held enough charge
to keep the device functioning (in LPM4) for at least a few seconds. To see this yourself,
remember that on first power up, the pendant will always start with LED1 illluminated. So start
it going, and then go into LPM4 when the next LED will _not_ be LED1. Remove the battery, wait
a while, then put the battery back and push the button again. You'll see that it will continue
on where it left off. If you push the button while it's asleep, you'll rapidly discharge the
capacitor and when you put the battery back in, it will start with LED1 again.

  2. According to the datasheet, power consumption in LPM4 is ~100 nA @ 2.2V. Lets assume we
  can model the device in LPM4 as a resistor. What is the resistance? Assume that right before
  you take the battery out, the capacitor is charged to 3V (i.e., battery voltage). Then, we
  can define the system as a capacitor discharging into a resistor. The brownout circuit will
  trigger a device reset when the power level drops too low. Let's assume that that value is
  1.35V. Finally, let's assume that the capacitor between power and ground which you soldered
  on is (actually) 10 µF. How long will it take for the voltage to drop from 3V to 1.35V?
  Experiment with your Lab 2 PCB. Do you find that the state is maintained as long as you
  predicted?
  {: class="questions" start="2"}

In Lab 2, you used the timer interrupt to wake up the CPU periodically to control which LED was
lit on your PCB. For Labs 3 -- 5, we want to generate PWM signals, which will end up
potentially using both of the TimerA modules on the MSP430G2553. There is a third, easily
forgogtten, timer module on the MSP430G2553, though. Before you look in the skeleton code for
Lab 3, see if you can remember what it is.

Now take a look at the [skeleton
code](https://raw.githubusercontent.com/ckemere/ELEC327/master/Labs/Lab3/lab3_skeleton.c). This
program follows the same code pattern as in Lab 2. Succinclty, this pattern involves a main
loop which contains the program logic. At the end of each main loop cycle, the device goes into
LPM3, and then the timer interrupt wakes it back up.
  
  3. What is the function of the function call `__bic_SR_register_on_exit(LPM3_bits);`? What
  would be the result to the program if we replaced this with `__bic_SR_register(LPM3_bits);`?
  4. (**not graded**) What clock sources can drive the ACLK? In which low power modes is only ACLK active? If
  we only want to enable the VLO when not in an interrupt, what low power mode should we put the
  MSP430 into?
  5. (**not graded**)  What is the difference in supply current between LPM1 (when SMCLK is set to 1 MHz from the
  DCO) and LPM3 (when ACLK is set to use the VLO)? Note that when the DCO is on, LPM1 power
  will be dominated by the DCO/DC generator and performance will be more like LPM0.
  6. In VLO-driven mode for the ACLK, what frequencies are available for the WDT+ interrupt?
  What code in the skeleton that sets the interrupt nominally at 4Hz? Why do we describe the
  WDT+ interrupt rates as "nominal"?
  {: class="questions" start="3"}

##### PWM

To change the brightness of an LED (or most other analog devices), we use PWM. This essentially
changes the brightness by altering the duty cycle of the output signal. We could do this
manually -- i.e., write code using the timer interrupts that makes the appropriate output bit
high or low for the apropriate amount of time. However, many microcontrollers include special
hardware that allows for this to be done automatically. In the MSP430G2553, the two TimerA
modules can drive up to 3 pins each with PWM signals, with the limitation that the fundamental
frequency for the 3 pins must be the same -- the module's selected clock frequency. Because PWM
is a useful function for controlling intensity, the Timer modules are designed so that this
constraint will still let a variety of pulse patterns to be generated. Hence the various modes
(continuous, up, up/down). 

  7. The timer counter register (TAR) is 16-bits. Assuming we use the VLO to drive the Timer
  module at 12 kHz, and run the counter in up/overflow mode, where it increments to 0xFFFF then
  overflows to 0x0, at what frequency will the TAR overflow? If we want our PWM modulation to not
  appear to flicker, the minimum modulation frequency is about 100-200 Hz. Is this achievable if
  the TAR is configured to overflow?
  {: class="questions" start="7"}

The TimerA module allows us to set various pins to be on for a fraction of the timer counter
period, creating a PWM signal when it is pulsed fast enough. These pins are depicted in the
device datasheet.

  8. Say we want to use Timer A1 for our PWM signal. Which pins is register 1 of Timer A1
  capable of sending a PWM signal to? What should PxSEL, PxSEL2, and PxDIR be for these
  pins?
  9. (**not graded**) In up mode, the timer will continuously count up to the value in TA1CCR0,
  resetting to 0 every time it reaches it. If we want our output (using TA1CCR1) to be initially
  on for some fraction of each cycle and then turn off when TA1CCR1 is reached, what output mode
  should we put the capture compare block in?  How do we actually set it to this mode?
  10. To drive an RGB LED, you in general need 3 output pins. In general, what is the maximum
  number of PWM signals that can be generated by the Timer A1 module? What if the module
  is configured in up mode?
  11. If you had to generate 4 different PWM signals (i.e., using both Timer A1 and Timer A0)
  what is a valid set of 4 output pins?
  {: class="questions" start="8"}

Write some code to toss all this together. Source Timer A1 off the VLO clock, leaving it at its
default frequency. Configure your registers such that the duty cycle of the LED input signal
is 50%, and make sure to enable the LPM found in b). Since the PWM signals are automatically
generated, you should not need an ISR.

  12. If you were to set CCR0 to be 500, why does the LED flicker and not dim?
  {: class="questions" start="11"}

##### Lab 3 programming task
Now, combine the PWM code you just wrote with the skeleton code. Your goal is for the LED to
change duty cycle from 0% to 100% in 5% steps every clock tick. You should be able to
accomplish this by changing the value of the CCR1 register. **Demo this functionality and turn
in your code.**


#### Part 2: Designing a ThermoDot

In this part, we will put together most of the concepts from Part 1, creating a circuit with an
RGB LED and a temperature sensor. In order to do the rest of the assignment, you will need to
clone the [ELEC327 reposistory](https://github.com/ckemere/ELEC327) from github (if you have
not done so yet). In the `Labs/Lab3/Datasheets` directory, you will find a data sheet for the
[RGB LED](https://www.sparkfun.com/products/10866) we will use on the Mood Ring PCB, and a
[temperature sensor](https://www.digikey.com/products/en?keywords=296-25569-1-ND). Refer to the
data sheet for the RGB LEDs to choose current-limiting resistors.

The temperature sensor will be used with the built in analog to digital converter (ADC) module
of the MSP430g2553. So the output pin will need to be connected to an appopriate input pin. We
will discuss the ADC module further in future weeks. For now, you can see from the data sheet
that there are eight pins (labeled A0-A7) which can be used for ADC input. I suggest you
connect the temperature sensor to pin P1.0/A0. If you look at the temperature sensor's data
sheet, you'll see that it is recommended that a capacitor be placed between the output line and
ground -- you may ignore this!

We will be using Eagle to design a PCB which contains the MSP430, RGB LED and a teperature
sensor. In the `Labs/Lab3` directory, you will find a schematic which contains all but one
of the parts you will need. These are all part of the ELEC327 library, which is found in the
`PCBs` directory. You will need to create 2 new parts - the RGB LED and the temperature sensor.
You will need to make both a schematic symbol and a package footprint.

Eagle comes with a good number of parts, but not all that you need. Start with the RGB LED. You
should create a personal library for parts you make. Then, start with the "symbol". Make sure
to adequately labels the various connections. Pay special attention to the direction of current
flow through each LED. Then you should create a "footprint", referring to the data sheet for
the spacing of the pads. Finally, combine the symbol and footprint so that the pins are
connected to the right pads. Then, do the same for the temperature sensor. 

Once you've made the RGB LED and the temperature sensor, add them to the schematic and connect
them to the MSP430. We already have suggested P1.0/A0 for the temperature sensor. **The RGB LED
should be connected to PWM output pins connected to available Timer outputs. Use the *TA\*.1
and TA\*.2* outputs and not the *TA\*.0* one so that you can use the VLO!!!!** {: style="text-decoration:underline"} 

Next, then create a `.brd` file and route all of the connectionts. Keep in mind that the
battery package is solid and plastic, so you should not place any parts on top of it. One
solution is to put everything but the battery on one side of the PCB and the battery on the
other. Try to make the final board approximately 40 mm x 40 mm. Additionally, for this project,
PCB designs should be rectangular. After routing, check to make sure that it passes the
electrical rule check (ERC) and design rule check (DRC), using the DRC rules given in the
`PCBS/AdvancedCircuitsBarebones.dru` rule file. 

When you're finished, make a PDF of the board at 200% zoom. Then run the CAM job in
`PCBs/AdvancedBarebones.cam` to create the necessary files for manufacturing. We will submit a
panel of the class's designs for manufacturing, and in a subsequent lab, you will assemble and
test your PCBs. Thus, late submissions of this portion of the assignment will mean that you
lose points not only for this lab but also a subsequent one!!!!

**Upload the following PCB files to Canvas:**

  + the PDF of your board design
  + the Eagle CAD .sch and .brd files
  + manufacturing files - `your-file-name.GBL` (bottom layer), `your-file-name.GML` (board
  outline), `your-file-name.GTL` (top layer) and `your-file-name.TXT` (drill locations)

**Please do NOT zip these, just upload them individually. If you do not follow this instruction
I will deduct points from your score. (I use an automated script to extract these files.)**


