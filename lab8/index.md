---
title: Lab 8
lab: 8
layout: default
group: labs-navigation
description: Piezo buzzer and Simon PCB
---

{::options parse_block_html="true" /}

## Lab #8: Piezo Buzzers with PWM (and the Simon PCB)

<div class="alert alert-info" role="alert">
#### **There are three goals for this lab:**
  - To understand how PWM will affect sound production.
</div>

<div class="alert alert-danger" role="alert">
#### **What should you turn in?**
  1. Turn in your code as `pwm_songs.c` and answered questions. (_Canvas_)
  2. Turn in the Simon EAGLE and gerber files.

#### **What should be demoed?**
  1. You _may_ choose to demonstrate your Simon PCB or sketch.
  2. Demonstrate your functional sound sequence player.
</div>

**Part 1 of this lab will be due March 27, 2019 at 11:59 PM. **

#### Part 1: Playing tones via PWM

For the Simon midterm project, you'll need to generate sounds appropriate for button presses,
success, and failure. Wire a piezo buzzer to a PWM-capable pin. Your goal is to create a
set of functions (i.e., a library) that will allow you to play arbitrary sequences of tones at
potentially different speeds. A piezo buzzer produces sounds by transducing electrical fields
into motion using a piezoelectric material. They are good for higher frequencies, but not those
in the lower part of our hearing spectrum. Begin by experimenting with PWM and the buzzer. Set
your PWM carrier frequency to 440 Hz (an "A").

  1. What happens as you vary the duty cycle from 0 to 50%? What about from 50% to 100%?
  2.  Now build a timer module ISR to change the frequency every other cycle from 440 to 880 Hz
  and back. How does this sound? Can you explain?
  {: class="questions"}

Now, modify the code you built for question 2 to be general. "Sound strings" should be
specified as a sequence of frequencies (or periods) stored in an array, with a separate "tone
length" variable specifying how long each note should be played for. Note that because each
tone has a different frequency, keeping track of how long each has played is a slightly
nontrivial task (though you should be able to figure out a simple way of accumulating periods
properly to account for their different lengths). You should create a function with prototype
`void PlaySound(int* SoundString, int StringLength, int ToneDuration)` that initializes the
proper global state variables and starts the sound playing. The ISR should ensure that, once
started, the sound string is played once. You might want to create a special tone symbol which
corresponds to a "rest", to enable more complex sounds.

Create the proper sequences for the first lines of "Twinkle, twinkle little star", and "Mary had
a little lamb". Set up an infinite loop so that you play a sequence and then have quiet for a
few seconds. **You may use __delay_cycles for this part of this lab!** __Be prepared to
demonstrate how your code works, including playing the two sequences at different speeds.__

#### Part 2: Simon PCB - See midterm project for details


