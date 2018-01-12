---
layout: default
title: Bonus
group: navigation
---

## ELEC 327: Digital Systems Laboratory (Spring 2018) Bonus Projects


---

### Accelerometer and LED circle board

  1. **[1 - 2 points]** - implement a clock. This will require that you properly solder the
  MSP430 and 3 shift register chips. The aesthetics of the clock and code will
  determine total scorer. Example questions: is there a second hand that ticks? a separate hour
  and minute hand?  is there some sort of PWM-like intensity modulation? does the device
  calibrate and use the VLO for low power?

  1. **[2 points]** - implement a tilt sensor in which the LED closest and furthest from the ground
  light up. The button should be used to make the device sleep/wake up. This will require that
  you (a) properly solder the MSP430 and 3 shift register chips to drive the LEDs and (b)
  interface with the accelerometer to read out the gravity vector, and (c) appropriately
  compute its direction.

  2. **[up to 2 points]** - derive optimized integer routines for (1) so that the update speed can be
  fast. Obviously, this also requires doing (1).

  3. **[up to 5 points]** - do something cool that links motion to the LEDs.


---

### Lab 1 Bonus - Decode Morse Code

**[2-6 points]** - **MVP (2 points):** after implementing the [Lab1 morse code blinking
project](lab1/), connect an input GPIO pin of a second MSP430 to the LED driving pin on the
first one (you'll presumably also need to connect the ground lines). Track the signal on this
pin to infer dashes, dots, and spaces. Decode these to characters, which can be viewed in
memory in the debugger. **Extra points:** (a) Implement a serial interface to see the translated
characters. (b) Figure out how to synchronize the clock over a large range of frequencies. You
can assume that the message is limited to 3-4 letters and repeats for a long time. (c) Use a
photodiode or other light sensor to get the signal rather than a wire.

---

