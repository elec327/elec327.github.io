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

<div class="row">
<div class="col-md-10 col-sm-10 col-xs-10">
<figure class="figure">
<a href="ChainedRGBLEDs.png"> <img src="ChainedRGBLEDs.png" class="figure-img
img-fluid rounded" alt="Pin Mux Table"></a>
<figcaption class="figure-caption"><p>Chainable SPI RGB LEDs</p></figcaption>
</figure>
</div>
</div>

Internally, each LED works by peeling off the first instruction that is sent to it, then forwarding on
any additional ones. Here's the message encoding system:

<div class="row">
<div class="col-md-10 col-sm-10 col-xs-10">
<figure class="figure">
<a href="LEDProtocol.png"> <img src="LEDProtocol.png" class="figure-img
img-fluid rounded" alt="Pin Mux Table"></a>
<figcaption class="figure-caption"><p>Protocol for Chainable SPI RGB LEDs</p></figcaption>
</figure>
</div>
</div>

The all-zeros word at the beginning of the data sequence serves to inform the LED 
that an instruction is starting. While it decodes the next word, it forwards on an all-zeros word to the
next LED. Each LED in the chain ends up being one clock cycle delayed from the previous one. Thus the 
final word of all-ones at the end of the data sequence is merely there to ensure that enough clock ticks
are given to drive the final color command all the way to the end of the chain.

While you could fairly easy "bit-bang" this protocol by sending out data bit wise using GPIO commands,
most microcontrollers include hardware Serial Modules that simplify this process for you. The MSPM0+ is
no exception. In general, a hardware serial module works by providing TX (transmit) and RX (receive) 
registers. Once the module is configured and enabled, the data in the TX register is automatically clocked 
out, one bit at a time, while data is simultaneously clocked into the RX register. As described in class,
this is not the end of the story - these registers are usually buffered, so that the firmware can load
the next word to be transmitted into the module while the current word is being transfered (and copy the
previously received word out while the current word is being received). In the MSPM0+, we additonally have
a multi-word FIFO queue that feeds from/to these buffer registers. AND, to top it off, we can load/empty that
queue using DMA. So it is possible to automatically transfer long strings of data without involving the CPU.

However, for this lab, we will stop at the first buffer layer. The template project configures SPI module


