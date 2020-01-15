---
title: Lab 1
lab: 1
layout: default
group: labs-navigation
description: Morse Code with Timers
---

{::options parse_block_html="true" /}

### Lab #1: Morse Code with Timers on the MSP430 (250 pts)

<div class="alert alert-info" role="alert">
#### **There are three goals for this assignment:**


  - To get CCS and/or Energia up and running. 
  - To become familiar with the _User Guide_ and datasheet (these will answer so many questions for you in the future). 
  - To learn to program an MSP430G2553 when it is separated from the Launchpad. 
  
</div>

<div class="alert alert-danger" role="alert">
#### **What should be turned in?**


  1. Your **commented** morse-code.c file. 
  2. Your answers to the questions (given at the end of this document) 
  3. A youtube link to a demo video of your code running after completing Part 3 of the lab.

</div>

#### Due Date: __Wednesday, January 22 at 6 pm__


#### Part 0: Installation (optional)

You are welcome to install TI's **Code Composer Studio** (CCS) on your own personal computers.
The updated Launchpad you are using this semester appears to be wel supported in the Ubuntu
version of CCS (as well as Windows). It is not yet known whether the beta OSX version is also
working well.

[**Energia**](http://energia.nu/) is a clone of the Arduino environment for the MSP430. We will
not use the Java-based approach used by Arduino, but the compiliing and device programming
components are still quite useful. Note that the Instructions for installing Energia can be
found at the project home page: [http://energia.nu/](http://energia.nu/). We will not
officially support Energia users in the class, however, we have found it to be quite usable in
a minimal sense. Specifically, by creating a new tab in a sketch with a ".c" extension, one can
write C-language code that is properly understood and compiled. You can then delete all the
stuff in the original sketch window (though it appears you have to leave the file there for
things to work). If you are going to use Energia, please make sure that you **do not** use the
Arduino-style sketch code but rather C-language or assembly.

[**msp430-gcc**](http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSPGCC/latest/index_FDS.html)
is a fork of the gcc compiler which has tools to compile, assemble, disasssemble, etc. MSP430
code. By itself, this can be a useful tool for understanding MSP430 code. With the addition of
the mspdebug package (available under Ubuntu Linux or Homebrew), code can also be uploaded to a
device.


#### Part 1: Verify CCS/Energia and Launchpad functionality and examine the skeleton code

Compile the included
[lab1\_skeleton.c](https://github.com/ckemere/ELEC327/blob/master/Labs/Lab1/lab1_skeleton.c)
file to verify that CCS is setup correctly. (In Energia, you will need to create a new
"sketch", add a tab with the name lab1.c or somesuch, erase the stuff in the first tab, and
then code away in the second ".c" one.) You should also read through this file: it shows the
minimum amount of code needed to run the MSP430 in an infinite loop. If you ever don't know
what some variable acronym means, look it up! A useful practice is right clicking the name and
going to "Open Declaration" (instructions for CCS are in red). For instance, in this file,
doing this on `CALBC\_1MHZ` brings you to:

`SFR\_8BIT(CALCBC1\_1MHZ)/\* BSCTL1 Calibration Data for 1 MHz \*/`

And inspecting `BSTCTL1` shows:

`SFR\_8BIT(BCSCTL1)/\* Basic Clock System Control \*/`

What, then, is the "clock system control" that is being referred to? Two resources you should
use extensively are the [MSP430x2xx Family User Guide](/assets/documents/slau144j_userguide.pdf)
and the [MSP430G2553 datasheet](/assets/documents/msp430g2553.pdf), both of which can be found
on the main 327 page (or by googling). The user guide explains how to use various functions or
registers common to most MSP430s, while the data sheet has register values and pin information
specific to the G2553. So, searching for "BCSCTL1" on the user guide takes you to Chapter 5 and
Chapter 24, from which you can figure out that this line will set the frequency of the DCO to a
calibrated 1 MHz.

On the web, you may notice a function called "\_\_delay\_cycles". You will find that
documentation of this function is somehwat lacking on the internet. If you look in the [MSP430
Optimizing Compiler Guide](assets/documents/slau132k.pdf), you will see that it is not a C
function, but rather an "intrinsic". In hindsight, if it's role is to delay the processor a
precise number of cycles that can range from 1 to some large number, it could not be a function
(because calling a function takes more than one cycle!). A compiler intrinsic is something like
a macro - it is something that is replaced by appropriate code at compile time. In this case,
\_\_delay\_cycles is marked as deprecated, no doubt because its use leads to poor quality code
because it blocks the processor but still runs at full power. In this class, you should
generally not write code which calls this function. 

#### Part 2: Understanding what the C compiler is doing
The goal of the compilation process is to turn a program written in a high level language into
machine code. 

**Please read** [this very interesting
writeup](https://www.theunterminatedstring.com/the-greedy-c-runtime/) about what code is
generated by a C compiler when it is naively called and after code size optimization is done.
We will discuss the operations of the compiler/assembler in class.

For those of you interested in understanding how compiler-to-opcode conversion might have
interesting effects in the modern day context,
[this](https://www.blackhat.com/docs/us-17/thursday/us-17-Domas-Breaking-The-x86-ISA.pdf) is an
interesting presentation from the 2017 BlackHat conference.

#### Part 3: Blinking a Morse Code Message

Using the P1.0 LED on your launchpad, blink a message in morse code. Look morse code up on
wikipedia to find the code for each letter and how to separate letters. Submit your code in a
separate file named `morse-code.c`. **Every line should have a meaningful comment and extra
comments are welcome!** A few specifications:

- A "unit" should be ¼ of a second.
- Use whatever clock and Timer mode you want.
- Organize your code such that to change the message, you only have to change one array at the
  beginning of your program (this should be an array of Morse code "dots" and "dashes").
- Be able to display either "SOS" or 3 other letters (i.e., your initials, the first 3 letters
  of your first name, etc), depending on which array is commented out.
- Your message should repeat.
- Consider repetitions of your message different words. This means that you should have 7
  "units" of off time between each repetition. If you want, this as well as spaces between
  letters and parts of the same letter can be hard coded into your array.
- To help yourself write clean code, you should use "BITx" whenever you do anything with a pin
  on the MSP430.
- You should use one of the timer interrupts for timing. Function LED flashing code is given in
  an example from the MSP-example code archive in the "Labs/Lab1/" directory of the [course
  repository](https://github.com/ckemere/ELEC327).
- **Continuing Bonus 1:** For those of you feeling particularly under-tasked by this lab, extra
  credit will be given for a second implementation of code that reads in the LED flashes and
  decodes the Morse code message. See Bonus page for more details.


#### Part 3: Moving it to a Breadboard

We'll be working with a lot of input/output devices in this class, and so it makes sense to be
able to program an MSP430 on a breadboard so that it can run independently. Make this
breadboard wiring clean, as you'll be testing a lot of circuits using it. To actually program
the MSP430 on a breadboard using the launchpad, you only need to:

1. Connect the TEST and RST pins on the EMULATION side of the launchpad to their respective
   pins on the MSP430 (these are labeled on the launchpad where the MSP430 itself is usually
   located).  
2. Connect Vcc and GND (or some independent battery, but for now use the launchpad's power) to
   their respective pins. For your convenience, jump these to the power lines on the
   breadboard. To ensure a clean power supply to the MSP430, connect a 10uF capacitor anywhere on
   the board between Vcc and GND.
3. Connect a pull-up resistor to the RST pin, as it is active-low. That is, connect a large
   resistor (47K from lab is fine) from the RST pin to Vcc, to ensure that its default state is
   high.

Now, reproduce your morse code circuit on the breadboard using LEDs and resistors in the lab.
There are, however, some differences you need to take into account – **see questions below!**
Wire the circuit on your breadboard, and successfully program it.

#### Demoing code

Over the course of the semester we will be developing a good schedule for demos. You will be
required to demonstrate your code to one of the course staff. You should be prepared to show
your code running on a breadboard, as well as changing the morse code message, reprogramming,
and showing the subsequent functioning. 

#### Questions (10 pts each):

Please reference your answers to one of the authoritative sources.

_Questions from week 1 of class:_
Load the code in [main.asm](main.asm) into CCS, compile it and load it onto your launchpad. (A
version that is Energia-compatible is in [main-energia.asm](main-energia.asm). Now 
answer the following questions: 

<ol class="questions" start="1">
<li><i>Understanding simple assembly code.</i>
(a) What does the code do? (b) How does it work (pseudocode)?
(Make sure to specify things like active pins, registers used and things like the period of operations!) 
</li>
</ol>

In CCS, you can see the disassembled code if you pause during debugging.

![Disassembly](Disassembly.png)

<ol class="questions" start="2">
<li><i>Understanding disassmbly.</i>
(a) Interpret the disassembled data. What does "c004: 40B2 5A80 0120" mean? (Specifically, what
does the "c004" refer to? What do the other numbers refer to? Why exactly are they those
numbers?  (b) What does "c014: 4034 C350" mean? What would it have been if the code had used
register R5 instead? What if the initialization had been #30000 instead of #50000?
(c) Why does assembly need to initialize the stack pointer in general? Is it necessary for this
program?

*Hint 1:* Remember that the MSP430 memory is little-endian. *Hint 2:* You'll want to make heavy
use of Table 3-12 ("Core Instruction Map") in the User Guide!
</li>
</ol>


_Questions from the skeleton code:_

<ol class="questions" start="3">
<li>In the Part 1 skeleton code, what is the frequency and period of the LED?</li>
</ol>

_Questions from bread-boarding:_

<ol class="questions" start="4">
<li>What is the forward voltage on the LED? What is its maximum forward current?</li>
<li>What is the supply voltage coming out of the MSP430? On the MSP430G2553, what is the
maximum current any one pin can output?</li>
<li>Using all this, what is the resistor value you should use to supply exactly this maximum
current? To be safe when using the MSP430, should you use a larger or smaller resistor?</li>
</ol>

**Upload your answers and your code to Canvas. Make sure to demo functionality by the deadline.**

