---
title: Lab 1
lab: 1
layout: default
# group: labs-navigation
description: Intro C Programming
---

{::options parse_block_html="true" /}

### Lab #1: Intro C Programming (100 pts)

<div class="alert alert-info" role="alert">
#### **There are two goals for this assignment:**


  - To get a taste for writing code in the C programming language. 
  - To build a mental understanding for pointers and arrays. 
  
</div>

<div class="alert alert-danger" role="alert">
#### Due Date: Friday, January 17, 2025

#### **What should be turned in?**

  1. Your **commented** `encode_morse.c` file. Functionality will be assessed by evaluation of the output in 10 test cases.
  2. As described below, you can discover whether your code is functioning correctly by submitting it to the Autograder.
     When you are satisfied, submit your `encode_morse.c` file on Canvas.

</div>


#### The Task

In Labs 2 and 3, you will write firmware to flash a message in Morse Code using the LED on your MSPM0+ Launchpad. Morse
Code is an old way of communicating alphabetic characters that relies on a simple on-or-off signal and timing. We will use 
the version called "International Morse Code" for these labs. The specification is as follows (credit: 
[wikipedia article](https://en.wikipedia.org/wiki/Morse_code)). There are five elements:

  1. A short "on" signal (called a "short mark", "dot", or "dit"). The duration of this signal is the unit of time. In this
  lab, dots will be represented by a single period character (`'.'`).
  2. A long "on" signal (called a "long mark", "dash", or "dah"). The duration of the long signal is three time units. These
  will be represented as a single hyphen character (`'-'`).
  3. An inter-element gap of "off" signal between the dots and dashes representing a single character. The duration of
  this off period is also a single unit of time. Characters will be represented as a series of dots and dashes (e.g., '...'
  or '.--.'), so these will be defined implicitly.
  4. A short gap of "off" signal between the groups of dots and dashes representing one character in a word and the next.
  The duration of this off period is three units of time. In this lab, the gap between letters will be represented as a
  space character (`' '`).
  5. A medium gap of "off" signal between words. The duration of this off period is seven units of time. In this lab, the
  gap between words will be represented as a semicolon character (`';`).


To warm up our C coding for the semester, for Lab 1, you will write code to translate a Morse code message, defined as a
C-string (an array of characters terminated by a zero value (an ASCII NULL, `\0`). You will translate the message into
`(signal,timing)` tuples, printing out the number of time units for the current item, and it's signal value (`1` or `0`).
The message will be defined on the command line as a string macro named `MESSAGE`. 

As an example, if you are given the following string:
```
#define MESSAGE "... --- ...;"
```
You should print out:
```
1,1
0,1
1,1
0,1
1,1
0,3
1,3
0,1
1,3
0,1
1,3
0,3
1,1
0,1
1,1
0,1
1,1
0,7
```

Your code will loop over the character array, interpreting each element and printing out the relevant tuples with a
newline character (`'\n'`) separating them. You will submit your code on Canvas, in a single C file. The macro `MESSAGE` 
will define the string that you need to parse. The automatic grading script will compile your code with different test 
strings and compare the output you produce to the expected output.

**Detailed specification.** In addition to the 5 rules listed above, for this lab, there are a few more rules:

  1. You should treat the character `'_'` as a dash (i.e., the same as a `'-'`). You should treat the character `'/'`
     as an interword gap (i.e., the same as a `';'`).
  2. You should ignore unspecified characters (i.e., other than`'\0'`, `'-'`, `'_'`, `'.'`, `' '`, `';'`).
  3. Repeated breaks should be decoded as a single one of the longest type. So for example, the sequence `"  "` (2 spaces) 
     in a message should be decoded as a `' '` (single inter-letter space), with the output `0,3`. For another example, the sequence
      `" ;  ; "` in a message should be decaded as a `';'` (single inter-word space) and produce the output `0,7`.
  4. For subsequent labs on the microcontroller, you will loop the messages, and the gap between loops should be an
     inter-word period. So for this lab, if a message ends with something other than am interword (`';'` or `'/'`), you
     should still output a `(0,7)` code. (Keeping in mind point 3, if the last character was a single inter-letter space
     or a dot/dash, you should _only_ output the interword code.)

#### Testing

You are welcome to use any C compiler that you have access too (e.g, if you are running Linux or another Unix-like environment
on your own computer), however you should ensure that your code compiles using gcc on CLEAR. The instructions below assume that 
you have logged into the Rice student cluster, CLEAR. You can connect to CLEAR using ssh: `ssh netid@ssh.clear.rice.edu` will work if you are on campus or VPN. Otherwise you will need to first `ssh netid@ssh-students.rice.edu`, and then type in `ssh.clear.rice.edu` 
at the `Enter remote host:` prompt. If you want to use the Visual Studio Code editor, there is
a helpful guide [here](https://kb.rice.edu/internal/117203)!

Here are four test strings and the correct output.

  1. `MESSAGE='"-.-. .- -.;--- -- ---;"'` -- [test1.txt](test1.txt).
  3. `MESSAGE='"- . ... - ; ; .-.  .  .--. .  .- -  ..."'` -- [test2.txt](test2.txt)
  4. `MESSAGE='"-._. --- -.. ./...- ._ .-. .. .- -. -;-.-. .... .- ._.  ... /"'` -- [test3.txt](test3.txt)
  1. `MESSAGE='".-. .. -.-. .;.. ... ; -. .. -.-. . .-.-.- ; .-. .. -.-. . ; .. ... ; -. .. -.-. . .-.-.-;"'` -- [test4.txt](test4.txt)


You can test your code using the following commands. For example, for the first message:
```
gcc -o morse -D MESSAGE='"-.-. .- -.;--- -- ---;"' morse_timing.c
```
This compiles the code in `morse_time.c` with the defined message. Then, capture the output of the program you've compiled
and compare it to the correct output:
```
./morse > test.out
diff test.out test1.txt -s
```
If the output is correct, diff will report `Files test.out and test.out are identical`. 
The examples are also available in the `/clear/courses/elec327/2025/` directory; thus, if you 
are running your program on CLEAR, you can instead run:
```
./morse > test.out
diff test.out /clear/courses/elec327/2025/lab1/test1.txt -s
```

Here is a sample program that produces the correct output for the first message. It is also available to download
as [morse_timing.c](morse_timing.c).

```
#include <stdio.h>

#ifndef MESSAGE  // Preprocessor directive. Asks "Is the macro MESSAGE defined? If not, include the following code.""
#define MESSAGE "... --- ...;" // Preprocessor macro. Will automatically substitite for the string "MESSAGE"
                               // everywhere that it occurs in the code. Works like a case-sensitive search and replace!
                               // We can also define this macro on the gcc command line, which will override this
                               // definition because of the #ifndef.
#endif

char message[] = MESSAGE; // Uses the macro definition to initialize the message character array

int main() {
  
  printf("1,1\n");
  printf("0,1\n");
  printf("1,1\n");
  printf("0,1\n");
  printf("1,1\n");
  printf("0,3\n");
  printf("1,3\n");
  printf("0,1\n");
  printf("1,3\n");
  printf("0,1\n");
  printf("1,3\n");
  printf("0,1\n");
  printf("1,1\n");
  printf("0,1\n");
  printf("1,1\n");
  printf("0,1\n");
  printf("1,1\n");
  printf("0,7\n");

  return 0;
}
```

**NOTE** This program obviously won't work for the rest of the lab!!

#### Using the Autograder and Submitting
The autograder will be running during the last few days of the turn-in period. It will show you whether your code is
producing the correct output for the grading test cases. After you are pleased with your results, submit your C file
on Canvas. **Please only submit a single C file.**

[Autograder Link](http://granule.rice.edu:5000). Note that this is only accessible from within the Rice network (or on VPN).
