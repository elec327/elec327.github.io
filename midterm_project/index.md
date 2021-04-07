---
title: Midterm Project
lab: 11
layout: default
group: labs-navigation
description: Midterm Project
---

{::options parse_block_html="true" /}

## Midterm Project (2021): Creating "Simon"

<div class="alert alert-info" role="alert">
#### **There are three goals for this project:**

  - To design and implement a somewhat complex embedded system that is evaluated by your peers
    based on principles like usability and enjoyment.
  - To construct, organize and implement a multi-module code project.
  
</div>

<div class="alert alert-danger" role="alert">
#### **How will it be evaluated?**

  1. The code for your Simon game will be submitted via canvas. Please include
  only code files and a "README.txt" that describes (a) briefly your code architecture
  and approach, (b) the score that you think you should get based on the rubric
  below, and (c) how to access or run any special features. You may include two
  different "main.c" files if desired, but the default functionality should be
  Simon.

  2. Prof. Kemere or the lab assistants will be running your code on their
  boards for evaluation. Your score for the final project will be based on the
  rubric below.

  3. Students from the class will be given the chance to evaluate
  based on a simpler rubric. These scores will not be used for grading, but
  course bonus will be assigned based on the final ranking of Simon programs.
  Additionally, a small bonus will be given for each of your peer's Simon games
  you evaluate.

  4. To facilitate peer grading, the code will be due **April 15**.

  **Rubric:** (10 pts each (mvp is 30 pts, code is 20 pts), 130 total) 
  1. MVP (minimally viable product): Does it actually run properly off of a
    battery and (occasionally) perform in a Simon-esque way? (30 pts)
  2. Gameplay-ButtonFeedback (when a button is pressed during play, does the
    light and sound asssociated with that button track the button press, i.e.,
    start when it is depressed and stop when it is released?)
  3. Gameplay-Timeout (does it game over after a while if no button is pressed?)
  4. Gameplay-MisplayingError (does it game over if the wrong button is pressed?)
  5. Gameplay-Win (does it do something special when the player wins?)
  6. Gameplay-Random (does it play a different sequence each time, including after power cycles?)
  7. Style-Animations (are there animations for start/win and lose/game-over?)
  8. Style-SoundLight (do lights and sounds work well together and convey information?)
  9. Is it easy to change the length of a sequence required to win?
  10. Well-commented, logical code architecture (does the architecture make sense? are there good
    comments?, functions (libraries?) used intelligently?) - 20 pts

</div>


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
should play a "Game Over - Lost" animation that continues until it is reset. Similarly, if the
player wins, the device should play a "Game Over - Won" animation until it is reset (e.g., by
power cycling or pressing a button). 

Details:

  - On initial boot, the devices should play either one of the "Game Over" animations or a
    third novel animation. Pushing any button should then start the game.
  - Sequences should be random each game (make sure your random routine produces a different
    value on startup!)
  - When a button is pressed, the appropriate LED should flash (and tone should sound).
  - The light and sound associated with the button should be displayed/played as long as the button is held down, and
    then should stop. (So _not_ like in the example video below where they play for a constant length of time regardless of
    how long the button is pressed for.)
  - The timeout period should not be a constant. Rather, each time a player pushes a button, a
    new timeout should start. Thus, a timeout of 1-2 s is appropriate.
  - Errors should result in immediate game over (i.e., button presses should be processed
    immediately).
  - You should make the maximum sequence size adjustable. For your video, sequences of length 5
    are appropriate.

Here's a video from Vitor Azevedo Andriotti (Spring 2015) showing a Simon board in action.
Note that in this video, the buttons are not synchronized with the LED/sound feedback.

<iframe width="560" height="315" src="https://www.youtube.com/embed/nrsBVdJFrKc"
frameborder="0" allowfullscreen></iframe>

Physical information is given in the
[ELEC327 Simon repository](https://raw.githubusercontent.com/ckemere/ELEC327/master/Labs/Midterm/)
Eagle CAD schematic in the ELEC327 git repository. 

*Note that you are not **limited** to the listed parts. You can add additional parts from the
list above or other lab supplies, but if you do, you are expected to demo their utility as part
of your project!*


