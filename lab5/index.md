---
title: Lab 5
lab: 5
layout: default
group: labs-navigation
description: Generating sounds using PWM
---

{::options parse_block_html="true" /}

# Lab #5: Generating sounds using PWM (100 pts)

<div class="alert alert-info" role="alert">
## **There are two goals for this assignment:**

  - To write microcontroller code to generate different music using PWM
  - To write microcontroller code to generate sounds in response to button presses
  
</div>

<div class="alert alert-danger" role="alert">
## Due Date: 2/28/2026
## **What should be turned in?**
  - Your microntroller code which plays "Mary Had a Little Lamb" then transitions to responding
    to button presses
  - A short writeup document (in TXT or PDF format) which describes the code architecture (i.e. state machine)
    and addresses issues described in the rubric below.
  - Please upload using the https://granule.rice.edu:5000 submission server

#### Rubric
_Simon board plays "Mary Had a Little Lamb" at start up, then transitions to tones when buttons are pressed_

**Points related to music:**

  - 10 pts Plays 3 notes in a song pattern at startup
  - 10 pts 3 notes are correct for Mary Had A Little Lamb
  - 10 pts Whole note duration is twice the half not duration, which itself is twice the quarter note duration
  - 10 pts Notes are distinct, with a short pause in between
  - 10 pts Note durations include the short pause (the half note -- including the pause -- is twice that 
    of the the quarter note -- including the pause)
  - 10 pts Some documentation of music can be easily changed

**Points related to buttons:**
  - 10 pts Pressing any button stops the Mary Had a Little Lamb
  - 10 pts When each button is depressed, a tone plays. 
  - 10 pts Tones stop when all buttons are released.
  - 10 pts Each button causes a distinct tone to be played

</div>

### Controlling sounds using PWM
In the template project for Lab 5, Timer Module TIMA1 is configured to drive the buzzer
on the Simon PCB. In this lab, you will integrate this buzzer into the Lab 5 concept.

When the duty cycle is set to 50%, PWM creates a square wave signal at the frequency
selected by the period register. Thus, In order to change the sound that is created,
you need to change the value both of the period register (to change the frequency)
and the duty cycle. On the Simon PCB, the buzzer is connected to TIMA1 channel C0.
In `hw_interface.c`, the TIMA1 module is configured to count based on the main
SYSOSC BUSCLK (32 MHz) with a divider of 4, so at 8 MHz.

When the Lab 5 template code is run, the buzzer beeps briefly at startup. The code 
which configures the frequency of this beep is at the end of the TIMA1 initialization
in `hw_interface.c`. **Note that both the period and the duty cycle need to be configured!**
```
    TIMA1->COUNTERREGS.LOAD = 3999; // Period is LOAD+1 - this is 8000000/4000 = 2kHz
    // HEADS UP: This sets the frequency of the buzzer!
    TIMA1->COUNTERREGS.CC_01[0] = (TIMA1->COUNTERREGS.LOAD  + 1) / 2; // half of load to make this a square wave
```

There are two other lines of code which are relevant. First, the following line in `hw_interface.c`
enables the Timer Module's counting function (enables the counter to tick). This is the
standard way of effectively enabling the Timer Module's functioning, and in this case, it
turns the PWM, and thus sound, on.

```
    TIMA1->COUNTERREGS.CTRCTL |= (GPTIMER_CTRCTL_EN_ENABLED);
```

Second, at the top of the `lab5.c` function, we have the following lines of code which
disables the Timer Module counting, which turns off the PWM / sound.

```
    // let the buzzer run for 0.1 s just so we know it's there!
    delay_cycles(1600000);
    TIMA1->COUNTERREGS.CTRCTL &= ~(GPTIMER_CTRCTL_EN_ENABLED); // Disable the buzzer
```

### Your task in Lab 5
Your task in Lab 5 is twofold. 
**First**, conceptually, you can start with your button state machine code from Lab 3. 
For this lab, we do not care about long-presses or short-presses. Instead, the goal is 
that whenever a button is pressed (not bouncing), you should play a tone that corresponds 
to the button being depressed.

