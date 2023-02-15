---
title: Lab 4
lab: 4
layout: default
group: labs-navigation
description: PCB Design, full stop
---


{::options parse_block_html="true" /}


## Lab #4: RGB LED PCB Design and PWM

<div class="alert alert-info" role="alert">
#### There are two goals for this assignment:

  - To learn and carry out various aspects of printed circuit board design
  - To practice using Timer moldule-based PWM
  
</div>

<div class="alert alert-danger" role="alert">
#### What should be turned in?

  1. The EAGLE CAD .sch and .brd files for your design. (_Canvas_)
  2. The manufacturing files - `your-file-name.GBL` (bottom layer), `your-file-name.GML` (board
  outline), `your-file-name.GTL` (top layer) and `your-file-name.TXT` (drill locations).
  **Don't zip, compress, or otherwise combine these files!** (_Canvas_)

#### What should be demoed live?
  1. Your EAGLE CAD design, if desired.

#### Files are due Wednesday, February 15 at midnight.

</div>

#### Hardware PWM Quiz preview

The Launchpad MSP430 FR2433 does not have a built in RGB LED, though it does have two regular LEDs, which
are connected to pins P1.0 and P1.1. As we discussed in class, these correspond to the outputs for TA0.1, 
and TA0.2.  TA0.0 can't be used for PWM (which is why its presumably not broken out)!!! 

In class, we will write a program which cycles one LED in brightness then the other.
To do this, create an array of at least length 32 which contains LED1 and LED2 values. 

