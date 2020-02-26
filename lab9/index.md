---
title: Lab 9
lab: 9
layout: default
group: labs-navigation
description: Randomness
---

{::options parse_block_html="true" /}

## Lab #9: Generating random numbers in an embedded system

_This lab builds on the PWM and RGB LED work we've done earlier. The goal is
for you to be comfortable with simple ways of generating random numbers in an embedded system.
That will be a very important feature for the Simon game._

<div class="alert alert-danger" role="alert">
#### What should be turned in?

  1. Your **commented** `random_rainbow.c` file (_Canvas_)

#### What should be demoed live?
  2. Showing how your RGB led string changes color in a random manner.
  3. The code for this demonstration.

#### The lab will be due April 3, 2019 at 11:59 PM
</div>

#### Randomness

##### Next, we will add some randomness to the rainbow color movement. 
Most random number generators maintain a state from one generated number to the next. The
number that is used to initialize this state is called a "seed". Implement a random number
generator in a separate C-language file, with an associated header. We will follow the
C standard library syntax. That means you should define two functions and a constant:

```
  int rand(void): returns a pseudorandom number in the range of 0 to RAND_MAX.
  RAND_MAX: is a constant whose default value may vary between implementations but it is granted to be at least 32767.
  void srand(int seed): initializes the random number generator.
```

For the purposes of this lab, you can make RAND_MAX 31. Note that you should include the state
variable in your C file, but not in the header. (In other words, it can have module "scope" but
should not have global scope".)

Now, change the shifting rainbow code so that at each time step, rather than
the temperature of each LED incrementing, pick a random change with value
`next_change = (7*last_change + 16 - rand())/8`. This value should be
constant for all LEDs in the chain. The result (hopefully) will be a rainbow
that randomly appears to move up and down. Note that the divide by 8 operation
should be implemented as a right shift, and that the `change` variables need
to be signed `int`s rather than `char`s. **Save this code as `random_rainbow.c`.***

