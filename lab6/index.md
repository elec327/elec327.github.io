---
title: Lab 6
layout: default
group: labs-navigation
description: Serial Communications (SPI + I2C)
---

{::options parse_block_html="true" /}

## Lab #6: Using serial communications (SPI controlling an LED driver)

_This lab builds on Lab 4. The goal is for you to be comfortable with SPI serial
communications that will be the foundation of the Simon game._

#### Part 0: Solder a APA102C SPI-controlled RGB LED to a breakout board

<div class="row">
<div class="col-md-3">
<a href="/assets/images/APA102C_5050Breakout.jpg" class="thumbnail">
<img src="/assets/images/APA102C_5050Breakout.jpg" alt="APA102 soldered onto breakout
board"></a>
</div>
<div class="col-md-9">
Solder one of the SPI-controlled LEDs to a "5050" breakout board. Additionally, solder pin
headers to the 6 pins so that you can plug the breakout board into a solderless breadboard. To
make sure the pins are parallel it can help to hold it in the breadboard while soldering.
**Caution:** if you apply too much heat you'll melt your breadboard!
</div>
</div>

#### Part 1: SPI control

Let's review serial communications. Also take a look at the [documentation for the APA102
device](https://www.adafruit.com/product/2343).

<ol class="questions">
<li>What are the two categories that all forms of serial communication can be divided into?
In which category is the APA102?</li>
<li>What are two major differences between SPI and I2C serial communications? Which would be
best for controlling a large string of LEDs?</li>
<li>The APA102 uses a modified form of SPI to enable control of multiple LEDs without needing a
separate "chip select" line for each one. Briefly describe how it does this.</li>
<li>How big (in bytes) is the SPI message requried to set the color of a single APA102? How
big (in bytes) is the SPI message required to set the color of each LED in a chain of 4
devices?</li>
</ol>

Now lets review the characteristics of the serial control hardware block
in your MSP430s, the USCI.

<ol class="questions" start="5">
<li>How many USCI blocks does the g2553 device have? What three protocols can be controlled by
the USCI?</li> 
<li>On your launchpad, one of the serial modules is used to make a UART connection with the
host computer (via USB). Which pins and which USCI module are used for this? </li>
<li>Which pins can be used for the SPI clock and master-out-slave-in (MOSI)
data?</li>
</ol>

Connect your APA102C to the MSP430 using the appropriate SPI clock and MOSI lines. Configure
the USCI module so that the SPI clock frequency is within the acceptable range for the APA102C,
and the data communication clock edges are proper. Practice sending SPI commands until you
figure out how to change the LED color (and, optionally, intensity). Convert your Lab 4 code to
now drive the APA102C according to the temperature (and randomness). Turn this code in as
`spi_led_temperature.c`. **BONUS:** You can continue to do the "heartbeat" functionality to
receive a bonus. However, now you should do this using the "global intensity" bits. Make a
video showing your APA102C being controlled by the temperature of the launch pad as in Lab 4.

**Turn in the answers to the questions, your code, and a video URL on Canvas.**

