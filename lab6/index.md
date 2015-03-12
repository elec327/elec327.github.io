---
title: Lab 6
layout: default
group: labs-navigation
description: Software Debouncing and the Simon PCB
---

{::options parse_block_html="true" /}

## Lab #6: Software Debouncing and the Simon PCB

#### Part 1: The Simon PCB

The game ["Simon"](https://en.wikipedia.org/wiki/Simon_(game)) is a classic toy which tests the
working memory of the player. In this lab, you will design the PCB for your implementation of
Simon and work on the code to process button presses. 

4 buttons
4 APA102 SPI RGB LEDs
(probably either in a row or in a circle)
Power switch
AAA battery pack
Piezo buzzer


#### Part 2: Software Debouncing

Two buttons which must be pressed in the pattern 1, 2, 1, 1, 2, 2. The LED should get
progressively brighter as pattern is entered faster and faster. If pattern is entered
incorrectly, LED should go off. Reset by holding both buttons simultaneously for 2 s, which
causes LED to flash.

**Save this code as `debounce.c`. Create a demo video that shows you playing and then resetting
and playing again. Upload your answered questions, code and the video URL to owlspace.**


