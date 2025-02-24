---
title: Lab 7
lab: 7
layout: default
group: labs-navigation
description: Generating sounds using PWM
---

{::options parse_block_html="true" /}

### Lab #7: Generating sounds using PWM (100 pts)

<div class="alert alert-info" role="alert">
#### **There are two goals for this assignment:**

  - To write microcontroller code to generate different music using PWM
  - To write microcontroller code to generate sounds in response to button presses
  
</div>

<div class="alert alert-danger" role="alert">
#### Due Date: 3/14/2025
#### **What should be turned in?**
  - Your microntroller code which plays "Mary Had a Little Lamb" then transitions to responding
    to button presses
</div>

### Controlling sounds using PWM
In the template project for Lab 6, Timer Module TIMA1 is configured to drive the buzzer
on the Simon PCB. In this lab, you will integrate this buzzer into the Lab 6 concept.

When the duty cycle is set to 50%, PWM creates a square wave signal at the frequency
selected by the period register. Thus, In order to change the sound that is created,
you need to change the value both of the period register (to change the frequency)
and the duty cycle. On the Simon PCB, the buzzer is connected to TIMA1 channel C0.
In `lab6_helper.c`, the TIMA1 module is configured to count based on the main
SYSOSC BUSCLK (32 MHz) with a divider of 4, so at 8 MHz.

When the Lab 6 template code is run, the buzzer beeps briefly at startup. The code 
which configures the frequency of this beep is at the end of the TIMA1 initialization
in `lab6_helper.c`. **Note that both the period and the duty cycle need to be configured!**
```
    TIMA1->COUNTERREGS.LOAD = 3999; // Period is LOAD+1 - this is 8000000/4000 = 2kHz
    // HEADS UP: This sets the frequency of the buzzer!
    TIMA1->COUNTERREGS.CC_01[0] = (TIMA1->COUNTERREGS.LOAD  + 1) / 2; // half of load to make this a square wave
```

There are two other lines of code which are relevant. First, the following line in `lab6_helper.c`
enables the Timer Module's counting function (enables the counter to tick). This is the
standard way of effectively enabling the Timer Module's functioning, and in this case, it
turns the PWM, and thus sound, on.

```
    TIMA1->COUNTERREGS.CTRCTL |= (GPTIMER_CTRCTL_EN_ENABLED);
```

Second, at the top of the `lab6.c` function, we have the following lines of code which
disables the Timer Module counting, which turns off the PWM / sound.

```
    // let the buzzer run for 0.1 s just so we know it's there!
    delay_cycles(1600000);
    TIMA1->COUNTERREGS.CTRCTL &= ~(GPTIMER_CTRCTL_EN_ENABLED); // Disable the buzzer
```

### Your task in Lab 7
Your task in Lab 7 is twofold. 
 **First**, you should modify your button-is-depressed state
so that in addition to the corresponding button being lit, a button-specific-tone should play.

**Second**, you should add an initialization state to your state
machine from Lab 6. When in this initialization state, the song "Mary Had a Little Lamb"
should play repeatedly. You should transition out of the the initialization state 
when a button is pressed.

#### Adding sound to button-presses
Start with the state machine code you wrote for Lab 6. Modify the button depressed states. During 
the light off state, the PWM counter should be disabled to turn off sound. When a button is
depressed, set the frequency and duty cycle and enable the PWM counter to play the appropriate
sound. This should be fairly straight forward.

From this [website](https://www.waitingforfriday.com/?p=586), we have the suggestion that
the notes for Simon should be:

  - Green -- G4 391.995 Hz
  - Red -- E4 329.628 Hz
  - Yellow -- C4 261.626 Hz
  - Blue -- G3 195.998 Hz

Our buzzer has a fundamental frequency in the 4-8 kHz range. Frequencies outside this range
will induce more nonlinearities in the piezo mebrane. So using notes that are
two octaves higher (i.e., G6, E6, C6, and G5) will sound a bit less mechanical.

#### Mary Had A Little Lamb
In order to play music, you need the ability to specify both the frequency and duration of
the notes that you are playing. (Music comprises both tonal sound and silence!) If we notated
music as tuples of note and duration, if "q" is a quarter note, "h" is a half note, and 
"w" is a whole note, Mary Had a Little Lamb could be represented as:
```
(E,q) (D,q) (C,q) (D,q)   (E,q) (E,q) (E,h)  (D,q) (D,q) (D,h)  (E,q) (E,q) (E,h)
(E,q) (D,q) (C,q) (D,q)   (E,q) (E,q) (E,q) (C,q)  (D,q) (D,q) (E,q) (D,q)  (C,w)
```

Here is the suggested approach.
1. Create a pair of arrays corresponding to the notes and durations (or define a struct 
   and create a struct array). For notes, you can use the values you will want to put in
   the LOAD (and CC_01[0] registers) to make the correct tones.
2. Create a new "playing music" state for your state machine from Lab 6. When in this state,
   advance through the song array. This state will be similar to the "lights off" state
   that you made previously (checking each interrupt tick whether a button has been pressed).
3. When a button is pressed transition to the previous state machine from Lab 6.

Presumably quarter notes will correspond to something like 600-800 ms, while your interrupt
ticks will occur every 10 ms. Thus, the "music playing" state will need to implement a counter
that resets for each note and then counts down while the note should be being played.
In order to play a note, you will need to set the approriate values for the frequncy and 
duty cycle of the PWM. **Importantly**, when no tone should be being played (e.g., during the 
brief periods between notes or during a musical rest), you can disable the counter
using the CTRCTL register's enable/disable bit. 

### Bonus
The buzzer is also connected to a pin that can be controlled by the DAC output of the MSMPM0+.
Rather than driving the sounds with PWM square-waves, implement more complex waveforms like
sinusoids.
