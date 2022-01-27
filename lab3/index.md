---
title: Lab 3
lab: 3
layout: default
group: labs-navigation
description: Timers, PWM, and Logic_and Soldering
---

{::options parse_block_html="true" /}


## Lab #3: _Timers, PWM, and Logic_

_The goals of this lab are two-fold. First, we aim for you to gain experience understanding the
difference between active modes and low power modes. Second, the goal is to begin learning about
interrupts, specifically by making use of the interrupt associated with one of the Timer modules._

_This assignment is due Friday, Febrary 4, 2022 at **3:30pm**._

<div class="row">
<div class="col-md-3 col-sm-6 col-xs-6">
<figure class="figure">
<a href="Display.jpg"> <img src="Display.jpg" class="figure-img img-fluid rounded" alt="Display PCB"></a>

<figcaption class="figure-caption"><p>Lab 3 35-LED display PCB.</p></figcaption>

</figure>
</div>
<div class="col-md-9 col-sm-12 col-xs-12">
The PCB has been pre-soldered for you, though if you want to add the battery pack or side-connection
headers, you can do that yourselves. 

In order to do the lab, you will need to reference the [board](Display.brd) and/or [schematic](Display.sch)
files in order to know how the LEDs are connected to the MSP430. These PCB design files are done in
EAGLE cad, which you can download from the Autodesk website for free. You will need to learn how to
use this software later in the course, so it's a good idea to begin familiarizing yourself with it.
In the meantime, screen shots of the schematic can also be found [here](Schematic P1.png) and
[here](Schematic P2.png).

1. **(Not scored!)** Either examine the PCB closely or look at the schematic for the pendant. Which GPIO pins
are connected to LEDs?

2. **(Not scored!)** In a normal, canonical (i.e., atomic), forward operating (i.e., not-breaking-down) diode,
which terminal does positive (conventional) current flow out of, cathode or anode? In the
pendant circuit, which pin(s) is this terminal connected to?

3. **(Not scored!)** What values for the rows and columns (0 or 1) will result in the bottom left
and top right diodes turning on?
{: class="questions"}

</div>
</div>

Precise modeling of the current/voltage characteristic of a diode is complicated, but
important for a number of applications (such as detecting light with a photo diode). A
very simple model of a diode switches from infinite resistance to zero resistance at the
"threshold voltage". Thus, when on, the current through the diode must be limited. A resistor
in series with the diode serves to limit the current, and you will see such a resistor in the
pendant circuit. In order to find the proper value of this resistance, you need to know
something about the LED and also something about the rest of the circuit.

4. **(Not scored!)** Use a multimeter in lab to measure the threshold voltage of the supplied
LEDs.  How does this compare to the "forward voltage" found in the
[datasheet](http://www.digikey.com/product-detail/en/LTST-C150KRKT/160-1405-1-ND/386760). Why
might they be different if they are?

5. **(Not scored!)** Further examining the datasheet, what is the maximum value of forward current that you
should apply? What appears to be the recommended forward current level?

6. **(Not scored!)** Assume that you will be using one a CR2032 battery, which has a nominal voltage of 3V. What
voltage will appear on the output of the LED drive pins when they are on? (You can ignore the
voltage drop through the MSP430!).

7. **(Not Scored!)** Measure the voltage of a new AAA battery - what voltage do you find? After you build the circuit
and program the pendant, measure again with the device running off 2 AAAs. What value do you find now?

8. **(Not Scored!)** Finally, assume that the threshold voltage of the diode is 2 V, and the MSP430 output pin
voltage is 3 V, and that the desired on current is 5 mA. What value of current-limiting
resistor should you use? What would be the minimum resistance such that the current is less
than the maximum (DC) specified in the data sheet?
{: class="questions" start="4"}

Here is a helpful video:

<iframe width="560" height="315" src="https://www.youtube.com/embed/7B_-qmJLfng"
frameborder="0" allowfullscreen></iframe>

#### Low Power Modes

Pursuant to helping you doing the lab, the [skeleton code](lab3_skeleton.c) will set up the MSP430
so that the ACLK is being driven by the VLO (which you remember runs ~12 kHz), and TimerA0 is being
driven by the ACLK. **These two conditions are required for the Timer to continue to function when the
device is in LPM3 (CPU and DCO off!).** The display PCB is designed as a matrix - each LED is
addressed by a row and a column. This means that in order to display an arbitrary pattern, the LEDs
will have to be rapidly scanned, and rely on the eye to integrate the result into a static image.
The skeleton code presents a simple design in which the display is operated by cycling through each
column of LEDs. Program the skeleton code onto your Display PCB. Verify that it works. Comment line 31
and uncomment line 30 (`P1OUT = row;`), and verify that this changes the functionality so that
either one LED per column or the whole column is lit when the code cycles through that column.

9. (This Question **IS** Scored!) Use the Energy Trace software to measure the power consumption of
the display PCB when it is programmed to light one LED per column. Change the two lines of code that
enter and exit LPM3 to instead enter and exit LPM0. What is the difference in averge current
consumed? What is the primary culprit for the residual current in LPM3? (Why does it still consume
so much current?)

10. (This Question **IS** Scored!) Return the code to go in and out of LPM3. Now change the code
so that each cycle an entire column is lit (commenting line 31 and uncommenting line 30). How much
current is consumed on average now? Change the code so that only 4 LEDs are lit each cycle. Can you
estimate a linear relationship between the number of LEDs used and the current consumption? What is
the slope (in units of mA per LED)? What is the intercept? What is responsible for the intercept?
{: class="questions" start="9"}


#### Lab Specification

The first part of the design is to implement a numeric display using the PCB. You should decide what
LEDs should be lit for the numbers 0 through 9, and arange your code so that you can specify a
number and the display will show it. (Hint: Use an array of arrays to store the set of row bits that
is required for each column of a particular numeric character. Cycle the index of the inner array to
the row output port.)

The second part of the lab is to implement a seconds counter. The display should increment from 0 to
9 in ten seconds. The easiest way to do this is to use the watchdog timer. The initial
[test](initial_test.c) code used to program your Display PCBs has an example of this where the WDT
interrupt happens at a high rate. You can also use a secondary CCR interrupt from TimerA0 or use
TimerA1 for this (but remember to configure whatever timer you use to use the ACLK!).

The third part of the lab is to implement PWM intensity for the numbers you are displaying. This
will be somewhat complicated, as it means adding an additional counter which will decide whether or
not a given LED should be turned on during a particular clock cycle. I belive that 12 levels of
intensity should be possible without the display flickering. **Speification:** You should be able to
set the intensity level by changing one numeric variable.

The final **specification** is that you should have another variable that determines whether your PCB is
displaying the numbers 0-2 (i.e., hours), the numbers 0-6 (i.e., tens of minutes or seconds), or the
numbers 0-9.

**Save your code as `display.c`. You will need to demonstrate your device running and walk
through your code comments and modifications for one of the course staff by the due date.
Upload your answered questions to the Google doc, and the code to Canvas.**
