---
title: Project 1 - Midterm
lab: 11
layout: default
group: labs-navigation
description: Midterm Project 
---

{::options parse_block_html="true" /}

## Midterm Project: Creating "Simon"

<div class="alert alert-info" role="alert">
#### **There are three goals for this project:**

  - To design and implement a somewhat complex embedded system that is evaluated by your peers
    based on principles like usability and enjoyment.
  - To construct, organize and implement a multi-module code project.
  
</div>

<div class="alert alert-danger" role="alert">
#### **How will it be evaluated?**

  1. The device will be presented and demo'ed to the class (you will need evals from at least 2 
  other students and the professor or TAs).
  2. In class demos will be April 5th, 2018.
  3. Please turn in your self-criticism score (rubric given below), your code, and the size of
  your board. 

  **Rubric:** (10 pts each (code is 20 pts), 100 total) 
  - Ergonomics-Shape (is it comfortable to hold and play?)
  - Ergonomics-Debouncing (does it register just one button press when you press a button?)
  - Gameplay-Timeout (does it game over after a while if no button is pressed?)
  - Gameplay-MisplayingError (does it game over if the wrong button is pressed?)
  - Gameplay-Win (does it do something special when the player wins?)
  - Gameplay-Random (does it play a different sequence each timei, including after power cycles?)
  - Style-Animations (are there animations for start/win and lose/game-over?)
  - Style-SoundLight (do lights and sounds work well together and convey information?)
  - Well-commented, logical code architecture (does the architecture make sense? are there good
    comments?, functions (libraries?) used intelligently?) - 20 pts

</div>


The game ["Simon"](https://en.wikipedia.org/wiki/Simon_(game)) is a classic toy which tests the
working memory of the player. For the midterm project, you will create a small,
coin cell-operated Simon game. This will involve PCB design and fairly involved firmware to
acheive an enjoyable user experience. In addition, you will be invited to add some sort of
interesting feature beyond the Simon game. In the past, this has ranged from simple animations
to a mode in which the device becomes a music sequencer.

Here's a video from Vitor Azevedo Andriotti (Spring 2015) showing a Simon board in action.

<iframe width="560" height="315" src="https://www.youtube.com/embed/nrsBVdJFrKc"
frameborder="0" allowfullscreen></iframe>

#### Rules for the The ELEC327 version of the Simon game

In our variant of Simon, the point of the game is to learn a sequence of *M* button presses.
Each button corresponds to one of the LEDs and to one frequency of PWM tone. On the *n*th turn,
the device plays the first *n* elements of the sequence. So one tone/LED on turn one, two on
turn two, etc. The pattern of the *n-1* elements of the sequence are the same as the previous
turn. Each turn, after the sequence is played, the player must push the appropriate buttons to
recreate the sequence. If they do it correctly, the game proceeds to the *n+1*th turn. If they
make an error or wait too long (measured by the time since the last button press), they lose.
Winning corresponds to playing the full *M*-element sequence. If the player loses, the device
should play a "Game Over - Lost" animation that continues until it is reset. Similarly, if the
player wins, the device should play a "Game Over - Won" animation until it is reset (e.g., by
power cycling or pressing a button). 

Details:

  - On initial boot, the devices should play either one of the "Game Over" animations or a
    third novel animation. Pushing any button should then start the game.
  - Sequences should be random each game (make sure your random routine produces a different
    value on startup!)
  - When a button is pressed, the appropriate LED should flash (and tone should sound).
  - The timeout period should not be a constant. Rather, each time a player pushes a button, a
    new timeout should start. Thus, a timeout of 1-2 s is appropriate.
  - Errors should result in immediate game over (i.e., button presses should be processed
    immediately).
  - You should make the maximum sequence size adjustable. For your video, sequences of length 5
    are appropriate.
  - You are expected to implement software debouncing (and don't use capacitors with switches!)


#### The Simon PCB

The first thing you must turn in is a layout of the Simon PCB. There is a hard upper limit on
size of 3 in. x 3 in., but the physical board will be graded on a combination of small size and
ergonomics. Parts:

  + 4 buttons (with capacitors just in case you can't figure out software debouncing)
  + 4 APA102 SPI RGB LEDs (probably either in a row or in a circle)
  + Power switch
  + AAA battery pack (mounted to the back - not connector polarity)
  + Piezo buzzer (wired up for PWM - see Lab 8)

These parts are given in the
[Simon.sch](https://raw.githubusercontent.com/ckemere/ELEC327/master/Labs/Midterm/Simon.sch)
Eagle CAD schematic in the ELEC327 git repository. 

*Note that you are not **limited** to the listed parts. You can add additional parts from the
list above or other lab supplies, but if you do, you are expected to demo their utility as part
of your project!*


