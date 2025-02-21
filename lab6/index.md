---
title: Lab 6
lab: 6
layout: default
group: labs-navigation
description: Serial Communication Protocols and Button Logic
---

{::options parse_block_html="true" /}

### Lab #6: Serial Communication Protocols (100 pts)

<div class="alert alert-info" role="alert">
#### **There is one goal for this assignment:**

  - To learn to use serial communication protocols to send and receive information to/from peripherals
  - To build on our previous state machine logic to control RGB LEDs using button presses

  
</div>

<div class="alert alert-danger" role="alert">
#### Due Date: 2/328/2025
#### **What should be turned in?**

</div>

### Controlling an RGB LED using SPI
The SPI serial protocol is used for high-ish speed synchronous serial communication with many peripherals.
In this lab, we'll be using a special case of an SPI peripheral, one that merely receives data from its
controller, rather than also sending data back. The "APA102C" family of digitally controllable LEDs are
configured in such a way that the control signals can be chained.

![ChainedRGBLEDs.png](ChainedRGBLEDs.png)


