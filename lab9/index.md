---
title: Lab 9
lab: 9
layout: default
group: labs-navigation
description: Randomness
---

{::options parse_block_html="true" /}

## Lab #9: Generating random numbers in an embedded system

_The goals of this lab are threefold. First, to continue to reinforce the basic
structure of modular multi-file C-language programs, where functions are defined
in one code file and referenced in another. Included in that concept is the
scope of global variables. The second goal is for you to understand
linear-feedback shift-register approaches to generating pseudorandom numbers.
Finally, you will also have to be creative in order to discover sources of "true
entropy" to use to seed your random number generation system. 
Together, these will be a very important feature for the Simon game._

<div class="alert alert-danger" role="alert">
#### What should be turned in?

  1. Your **commented** `random_rainbow.c` file (_Canvas_)

#### The lab will be due April 3, 2019 at 11:59 PM
</div>

#### Randomness

##### We will add some randomness to the rainbow color movement. 
Most random number generators maintain a state from one generated number to the next. The
number that is used to initialize this state is called a "seed". Implement a random number
generator in a separate C-language file, with an associated header. We will follow the
C _standard library_ syntax. That means you should define two functions and a constant:

```
  int rand(void): returns a pseudorandom number in the range of 0 to RAND_MAX.
  RAND_MAX: is a constant whose default value may vary between implementations but it is granted to be at least 32767.
  void srand(int seed): initializes the random number generator.
```

For the purposes of this lab, you can make RAND_MAX 31. Note that you should include the state
variable in your C file, but not in the header. (In other words, it can have module "scope" but
should not have global scope".) **Your `rand()` and `srand()` functions should be
defined in a file called `random.c`, and they and the `RAND_MAX` constant you
chose should be defined in a file called `random.h`.**

Use your random number generator with your rainbow LED code from Lab 7. Rather
than having the colors cycle from "cold" to "hot", they should move up and down
in a random way at each time step. Note that if you just picked a random color
each timestep, it would appear as random flashing. Thus, you should have the
colors change smoothly and randomly. As in Lab 7, the color of each LED should
be delayed by one time step (so that color change also appears as physical
movement). 

An example of how you might change the colors is:
`next_change = (7*last_change + 16 - rand())/8`. This is effectively an IIR
lowpass filter on the sequence of random numbers. Note that the divide by 8
operation should be implemented as a right shift, and that the `change`
variables need to be signed `int`s rather than `char`s. 

###### Seeding the random number generator
The most complex part of this assignment is to generate an initial seed for the
random number generation (which would be passed into `srand()` during
initialization. Two ways which were discussed in class to generate random
entropy were to (a) look at the least significant bits when sampling from an
unconneted pin with the ADC and (b) require that the user push a button in order
to start the light display, and use something about the timing (e.g., elapsed time
since start or duration of depress) of that button press for entropy. _Again LSBs
will be most random in any sort of sampling of this type!_

Implement a true random seed for your visualization and save the file as
**`random_rainbow.c`.**.

##### Rubric
You will be graded on your achievement of the three learning goals: (1) Do you
have well-commented code in three files, with a locally-scoped state variable in
random.c? (2) Does your random number generator produce an appropriate sequence
of light changes that are visually interesting? Is this part of the code well
commented? (3) Does the sequence or pattern change each time the program is
power-cycled? (Is it seeded with an actual source of randomness?) Is this well
explained? (Bonus) Is there an attempt to continue to add entropy to the random
number generator as program operation continues? Are there other interesting
features?

