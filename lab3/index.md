---
title: Lab 3
lab: 3
layout: default
group: labs-navigation
description: Processing Input
---

{::options parse_block_html="true" /}

# Lab #3: Processing GPIO Input - Setting the Clock
--- (100 pts)

<div class="alert alert-info" role="alert">
#### **Goal for this assignment:**

  - To develop more complex input driven state machines
  
</div>

<div class="alert alert-danger" role="alert">
#### Due Date: 2/7/2025
#### **What should be turned in?**

  1. Your **commented** lab3.c file. Your grade will be assigned based on
     functionality as defined in the Detailed Specifications below.

</div>

## Overview

In Lab 1, you built a simple LED-based clock display using GPIO.  
In Lab 2, you replaced software delays with hardware timers and PWM to improve the power consumption of the clock.

In this lab, you will add **user interaction** to your clock by implementing a **button-controlled time-setting interface**. You will use the pushbutton connected to **PB8 (GPIO Port B, pin 8)** to enter and exit clock-setting modes, and to adjust the displayed time.

This lab introduces:
- GPIO input configuration
- Button debouncing
- Long-press vs short-press detection
- Increasing the complexitt of the finite state machine construct to include input
- Extending without breaking existing timing behavior

---

## Hardware

You will continue to use the custom ELEC 327 PCB from Labs 1 and 2.

Relevant circuitry for this lab:

- **Pushbutton** connected to **PB8 (GPIOB pin 8)**
- Hour and minute LED outputs from Labs 1 and 2
- Hardware timer and PWM configuration from Lab 2

No additional hardware is required.

---

## Starting Point

Start from your **Lab 2 working codebase**.

Your program should already:
- Use a hardware timer interrupt to maintain time
- Drive the hour and minute displays correctly
- Use PWM (or timer-driven logic) to update LED brightness or sequencing

If your Lab 2 code does not work correctly, a solution will be provided Wednesday Feb 4, 2026.

---

## Functional Requirements

### 1. Clock Operating Modes

Your firmware must support **three operating modes**:

1. **Normal Clock Mode**
2. **Hour-Set Mode**
3. **Minute-Set Mode**
4. **\[Extra-Credit\] Brightness-setting Mode**

---

### 2. Button Behavior

The pushbutton on PB8 must behave as follows:

#### Long Press
- A **long press** is defined as holding the button continuously for **≥ 1 second**
- Long presses are used to **change modes**

#### Short Press
- A **short press** is a press shorter than the long-press threshold
- Short presses are used to **increment the time value** when in a setting mode
- Critically, a short press should be at least 5 ms long. (This is equivalent to debouncing!)

---

### 3. Mode Transitions

| Current Mode       | Long Press Action              |
|--------------------|--------------------------------|
| Normal Clock       | Enter Hour-Set Mode            |
| Hour-Set Mode      | Enter Minute-Set Mode          |
| Minute-Set Mode    | Return to Normal Clock Mode    |

---

### 4. Visual Feedback

To provide clear user feedback:

- **Normal Clock Mode**
  - Clock operates normally
  - No flashing indicators

- **Hour-Set Mode**
  - The **hour hand/location must flash**
  - The minute display remains steady
  - Clock time does **not advance automatically**

- **Minute-Set Mode**
  - The **minute hand/location must flash**
  - The hour display remains steady
  - Clock time does **not advance automatically**

- **\[Extra-Credit\] Brightness-Set Mode**
  - Both **hour hand/location and minute hand/location flash**
  - Hour and minute locations remain steady
  - Clock time does **not advance automatically**

Flashing should be implemented using the state machine mechanism (do **not** use blocking delays).

---

### 5. Adjustment

- In **Hour-Set Mode**:
  - Each **short press** advances the hour by 1
  - Hour values should wrap correctly (e.g., 12 → 1)

- In **Minute-Set Mode**:
  - Each **short press** advances the minute by 1 LED (5 minutes)
  - Minutes should wrap correctly (e.g., 55 → 0)

It is strongly recommended (but not required) that the change in LED position should be actuated
when the button is released. __However it is implemented, the position should not advance when
the user changes the mode using a long-press.__

When exiting Hour-Set or Minute-Set Mode, the newly set time becomes the active clock time.

**Extra Credit:** For extra credit, add a third setting mode after hour and minute. In this third
mode, the user will change the LED brightness setting. 
   - Each **short press** in brightness mode increases the brightness by one level. 
   - There should be at least 15 levels of brightness.
   - After maximum brightness is reached, another short press should cycle the brightness back to the minimum level.
   - The minimum brightness level should be visible (in the dark)

---

### 6. Button Debouncing

Your firmware must handle button debouncing as part of the state machine architecture. 
You may assume that "real" button presses last longer than 100 ms, and that glitches when the button is depressed
longer than this duration will not occur.

---

## Implementation 

As with Labs 1 and 2, the final implementation must be a state machine, where the next state
depends on the current state. However, now, the next state will depend on the current state 
AND the input. We will modify the Lab 2 template code together during class to develop a Lab 3
template main() function.

In the final implementation, you are strongly encouraged to construct your state machine in
such a way that the the logic is handled heirarchically using state variables corresponding
to the operating mode and internal substates. This will enable you to separate button handling 
logic from clock setting logic from clock operating logic from PWM logic.

---

## Testing Checklist

Before submitting, verify:

- ☐ Clock runs normally in Normal Clock Mode  
- ☐ Long press enters Hour-Set Mode  
- ☐ Hour indicator flashes in Hour-Set Mode  
- ☐ Short presses increment the hour correctly  
- ☐ Long press enters Minute-Set Mode  
- ☐ Minute indicator flashes in Minute-Set Mode  
- ☐ Short presses correctly differentiate between bounces (too short) and actual short presses
- ☐ Short presses increment the minute correctly  
- ☐ Long press exits back to Normal Clock Mode  
- ☐ Button presses are reliable (no false triggers)

---

## Submission

Submit the following:

1. **Source code**
   - Clearly organized and commented
   - State machine logic must be identifiable
   - Single zip file as in Lab 3

2. **README (brief)**
   - Description of your state machine
   - Explanation of how long vs short presses are detected
   - Any known limitations or assumptions

---




