---
title: Lab 6
lab: 6
layout: default
group: labs-navigation
description: Piezo buzzer and Simon PCB
---

{::options parse_block_html="true" /}

## Lab #6: Piezo Buzzers with PWM (and the Simon PCB)

<div class="alert alert-info" role="alert">
#### **There are three goals for this lab:**
  - To understand how PWM will affect sound production.
</div>

<div class="alert alert-danger" role="alert">
#### **What should you turn in?**
  1. Turn in your code in at least two .c files (and headers as needed) and answered questions. (_Canvas_)

#### **What should be demoed?**
  1. If you choose to use the Simon-Giveaway board, the graders can run it on their boards.

  2. Alternatively, you may choose to make a video showing functionality and describing your
  code (which will allow you to highlight anything special in your code).
</div>

**This lab will be due March 1, 2023 at 2 pm. **

#### Part 1: Playing tones via PWM

For the Simon midterm project, you'll need to generate sounds appropriate for button presses,
success, and failure. You will begin to use your Simon board in this lab, developing code
to play sounds on its buzzer. If you look at the [schematic](https://github.com/ckemere/ELEC327/blob/07ee4e43732058bed81754431f8a43ebf6909a19/Labs/Midterm/Simon-2023.sch) and [board](https://github.com/ckemere/ELEC327/blob/07ee4e43732058bed81754431f8a43ebf6909a19/Labs/Midterm/Simon-2023.brd) files on github,
you'll see that the piezo buzzer is connected between pins `P2.5` and `P2.1`. If you look
at the [datasheet](https://github.com/ckemere/ELEC327/blob/07ee4e43732058bed81754431f8a43ebf6909a19/Documents/msp430g2553.pdf) for the MSP430G2553, you'll see that `P2.5` corresponds to the Timer module PWM output `TA1.2`.
In order to produce sound on the buzzer, you'll need to output a PWM signal to `P2.5` and
actively connect `P2.1` to either GND or VCC by configuring it's GPIO information.
**Remember - to play SOUND with PWM, you need to change the frequency rather than
the duty cycle.** (The duty cycle can always be half of the square wave frequency.)

Your goal is to create a set of functions (i.e., a
library) that will allow you to play arbitrary sequences of tones at potentially different
speeds. A piezo buzzer produces sounds by transducing electrical fields into motion using a
piezoelectric material. They are good for higher frequencies, but not those in the lower part
of our hearing spectrum. 

Example code in [piezo_example.c](piezo_example.c) is set up to play through a C-major chord using
the watchdog timer to switch between the different notes. Program your board with this code.
You may notice that the level of volume produced by the buzzer is fairly high. If you
re-configure `P2.1` as an INPUT, and set the pull-up or pull-down resistor, the volume will
be lowered!

For this lab, you'll need to modify the example code to be general. The way that I
think of music is as a series of notes, each with a corresponding duration. So a
function that would play a song would have a prototype that looks like `void
PlaySound(int *Notes, int* Durations, int Length)` (remember that arrays don't
have a built in length in C!). Alternatively, one could think of the music as
having a fundamental duration (e.g., one eighth note), and the song would be
specified as a series of eighth notes at different frequencies. Then, the
prototype would look like `void PlaySound(int *Notes, int Length, int
Duration)`, where the `Duration` parameter is the length in time of the
fundamental unit. While the `Notes` in either case are probably properly thought
of as frequencies, you can choose to specify them as periods for runtime
efficiency. You should implement one of these two prototypes, or, if you have a
very good (and well-commented reason), another one.

A few notes:
  - Advanced musicians will recognize that in a lot of music there are tiny
    implicit rests between individual notes that allow, for e.g., two quarter
    notes versus an individual half-note to have different sounds. Implement
    this for extra credit.
  - Because each tone has a different frequency, keeping track of how long each
    has played is a slightly nontrivial task (though you may be able to
    figure out a simple way of accumulating periods properly to account for
    their different lengths). Alternatively, you can use the second timer module
    to help with note duration.
  - `PlaySound()` should initialize the proper global state variables and start 
    the sound playing. An interrupt-driven process should ensure that, once
    started, the sound string is played only once. 
  - You should organize your code into two or more source code files, one with
    the `main()` function (and maybe other stuff), and one with `PlaySound()`
    and maybe other stuff.

Create the proper sequences for the first lines of "Twinkle, twinkle little star", and "Mary had
a little lamb". Set up an infinite loop so that you play a sequence and then have quiet for a
few seconds. 

As always, you will demonstrate your code to your peers in class, changing which song is
played (ideally by some simple configuration in your code). Code should be turned in on Canvas.