**Second**, similarly to how there were two highest-level states for the clock (ticking or setting),
there should be two highest-level states. In the first, which is active upon reboot,
your PCB should play the song "Mary Had a Little Lamb" repeatedly. When any button is depressed,
you should transition out of the the initialization state into the button-tone state described
above.

#### Adding sound to button-presses
When a button is depressed, set the frequency and duty cycle and enable the PWM counter to 
play the appropriate sound. (**Hint:** Begin by adding your state machine code to the lab 
template. Remove the long-press states, and modify the short-pressed state to enable PWM.)

From this [website](https://www.waitingforfriday.com/?p=586), we have the suggestion that
the notes for Simon should be:

  - Green (SW1) -- G4 391.995 Hz
  - Red (SW2) -- E4 329.628 Hz
  - Yellow (SW3) -- C4 261.626 Hz
  - Blue (SW4) -- G3 195.998 Hz

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
2. Create a new "playing music" state. When in this state, cycle through the song array. 
3. When a button is pressed transition to the button-tone state.

Presumably quarter notes will correspond to something like 600-800 ms, while your interrupt
ticks will occur every 10 ms. Thus, the "music playing" state will need to implement a counter
that resets for each note and then counts down while the note should be being played.
In order to play a note, you will need to set the approriate values for the frequncy and 
duty cycle of the PWM. **Importantly**, when no tone should be being played (e.g., during the 
brief periods between notes or during a musical rest), you can disable the counter
using the CTRCTL register's enable/disable bit. 

Full rubric credit for the song requires that the song be easily changed to a different
musical score.

##### Internotes
One more requirement for the notes for this lab is that sounds should not slur from one note to
another. This means that there needs to be a gap of silence between notes. Full credit for this
requirement requires that the whole note **including the internote gap** is four times as long as
the quarter note **including the internote gap**. (This makes it harder to just paste on to
existing code.)

### Bonus
1. The buzzer is also connected to a pin that can be controlled by the DAC output of the MSMPM0+.
Rather than driving the sounds with PWM square-waves, implement more complex waveforms like
sinusoids.

2. Optimize your code for lower power. Configure the SYSOSC to use a 4 MHz frequency for both 
your code and timer. Implement at GPIO interrupt to additionally trigger wakeups with button
state changes and timer G0 wakeups. Optimize the timer interrupt for debouncing.
Ensure that you go into SLEEP while waiting for input. Measure power consumption before
and after these changes and demonstrate the improvement.


### Further notes

The schematic for the Simon PCB can be found on the github - [https://github.com/ckemere/ELEC327/tree/master/PCBs/Simon-2026-JLC](https://github.com/ckemere/ELEC327/tree/master/PCBs/Simon-2026-JLC).
Of critical importance, the GPIOs conneted to the buttons are PA23, PA24, PA25, and PA26.
The Workspace template Code Composer Studio project [https://github.com/ckemere/ELEC327/tree/master/Workspace/Lab5](https://github.com/ckemere/ELEC327/tree/master/Workspace/Lab5) helps you out by configuring the GPIO for 
those 4 buttons, as well as 2 modules: 

  - TIMG0 - configured to use the LFCLK for a timer interrupt 
  - TIMA1 - configured to drive PWM on the buzzer pin.  (You will use this for Lab 8.) 

In order to program the Simon PCB, remove the 10 jumpers that connect across the top of the Launchpad.
These connect an XDS110 debugging interface at the top of the PCB to the microcontroller at the bottom.
Instead, you need to connect these pins to the Simon PCB. The programming pins are labelled - you will
need to connect `GND`, `VCC`=`3V3`, `NRST`, `SWDIO`, and `SWCLK`. (The other ones we won't connect allow
the debug interface to pass through UART communications to the PC and enable some sort of boot-strap loader.)
The video below shows a jumper cable connecting the Launcpad and a Simon PCB.

<div class="row">
<div class="col-md-10 col-sm-10 col-xs-10">
<figure class="figure">
<video class="figure-img img-fluid rounded" alt="Pin Mux Table" controls autoplay loop>
<source src="LaunchpadAndSimon.mp4">
</video>
<figcaption class="figure-caption"><p>Video of Launchpad Connected to Simon PCB</p></figcaption>
</figure>
</div>
</div>