<!---
You can generate these using Python (e.g., the [matplotlib hsv
colormap](https://matplotlib.org/stable/tutorials/colors/colormaps.html)). Sample code in a Jupyter
notebook is [here](GenerateColorMap.ipynb). 
--->

Using the watchdog timer
in timer mode with the VLO and the `/8192` divider, cycle through the values. You will need to:
  - chose an appropriate PWM frequency
  - configure TimerA0 to run at this frequency
  - configure the appropriate output pins using the P1SEL
  - configure the appropriate output mode in the TA0CCLx registers
  - change the values of TA0CCR1 or T0xCCR2 based on the values in your array

You do not need to use LPM3 in this lab!

We will solve this in class and then have a quiz about it!

Some sample code for the launchpad that generates a heart-beat effect using PWM of the red channel
of the RGB led and the WDT for timing is in [template_code.c](template_code.c).

#### Designing a RGB Trinket PCB

<!--
By popular demand, this lab will feature a BGA-mounted accelerometer. The part we will use can be
found in the Digikey catalog:
[MXC4005XC](https://www.digikey.com/en/products/detail/memsic-inc/MXC4005XC/10322569), and the data
sheet is also [here](MXC400xXC_Rev.B_4-24-15.pdf). The accelerometer uses the I2C serial data
interface. If you look at the datasheet for the MSP430G2553, you'll see that only one of the serial
interface modules handles I2C, USCI B0. The pins which need to be connected are P1.6 (SCL - I2C
clock) and P1.7 (SDA - I2C data). The I2C bus requires pull-up resistors, which have been included
in the schematic for you.

-->
You will likely find useful to clone the [ELEC327 reposistory](https://github.com/ckemere/ELEC327) from
GitHub (if you have not done so yet).

Your task is to design a PCB with Eagle which includes the following parts from the ELEC327 library:
   - A [MSP430FR2411](https://github.com/ckemere/ELEC327/raw/master/Labs/Lab4/Datasheets/msp430fr2422.pdf)
   - A decoupling capacitor in 1206 package
   - A 1632 battery holder
   - One surface mount push button (TACTILE-6.2MM, which has slightly larger pads)
   - One RGB LED [IN-S128TATRGB](https://github.com/ckemere/ELEC327/raw/master/Labs/Lab4/Datasheets/IN-S128TATRGB_V1.0.pdf)
   - One header for programming (1x04-LOCK)
   - 4 1206 resistors (3 for current limiting the LED and one connected between _RST and VCC)

<div class="alert alert-info" role="alert">
   - Connect them properly so that the RGB LED can be driven by TA0.1, TA0.2, and TA1.1.
   - Connect one side of the switch to VCC, and connect the other end to an unused GPIO pin.
   - Put your initials in Text on either the Top or Bottom  (copper) layers.
</div>

Eagle comes with a good number of parts, but not all that you need. You can either
create a personal library for parts you make or add them to the ELEC327 library. Once you have
created/opened the library, start with the "symbol". Make sure to adequately labels the various
connections.  For reference, note that Digikey may provide an Eagle part design for the deisgn using an "Ultralibrarian"
script or a SnapEDA file. Feel free to make use of these, but you MUST DOUBLE CHECK the
design!!!! You shouldn't need to do this for this lab.

Next, then create a `.brd` file and route all of the connections. Keep in mind that the
battery package is solid and plastic, so you should not place any parts on top of it. One
solution is to put everything but the battery on one side of the PCB and the battery on the
other. Try to make the final board approximately square/circular, with a diameter of 20-40 mm.
After routing, check to make sure that it passes the electrical rule check (ERC) and design rule
check (DRC), using the DRC rules given in the `PCBS/AdvancedCircuitsBarebones.dru` rule file in the
github repository.

After you place your components and route traces, please put your initials or some other
identifying mark on the board **on either the top or bottom copper layer** (since this is a
barebones process, there is no silkscreen).{: style="text-decoration:underline"}

When you're finished, run the CAM job in `PCBs/AdvancedBarebones.cam` to create the necessary
files for manufacturing. We will submit a panel of the class's designs for manufacturing, and
in a subsequent lab, you will assemble and test your PCBs. Thus, late submissions of this
portion of the assignment will mean that you lose points not only for this lab but also a
subsequent one!!!!

### PCB Design Patterns and Anti-Patterns

A "Design Pattern" is an approach for a design task that will help you put small steps together
into a full hole. When routing the traces on a PCB, straight lines, symmetry, and right angles
are one possible pattern to follow. Note that this requires not just rotely following a rule -
think about how you will make the routes while placing the components and deciding their
rotation/orientation.

An "Anti-Design Pattern" is the opposite: rules of thumb that end up causing more problems than
they solve. For the PCB example below, I imagine the student placing the components then
thinking, "I will make the routes as straight as possible and introduce only minimal bends when
necessary to avoid vias." The result is a number of places where traces and vias are minimally
separated, or parallel traces travel very closely (minimal separation) for a long distance. A
piece of conductive junk ended up between two traces on this board, causing hours and hours of
confused debugging.


<div class="row">
<div class="col-md-6 col-sm-6 col-xs-6">
<figure class="figure">
<a href="PCB-Antidesign-Front.jpg"> <img src="PCB-Antidesign-Front.jpg" class="figure-img
img-fluid rounded" alt="PCB Example Front"></a>
<figcaption class="figure-caption"><p>Anti-design PCB front</p></figcaption>
</figure>
</div>
<div class="col-md-6 col-sm-6 col-xs-6">
<figure class="figure">
<a href="PCB-Antidesign-Back.jpg"> <img src="PCB-Antidesign-Back.jpg" class="figure-img
img-fluid rounded" alt="PCB Example Back"></a>
<figcaption class="figure-caption"><p>Anti-design PCB back</p></figcaption>
</figure>
</div>
</div>


**Upload the following PCB files to Canvas:**

  + the Eagle CAD .sch and .brd files
  + manufacturing files - `your-file-name.GBL` (bottom layer), `your-file-name.GML` (board
  outline), `your-file-name.GTL` (top layer) and `your-file-name.TXT` (drill locations)

**Please do NOT zip these, just upload them individually. If you do not follow this instruction
I will deduct points from your score. (I use an automated script to extract these files.)**


