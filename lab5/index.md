---
title: Lab 5
lab: 5
layout: default
group: labs-navigation
description: PCB Design With KiCAD
---

{::options parse_block_html="true" /}

### Lab #5: PCB Design With KiCAD (100 pts)

<div class="alert alert-info" role="alert">
#### **There is one goal for this assignment:**

  - To learn how to design a PCB
  
</div>

<div class="alert alert-danger" role="alert">
#### Due Date: 2/27/2025
#### What should be turned in?

  1. The KiCAD .kicad_sch and ..kicad_pcb files for your design. (_Canvas_)
  2. The manufacturing files - `your-file-name.GBL` (bottom layer), `your-file-name.GML` (board
  outline), `your-file-name.GTL` (top layer) and `your-file-name.TXT` (drill locations). (**TODO**)
  **Don't zip, compress, or otherwise combine these files!** (_Canvas_)

#### How will you be assessed?
  - We will run DRC on the individual PCB layout files, and should not find errors.
  - We will look for your initials to be on either the top or bottom copper layers.
  - We will measure the board area. If it is less than 2.75 square inches, you will receive full credit.

</div>

#### Designing a RGB Trinket PCB

For this lab, you have the choice of making a PCB design with "through hole" components

You will likely find useful to clone the [ELEC327 reposistory](https://github.com/ckemere/ELEC327) from
GitHub (if you have not done so yet). In the `PCBs/ELEC327-Library` subdirectory, there are KiCAD symbol and 
footprint libraries that you should add to your Symbols and Footprints libraries.

Your task is to design a PCB with KiCAD which includes the following parts from the ELEC327 library:
   - A [MSPS003F4](https://www.ti.com/lit/ds/symlink/mspm0c1104.pdf) ([datasheet][mspm0c1104.pdf])
   - Necessary RC filter for NRST pin
   - Power decoupling capacitors
   - A 2032 battery holder
   - One tactile push button 
   - One common anode RGB LED, and 3 current limiting resistors
   - One slide potentiometer
   - One header for programming and debugging (2x5)
   - One buzzer

Starter projects with all the parts can be found in two starter projects:
   - If you want to use mainly 0805 surface mount parts [Lab5_SMD.zip](Lab5_SMD.zip)
   - If you want to use larger 1210 surface mount and through hole parts [Lab5_THT.zip](Lab5_THT.zip)

<div class="alert alert-info" role="alert">
   - Connect the RGB Led properly so that the RGB LED can be driven by TIMG14 PWM outputs.
   - Connect the Buzzer so that it can be driven by the BEEP output.
   - Connect the slide potentiometer so that the center point can be read out by an ADC input.
   - Put your initials in Text on either the Top or Bottom  (copper) layers.
</div>

<!--
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

-->

After you place your components and route traces, please put your initials or some other
identifying mark on the board **on either the top or bottom copper layer** (since this is a
barebones process, there is no silkscreen).{: style="text-decoration:underline"}

When you're finished, run the CAM job to create the necessary files for manufacturing. We will 
submit a panel of the class's designs for manufacturing, and in a subsequent lab, you will assemble 
and test your PCBs. Thus, late submissions of this portion of the assignment will mean that you lose 
points not only for this lab but also a subsequent one!!!!

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
