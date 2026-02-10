---
title: Lab 4
lab: 4
layout: default
# group: labs-navigation
description: PCB Design With KiCAD
---

{::options parse_block_html="true" /}

## Lab #4: PCB Design With KiCAD (100 pts)

<div class="alert alert-info" role="alert">
### **There are two goals for this assignment:**

  - To learn to navigate the Schematic and PCB layout tools in KiCAD
  - To lay out your own PCB with KiCAD
  
</div>

<div class="alert alert-danger" role="alert">
### Due Date: 2/13/2026
### What should be turned in?

  1. Just the KiCAD `.kicad_pcb` file for your design. (_Canvas_)

### How will you be assessed?
  - We will run DRC on the individual PCB layout files, and should not find errors.
  - We will look for your initials to be on either the top or bottom copper layers.
  - We will measure the board area. If it is less than 3 square inches, you will receive full credit.

</div>

### Designing a RGB "Mood Ring" PCB

You will likely find useful to clone the [ELEC327 reposistory](https://github.com/ckemere/ELEC327) from
GitHub (if you have not done so yet). In the `PCBs/ELEC327-Library` subdirectory, there are KiCAD symbol and 
footprint libraries that you should add to your Symbols and Footprints libraries. It is also possible to add
3D designs for parts - this requires adding a path variable, and then specifying the parts relative to
this path variable. (**TODO:** Write a HOWTO document for this step.)

For this lab, your task is to design the PCB corresponding to a provided schematic design. The design
includes the following parts:
   - A [MSPM0C1103](https://www.ti.com/lit/gpn/mspm0c1104-q1) ([datasheet and TRM here](https://github.com/ckemere/ELEC327/tree/master/Documents/MSPM0-C-Series))
   - Necessary RC filter for NRST pin
   - Power decoupling capacitors
   - A CR1220 battery holder
   - One tactile push button 
   - One "NeoPixel" digitally-controlled RGB LED
   - A negative thermal coefficient [thermistor](https://datasheets.kyocera-avx.com/nb21-nb12-nb20.pdf) and resistor divider
   - One header for programming and debugging (1x5)

Critically, the project on Github includes two copies - through-hole and surface mount - of the button and LED parts. The through-hole parts are easier to solder, but may take up more PCB space. You should pick the ones
you want to use, and delete the other one from the schematic and PCB before you route the traces.

The 47K and 10K resistors and the 3 capacitors will be made available either as 1206_3216 or 0603_1608 SMD
parts. Again, the larger SMD parts (which are currently specified in the design) are easier to solder but take
up more space. If desired, you may also choose to change the footprints for these 6 items to the smaller 0603
package.

After you place your components and route traces, please put your initials or some other
identifying mark on the board **on either the top or bottom copper layer** (since this is a
barebones process, there is no silkscreen).{: style="text-decoration:underline"}


<div class="alert alert-info" role="alert">
   - Make sure to pick one each of the LED and button parts.
   - Make sure that you run DRC on your PCB and that it passes without rule errors **OR** unconnected items!
   - Put your initials in Text on either the Top or Bottom  (copper) layers.
</div>

#### DRC and Manufacturing
To facilitate manufacturing in the Advanced Circuits Barebones process, 
[AdvancedCircuits_8mil.zip](AdvancedCircuits_8mil.zip) contains a minimal KiCAD project that
sets the appropriate layers as well as "Design Rule Check" (DRC) rules. The DRC rules include that
the minimum sizes for traces and spacing is "8 mil" (0.008 inches), and the minimum drill size is
"10 mil". You can set these rules for your PCB by doing the following:
  - Unzip the AdvancedCircuits project.
  - Open your project, and open the PCB in the PCB editor.
  - Select the "Board Setup" option from the "File" menu.
  - At the bottom of the dialog box, there is an option to "Import Settings From Another Board".
  - In the resulting dialog, select the AdvancedCircuits_8mil pcb that you have unzipped
  - Click on the "Select All" option in the bottom left corner, and then "Import Settings".

<!--


When you're finished, if you're interested in seeing what manufacturing files look like, you can generate them.
To generate the manufacturing files:
  - Select "File Menu"->"Fabrication Outputs"->"Gerbers (.gbr)"
  - Click "Plot" to generate three "Gerber" files (for our PCBs, these describe the copper layers and the board outline)
  - Note that for the panel, we will check the "Disable aperture macros" option, and uncheck the "Include netlist options",
    but if you do fabrication elsewhere, these options are likely acceptable.
  - Click the "Generate Drill Files..." button.
  - Note that for the panel, we will select the "PTH and NPTH in a single file", "Use alternate drill mode", and "Keep Zeros"
    options.
-->


### Turning in
We will submit a panel of the class's designs for manufacturing, and in a subsequent lab, you will assemble 
and test your PCBs. Thus, late submissions of this portion of the assignment will mean that you lose 
points not only for this lab but also a subsequent one!!!! We will regenerate the manufacturing files from
your PCB files, so the only thing you need to submit is the `.kicad_pcb` file from your project.

We will peer-review each others PCB designs, and you will have a chance to revise your design. Your final
grade will depend on a combination of the initial peer reviewed version and the final PCB.


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
