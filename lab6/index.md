---
title: Lab 6
lab: 6
layout: default
group: labs-navigation
description: SPI Serial Output
---

{::options parse_block_html="true" /}

### Lab #6: SPI Serial Communication Output (100 pts)

<div class="alert alert-info" role="alert">
#### **There is one goal for this assignment:**

  - To learn to use serial communication protocols to send and receive information to/from peripherals
  - To build on our previous state machine logic to control RGB LEDs in a sequence and using button presses

  
</div>

<div class="alert alert-danger" role="alert">

#### Due Date: 3/5/2026
#### **What should be turned in?**

  - Your firmware code which controls RGB LEDs to change in sequence with the music and turn on/off with the button presses.
  - A short writeup that describes your state machine architecture and strategy for achieving this goal.

#### Rubric
_Simon board plays "Mary Had a Little Lamb" at start up, changing LED patterns in such a way that
each note corresponds to a distinct pattern of the 4 LEDs, then transitions to tones when buttons are pressed_

**Points related to light/music sequencing:**

  - 20 pts Displays 3 distinct 4-LED color patterns 
  - 10 pts Color patterns are consistently matched to notes across song
  - 10 pts Timing of color patterns is synchronized to notes
  - 10 pts During rests/internote silences LEDs are off (or change in otherwise meaningful, consistent way)
  - 10 pts Some documentation of how color patterns were chosen to be somehow meaningful

**Points related to buttons:**
  - 10 pts When any button is depressed during song mode, the music/light sequencing stops 
  - 10 pts When a button is depressed, the LED corresponding to that button lights up. 
  - 10 pts The LED for each button has a different color 
  - 10 pts In button mode, when the buttons are all released, no LED should be illuminated 


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
For this lab, we will stop at the first buffer layer, but if you reconfigure the code to use the FIFO or 
DMA (without leveraging the Driverlib libraries!!), you can get bonus points.

### Your task for Lab 6
For Lab 6, you will use the Simon PCB handed out for Lab 5.
Looking at the PCB, in addition to an MSPM0G3507 in the center, you can see 4 buttons
at the outside corners, and 4 SPI RGB LEDs in a square diagonally aligned with them.
In Lab 5, you programmed the PCB so that it initially played a song on the piezo buzzer,
then transitioned to a mode where depressing a button would cause a corresponding note to be played.

**Your task for Lab 6**
is to configure the PCB such that both of these modes are accompanied by displays on the 4 LEDs.
First, when the song is playing, the LEDs should change in time with the music, with each audio note
corresponding with a distinct set of colors for the 4 LEDs. Rests and internote periods should be
accompanied by all the LEDs being off or some other distinct, consistent display. 
Second, as before, when you depress one of the buttons, the mode should switch to button feedback.
Now, when the button is depressed, the LED corresponding to that button (i.e., the nearest one) 
should light up. Each LED should have a single, distinct color in this mode (i.e., the colors of the
Simon game).

The Workspace template Code Composer Studio project for Lab 6 extends the code provided for Lab 5.
Now, in addition to the `TIMG0` and `TIMA1` modules, the `SPI0` module is enabled and configured
to connect to the correct pins on the microcontroller. For pedagogical reasons, the code has been
made more modular. We've split all of the conceptual functions into their own files: `buttons.c/.h`,
`timing.c/.h` (for `TIMG0`), `buzzer.c/.h` (for PWM/`TIMA1`), `leds.c/.h` (for SPI LEDs); and the
main code is in `lab6.c`. (You will likely want to add a `state_machine.c/.h`.)

If you load the template code, you should see the same behavior as with the Lab 5 template 
(pressing a button sounds the piezo buzzer). In addition, the LEDs should be on, displaying 
four different colors, and the colors should change when the button is pressed.

<div class="alert alert-info" role="alert">

### Important differences

Explore the template code. Make sure to understand the `SendSPIMessage()` function, and how
it interacts with the `SPI` interrupt in `leds.c`, and what the return values mean.

The FIFO is configured and an interrupt enabled which will trigger when the data in the FIFO is moved
into the transmit shift register (indicating that another word should be written). The template code
leverages this interrupt to transmit a sequence of bytes that are stored in an array.
The SPI module keeps a pointer to the array being transmited (`uint16_t *spi_message`), an index
(`spi_message_idx`) and the array length (`spi_message_len`) as local/private global variables.
Notice how this abstraction level separates what is tracked globally (i.e., in other files) and what
data are maintained in local module context so that they are accessible to multiple functions.

**Critically**, this means that there are now two ISRs operating. 
 _Both of the ISRs will wake up the device from WFI()._
This means that our while(1) code has to become a bit more sophisticated. We will track the
two possible wakeup conditions and only tick the state machine if the timer is responsible
for waking us up. (We basically ignore the SPI interrupt as it's functionality is inside the
ISR.) To do this, the `timing.h` and `leds.h` expose public flag variables, `bool timer_wakeup`,
and `bool spi_wakeup`. We can use these to in our main loop to know which interrupt has triggered
WFI().

</div>

In order to change which LEDs light up in what colors, you will have to understand the SPI message 
protocol for these LEDs (described above), and pre-generate different SPI messages (or some sort of 
message generator function). You may choose whatever colors you like for each LED. **As before, you 
may assume that only one button will be depressed at a time.** (Note that adding extra functionality 
via multi-button presses is a bonus option for the midterm project, so you may choose to consider how
to do this.)

#### Bonus
 - Configure the SPI FIFO to be 4 deep rather than 1 deep, and adapt your code to use this functionality.
 - Note that the [Bonus](/bonus) web page describes the accelerometer on the Simon PCB. Using this device
   also involves SPI, but both read and write.

#### Supplemental
Some of you may be interested in doing more with the Simon PCB. The TI-provided "Driverlib" libraries
make it convenient to explore some of the other functions of the MSPM0+. A Driverlib version of the project
template is provided in the [Lab6-Driverlib.zip](Lab6-Driverlib.zip) archive. (Note that it does not
configure PWM for sound.)
