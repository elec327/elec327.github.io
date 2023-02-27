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
success, and failure. There are piezo buzzers in the lab that can be connected to your
launchpad, or you can (wisely) use the Simon-Giveaway board. If you choose to use one from lab,
wire a piezo buzzer to a PWM-capable pin. Your goal is to create a set of functions (i.e., a
library) that will allow you to play arbitrary sequences of tones at potentially different
speeds. A piezo buzzer produces sounds by transducing electrical fields into motion using a
piezoelectric material. They are good for higher frequencies, but not those in the lower part
of our hearing spectrum. Begin by experimenting with PWM and the buzzer. Set your PWM carrier
frequency to 440 Hz (an "A").

  1. What happens as you vary the duty cycle from 0 to 50%? What about from 50% to 100%?
  2.  Now build a timer module ISR to change the frequency every other cycle from 440 to 880 Hz
  and back. How does this sound? Can you explain?
  {: class="questions"}

Now, modify the code you built for question 2 to be general. The way that I
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
few seconds. **You may use __delay_cycles for this part of this lab!** 

You will be graded on the following:
  - Code quality: use of multiple files, proper header calling, explanatory
    comments, PlaySound() function with proper prototype, reasonable
    architecture [about 40 pts]
  - Functionality: changing a variable or commenting/uncommenting a small number
    of lines of code should change which song is played, with comments
    indicating how to do this for the peer grader; songs sound correct [about
    40 pts]
  - Extra: rests/pauses between notes implemented and demonstrated [up to 10
    pts], LPM3 used [up to 5 pts], other special features



