---
title: Lab 6
lab: 6
layout: default
group: labs-navigation
description: Serial Communications (SPI + I2C)
---

{::options parse_block_html="true" /}

## Lab #6: Using serial communications (SPI controlling an LED driver)

_This lab builds on the PWM and RGB LED work we've done earlier. The goal is
for you to be comfortable with SPI serial communications. This particular
device will be one foundation of the Simon game._

<div class="alert alert-danger" role="alert">
#### What should be turned in on Canvas?

  1. Your **commented** `rainbow_spi.c`, `rainbow_spi.h`, and `main.c` files. Specifically, the
comments should include any instructions that peer graders might need to compile and run your
code. Please include the proper interrupt compiler directives to ensure that both the TI and
gcc compilers will work.

  2. Answers to the questions in a text or otherwise broadly-accessible format.

#### The lab will be due March 23, 2021 at 11:59 AM. 

</div>

<div class="row">
<div class="col-md-3 col-sm-6 col-xs-6">
<figure class="figure">
<a href="APA102-Strip-Front.jpg"> <img src="APA102-Strip-Front.jpg"
    class="figure-img img-fluid rounded" alt="APA102 Strip"></a>
<figcaption class="figure-caption"><p>APA102 Strip.</p></figcaption>
</figure>
<figure class="figure">
<a href="simon.gif"> <img src="simon.gif"
    class="figure-img img-fluid rounded" alt="Simon Board"></a>
<figcaption class="figure-caption"><p>Simon Board with APA102.</p></figcaption>
</figure>

</div>
<div class="col-md-9 col-sm-12 col-xs-12">
#### Part 0: Get some APA102C RGB LEDs

In the old days, students would have to cut a piece of APA102 strip. **Starting
in 2021, use the prefabricated Simon PCB, which has 4 LEDs arranged in a circle.**

<div class="alert alert-danger" role="alert">
(**Not required starting in 2021!!!**) If you are wanting to solder the LED strips here's the
old instructions. **Take care to leave as much of the perforation intact on the entry side of
the strip.** (There are directional arrows which point in the direction of signal flow.) Solder
4 jumper wires to the exposed copper perforation holes as shown in the second picture to the
left. When looking from the front, the 4 perforations are `VCC, CLK, DATA, GND`. I found that
the easiest way to solder was to first apply lots of flux and then melt solder onto the
perforations, making sure that it actually had flowed onto them. Then, I pre-tinned the exposed
ends of the jumper wires.  Finally, I held the jumper wires in place on each of the
perforations and applied heat to reflow the solder. Once you get a good connection, you may
want to apply some epoxy resin over the wires.
</div>

#### SPI control

Let's review serial communications. Also take a look at the [documentation for the APA102
device](https://www.adafruit.com/product/2343).

<ol class="questions">
<li>What are the two categories that all forms of serial communication can be divided into?
In which category is the APA102?</li>
<li>What are two major differences between SPI and I2C serial communications? Which would be
best for controlling a large string of LEDs?</li>
<li>The APA102 uses a modified form of SPI to enable control of multiple LEDs without needing a
separate "chip select" line for each one. Briefly describe how it does this.</li>
<li>How big (in bytes) is the SPI message required to set the color of a single APA102? How
big (in bytes) is the SPI message required to set the color of each LED in a chain of 4
devices?</li>
</ol>

Now let's review the characteristics of the serial control hardware block
in your MSP430s, the USCI.

<ol class="questions" start="5">
<li>How many USCI blocks does the g2553 device have? What three protocols can be controlled by
the USCI?</li>
<li>On your launchpad, one of the serial modules is used to make a UART connection with the
host computer (via USB). Which pins and which USCI module are used for this? </li>
<li>Which pins can be used for the SPI clock and master-out-slave-in (MOSI)
data?</li>
</ol>

The Simon PCB has 4 APA102C RGB LEDs connected to a MSP430 using appropriate 
SPI clock and COPI lines. Three sample files are provide for you: [main.c](main.c),
[rgb_interface.c](rgb_interface.c), and [rgb_interface.h](rgb_interface.h). These files
demonstrate configuration of the USCI module so that the SPI clock frequency is within the
acceptable range for the APA102C, and the data communication clock edges are proper. These
examples also serve as an example of how to do modular programing. The current interface
for LED control should be abstracted at least one more level as part of this lab.

Write code to shift the LED colors through a rainbow (starting with red and
going to blue as in Lab 6). There should be 256 color "temperature" levels. **You should
modify the API so that the `main.c` function can simply call a `set_temperature(LED1, LED2,
LED3, LED4)` function. Then configure the logic in `main.c` such that each
LED should cycle one step behind the previous one so that the rainbow appears to
move upward. Use the `_16ms` watchdog timer interrupt for timing, and increment
the temperature by 16 each time step. (**Note that you will need to change from the _250ms
in the current file!**) 


</div>
</div>
