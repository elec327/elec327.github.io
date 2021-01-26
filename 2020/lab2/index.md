---
title: Lab 2
lab: 2
layout: default
group: labs-navigation-OLD
description: Timers and Soldering
---

{::options parse_block_html="true" /}


## Lab #2: _Timers and Soldering_

_The goals of this lab are two-fold. First, we aim for you to gain experience soldering small,
surface mount parts both for skill acquisition and in order to give you some background as you
begin PCB design in the next lab. Second, the goal is to begin learning about interrupts,
specifically by making use of the interrupt associated with one of the Timer modules._

_This assignment is due Friday, January 31, 2020 at **NOON**._

#### Part 1: Soldering a pendant
<div class="row">
<div class="col-md-3 col-sm-6 col-xs-6">
<figure class="figure">
<a href="Pendant.gif"> <img src="Pendant.gif" class="figure-img img-fluid rounded" alt="Pendant PCB"></a>

<figcaption class="figure-caption"><p>Lab 2 6-LED pendant PCB.</p></figcaption>

</figure>
</div>
<div class="col-md-9 col-sm-12 col-xs-12">
You need to solder all the components onto the PCB. New in 2020, we have a PCB oven in the lab,
and there are multiple copies of a solder-paste stencil for the PCB. To use it, carefully tape
the stencil over the PCB (lined up right, obvi!). Put a big blog of paste at one end, then
carefully use the squeegee to spread it over. Scrape well, but without scraping the paste off
the pads. Put excess solder paste back into the container! Then, carefully remove the stencil
and put all the surface mount parts on with tweezers (24 LEDs, 7 resistors, and 2 capacitors).
You'll need to solder the button and the battery holder by hand.

You may need to reference the
[board](https://github.com/ckemere/ELEC327/raw/master/Labs/Lab2/Pendant.brd)
and/or [schematic](https://github.com/ckemere/ELEC327/raw/master/Labs/Lab2/Pendant.sch)
files in order to know what other parts go where. In particular notice which
components are resistors, which are capacitors, and which are light emitting
diodes (LEDs). The LEDs in the outer ring all face in one direction and the LEDs in the inner
ring all face the opposite direction. If you get the direction reversed for all of them, you
can fix it in your code. (But if just a few LEDs are wrong, you'll have to take it off and
reverse them!)

1. **(Not scored!)** Either examine the PCB closely or look at the schematic for the pendant. Which GPIO pins
are connected to LEDs?

2. **(Not scored!)** In a normal, canonical (i.e., atomic), forward operating (i.e., not-breaking-down) diode,
which terminal does positive (conventional) current flow out of, cathode or anode? In the
pendant circuit, which pin(s) is this terminal connected to?

3. **(Not scored!)** What value (0 or 1) will result in the 12 o'clock diodes turning on?
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

4. Use a multimeter in lab to measure the threshold voltage of the supplied
LEDs.  How does this compare to the "forward voltage" found in the
[datasheet](http://www.digikey.com/product-detail/en/LTST-C150KRKT/160-1405-1-ND/386760). Why
might they be different if they are?

5. **(Not scored!)** Further examining the datasheet, what is the maximum value of forward current that you
should apply? What appears to be the recommended forward current level?

6. **(Not scored!)** Assume that you will be using one a CR2032 battery, which has a nominal voltage of 3V. What
voltage will appear on the output of the LED drive pins when they are on? (You can ignore the
voltage drop through the MSP430!).

7. Measure the voltage of a new CR2032 - what voltage do you find? After you build the circuit
and program the pendant, measure again with the device running. What value do you find
now?

8. Finally, assume that the threshold voltage of the diode is 2 V, and the MSP430 output pin
voltage is 3 V, and that the desired on current is 5 mA. What value of current-limiting
resistor should you use? What would be the minimum resistance such that the current is less
than the maximum (DC) specified in the data sheet?
{: class="questions" start="4"}

**Use the value of resistor which will achieve 5 mA on current along with the LEDs and a 47 K
pull-up resistor on the ~RST pin to finish the pendant.**

Here is a helpful video:

<iframe width="560" height="315" src="https://www.youtube.com/embed/7B_-qmJLfng"
frameborder="0" allowfullscreen></iframe>


#### Part 2: Using the Timer interrupts

The second part of the lab is to program the pendant to do something interesting. The pattern
that is desired is as follows:

  - One LED should be lit at any one time.
  - Which LED is lit should change every 333 ms.
  - The first LED that is lit should be the outside ring, 12 o'clock LED.
  - Which LED is lit should rotate around the clock (clockwise), in the outer ring, then switch
    at 12 o'clock to the inner ring, then back to the outer and so on. 
  - (Note that in the hour I spent on my demo PCB for the video above, I couldn't get it to
    start at 12 o'clock, so I realize that this is moderately non-trivial.)

Refer to the [skeleton code
file](https://github.com/ckemere/ELEC327/blob/master/Labs/Lab2/pendant.c) file. In order for it
to work, you will need to:
  - properly implement the `next_led()` function. This function sets the values of PORT1 and
    PORT2 that are appropriate for the next led to light up in sequence in the circle. Note
    that you might want to use `static` variables to maintain state from one function call to
    the next!

Once the code is functioning, examine it carefully and make sure you fill in comments on all
the lines that are marked. Additionally, think about the way the code is structured. In
principle, the code could all go in the interrupt, but in general it is best to have interrupt
service routines execute as quickly as possible.

##### Final modification for full functionality

After your code is functioning and you understand it well, make the appropriate changes so that
between changing LED values, you go into **LPM3** rather than LMP0.


To answer the following questions, you will need to refer to Chapters 5 and 12 of the User
Guide.

9. **(Not scored.)** How do you set a pin to be an output? What is the default mode for GPIO pins?

10. **(Not scored.)** If your main function begins with the instruction `BCSCTL2 = 0;` what will be the
frequency of the CPU clock (`MCLK`)? What will be the frequency of the submain clock (`SMCLK`)?
(Hint: you will also need to figure out what the default setting for the DCO is, and assume
that it is set.) (Second hint: the DCO in the MSP430g2553 is calibrated by default.)

11. Assume that the SMCLK has been configured to 1 MHz. Assume you are given the following
configuration of Timer A0: `TA0CTL = TASSEL_2 | ID_3 | MC_1 | TAIE;`. What register do you need
to set, and to what value in order to generate interrupts every 1 millisecond? Will you need
more/different ISR code?

12. Instead, assume you are given the following configuration of Timer A0: `TA0CTL = TASSEL_2
| ID_3 | MC_2;`. You can still achieve a 1 ms interrupt, but now you will additionally
be required to update the register in the previous question in your ISR. What is the proper
update command? (Hint: the right answer involves changing CCR0.) What would happen to
your program if you forgot to initialize the register in your main function and only modified
it in the ISR? 

13. In the timer ISR that you're given in the skeleton code, what is the purpose of this line
of code: `__bic_SR_register_on_exit(LPM0_bits);`? Where is the code for this function found?
{: class="questions" start="9"}

**Save your code as `pendant.c`. You will need to demonstrate your device running and walk
through your code comments and modifications for one of the course staff by the due date.
Upload your answered questions to the Google doc, and the code to Canvas.**
