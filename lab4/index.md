---
title: Lab 4
lab: 4
layout: default
group: labs-navigation
description: PWM
---


{::options parse_block_html="true" /}


## Lab #4: RGB LED PWM

<div class="alert alert-info" role="alert">
#### There is one goal for this assignment:

  - To practice using Timer moldule-based PWM
  
</div>

<div class="alert alert-danger" role="alert">
#### What should be turned in?
#### What should be demoed live?

#### Files are due Wednesday, February 15 at midnight.

</div>

#### Hardware PWM

The Launchpad MSPM0+ G3507 has a built in RGB LED, which is connected to channels PB22, PB26, and PB27.
Let's look at the PinMux table in the data sheet.
<div class="row">
<div class="col-md-10 col-sm-10 col-xs-10">
<figure class="figure">
<a href="PinMuxTable.png"> <img src="PinMuxTable.png" class="figure-img
img-fluid rounded" alt="Pin Mux Table"></a>
<figcaption class="figure-caption"><p>Pin Mux Table - RGB Entries</p></figcaption>
</figure>
</div>
</div>

We see that while we have a couple of options for Timer module PWM outputs on PB26 and PB27, but only one
for PB22 (and it's a different one). The G3507 has two different kinds of Timer modules, TIMA and TIMG. 
The TIMA modules have 4 PWM outputs, but the TIMG variants only have two. And unfortunately, our RGB 
LED pins are not connected to pins that allow us to control it's color output with just one Timer module.
Some sample code for the launchpad that configures two timers and drives a heart-beat effect using PWM
is in this template project - [Lab4.zip](Lab4.zip).


#### Your task is 
Your task for this lab is to create an array of RGB colors and have the RGB LED cycle through the colors 
of the rainbow. You can generate these using Python (e.g., the [matplotlib hsv
colormap](https://matplotlib.org/stable/tutorials/colors/colormaps.html)). Sample code in a Jupyter
notebook is [here](GenerateColorMap.ipynb). 

Using a Timer interrupt as in Lab 3, cycle through the values of a rainbow. You will need to:
  - chose an appropriate PWM frequency and configure the two timer modules to run at this frequency
  - configure the CC ("capture compare") registers for the 3 channels to cycle through colors based
    on the values in your array

You do not need to use STANDBY mode in this lab. In fact, the available timers will not allow it!
