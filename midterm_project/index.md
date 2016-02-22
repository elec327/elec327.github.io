---
title: Project 1 - Midterm
layout: default
group: labs-navigation
description: Midterm Project - Simon
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

  1. The device will be presented and demo'ed to the class (you will need evals from at least
  10 other students) and the professor.
  2. You should turn in your final firmware code and a youtube link to a demo video of your
  code running.  **Specifically, your demo video should show you playing through to a win,
  running the "Game Over - Win" animation, and then pushing a button to restart and then
  playing through but making a mistake to generate the "Game Over - Loss" animation.**

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
  - Sequences should be random each game!
  - When a button is pressed, the appropriate LED should flash (and tone should sound).
  - The timeout period should not be a constant. Rather, each time a player pushes a button, a
    new timeout should start. Thus, a timeout of 1-2 s is appropriate.
  - Errors should result in immediate game over (i.e., button presses should be processed
    immediately).
  - You should make the maximum sequence size adjustable. For your video, sequences of length 5
    are appropriate.

The specifications above will correspond to a "B" grade. To achieve a higher grade, you should
add additional functionality. Some potential suggestions:
  
  - Implement software debouncing (and don't use capacitors with switches!)
  - Allow the user to select the level of difficulty - the timeout period and/or speed of initial
    sequence playing. You could implement this by which button is used to start the game after
    a reset.
  - Implement the reset functionality by requiring multiple buttons to be pressed
    simultaneously
  - Add double or triple button presses to the pattern
  - Do something interesting with the LEDs (i.e., using the color channels creatively or
    specifying interesting patterns)
  - Track fastest performance (i.e., how fast the entire game goes) and reward the player for
    beating their previous best
  - Use the PCB for something else in addition to Simon (e.g., a different game, a music
    sequencer) that is executed depending on some startup condtion.


#### The Simon PCB

The first thing you must turn in is a layout of the Simon PCB. There is a hard upper limit on
size of 3 in. x 3 in., but the physical board will be graded on a combination of small size and
ergonomics. Parts:

  + 4 buttons with 1206 capacitors in parallel
  + 4 APA102 SPI RGB LEDs (probably either in a row or in a circle)
  + Power switch
  + AAA battery pack (mounted to the back - not connector polarity)
  + Piezo buzzer (wired up for PWM - see Lab 7)

These parts are given in the
[Simon.sch](https://raw.githubusercontent.com/ckemere/ELEC327/master/Labs/Midterm/Simon.sch)
Eagle CAD schematic in the ELEC327 git repository. 

*Note that you are not **limited** to the listed parts. You can add additional parts from the
list above or other lab supplies, but if you do, you are expected to demo their utility as part
of your project!*


