---
title: Midterm Project
lab: 11
layout: default
group: labs-navigation
description: Midterm Project
---

{::options parse_block_html="true" /}

## Midterm Project (2025): Creating "Simon"

<div class="alert alert-info" role="alert">
#### **There are three goals for this project:**

  - To design and implement a somewhat complex embedded system that is evaluated by your peers
    based on principles like usability and enjoyment.
  - To construct, organize and implement a multi-module code project.
  
</div>

<div class="alert alert-danger" role="alert">
#### Due date: 3/26/2025

#### **How will it be evaluated?**

  1. The code for your Simon game will be submitted via canvas. Please include
  only code files and a "README.txt" that describes (a) briefly your code architecture
  and approach, (b) the score that you think you should get based on the rubric
  below, and (c) how to access or run any special features. 

  2. In addition to peer grading, Prof. Kemere or the lab assistants may run your code 
  on their boards for evaluation. Your score for the final project will be based on the
  rubric below.

  3. Students from the class will be given the chance to evaluate
  based on a simpler rubric. These scores will not be used for grading, but
  course bonus will be assigned based on the final ranking of Simon programs.
  Additionally, a small bonus will be given for each of your peer's Simon games
  you evaluate.

  4. We will grade in class on **March 26, 2025**.

 #### Rubric: (10 pts each, 150 total) 
  1. Power-on animation: When powered on, does the game display an animation that involves 
     changing patterns of the lights?
  2. Power-on animation: Does the power on animation also include changing sounds?
  3. Power-on animation: Does the power-on animation transition to game play when a button is pressed?
  4. Random-Gameplay: Is the first element displayed random, including between power cycles?
  5. Gameplay-ButtonFeedback: When a button is pressed during play, does the **light** asssociated with 
     that button track the button press, i.e., turn on when it is depressed and turn off when it 
     is released?
  6. Gameplay-ButtonFeedback: When a button is pressed during play, does the **sound** asssociated with 
     that button track the button press, i.e., turn on when it is depressed and turn off when it 
     is released?
  7. Gameplay-Timeout: Does the game transition to a "loss" state if no button is pressed within some period during the response?
  8. Gameplay-MisplayingError: Does the game transition to a "loss" state if a wrong button is pressed during a response?
  9. Gameplay-Win Animation: If the player wins (correctly responds to a sequence of length 5), does
     the game display an animated sequence of **lights**? (This can be the same as the power on sequence but must 
     be different than the gameplay-lose animation.) 
  10. Gameplay-Win Animation: Does the win animation also include **sounds**?
  11. Gameplay-Lose Animation: If the player loses (times out or responds incorrectly), does
      the game display an animated sequence of **lights**? (This can be the same as the power on sequence but must 
      be different than the gameplay-win animation.) 
  12. Gameplay-Lose Animation: Does the lose animation also include **sounds**?
  13. Can the length of a sequence required to win be changed by changing no more than one line of code?
  14. Well-commented, logical code architecture (does the architecture make sense? are there good
      comments?, functions (libraries?) used intelligently?) - 20 pts

</div>


### Background

The game ["Simon"](https://en.wikipedia.org/wiki/Simon_(game)) is a classic toy which tests the
working memory of the player. For the final project, you will create a small,
coin cell-operated Simon game. This will involve PCB design and fairly involved firmware to
achieve an enjoyable user experience. In addition, you will be invited to add some sort of
interesting feature beyond the Simon game. In the past, this has ranged from simple animations
to a mode in which the device becomes a music sequencer.

Here's a video from Tiger Yang (Spring 2019), showing a Simon board in action along with a number of bonuses.

<iframe width="560" height="315" src="https://www.youtube.com/watch?v=DYyrkACy08Q"
frameborder="0" allowfullscreen></iframe>

#### Rules for the ELEC327 version of the Simon game

In our variant of Simon, the point of the game is to learn a sequence of *M* button presses.
Each button corresponds to one of the LEDs and to one frequency of PWM tone. On the *n*th turn,
the device plays the first *n* elements of the sequence. So one tone/LED on turn one, two on
turn two, etc. The pattern of the *n-1* elements of the sequence are the same as the previous
turn. Each turn, after the sequence is played, the player must push the appropriate buttons to
recreate the sequence. If they do it correctly, the game proceeds to the *n+1*th turn. If they
make an error or wait too long (measured by the time since the last button press), they lose.
Winning corresponds to playing the full *M*-element sequence. If the player loses, the device
should play a "Game Over - Lost" animation that continues until it is reset (e.g., by
power cycling or pressing a button). Similarly, if the player wins, the device should play 
a "Game Over - Won" animation until it is reset. 

Details:

  - On initial boot, the devices should play either one of the "Game Over" animations or a
    third novel animation. Pushing any button should then start the game.
  - Sequences should be random each game (make sure your random routine produces a different
    value on startup!)
  - When a button is pressed, the appropriate LED should flash (and tone should sound).
  - The light and sound associated with the button should be displayed/played as long as the button 
    is held down, and then should stop. (So _not_ like in the example video below where they 
    play for a constant length of time regardless of how long the button is pressed for.)
  - The timeout error should calculated relative from when a player **depresses** the previous button. 
    A timeout of 1-2 s is appropriate.
  - An erroneous button press should result in a game over either when the button is depressed
    or when it is released. 
  - You should make the maximum sequence size adjustable by changing at most one line of code.

Here's a nice video from Joshua Harper (Spring 2022) showing a Simon board in action.

<iframe width="560" height="315" src="https://www.youtube.com/watch?v=6odXYgCBaWI"
frameborder="0" allowfullscreen></iframe>

#### Helpful Tips
Much of Simon can be pieced together by using code developed from previous labs. To help you,
 - Build off of an accepted solution for Lab 7.
 - An example random number generator is given in [simon_random.c](simon_random.c)
and [simon_random.h](simon_random.h). 
 - Remember that the LFSR random number generator can be used to both generate the 
   button/light sequences **and** check the playback (if you store the seed used 
   and start over during the button pressing)
 - Here's a gist that shows how to turn on the TRNG module and grab a random
   number from it - [https://gist.github.com/kemerelab/a8de90811a15cb982f5fb3d0e2410c70](https://gist.github.com/kemerelab/a8de90811a15cb982f5fb3d0e2410c70)


Physical information is given in the
[ELEC327 Simon repository](https://github.com/ckemere/ELEC327/tree/master/PCBs/Simon-2025)
Eagle CAD schematic in the ELEC327 git repository. 



