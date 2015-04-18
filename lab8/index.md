---
title: Lab 8
layout: default
group: labs-navigation
description: Deep Brain Stimulation Case Study
---

{::options parse_block_html="true" /}

## Lab #8: Deep Brain Stimulation Case Study

#### Deep Brain Stimulation Background
Deep brain stimulation is an FDA-approved treatment for Parkinson's disease and essential
tremors. As the name implies, DBS therapy involves the implantation of electrodes into
structures deep in the brain ("deep" as opposed to surface or non-invasive transcranial
stimulation, and "brain" as opposed to stimulation of peripheral nerves). A DBS system
comprises to elements - the electrodes which are implanted into the brain and deliver charge to
the tissue, and the "implanted pulse generator" (IPG) which contains a battery and generates
and controls the stimulation pulses.  In this course, we have been studying the implementation
of small, low power embedded systems. An IPG is an excellent example of a very specialized
embedded system which must be both small and ulta-low power. The goal of this lab is for you to
learn more about devices which interface with the nervous system and to consider the design of
an IPG.


#### Deep Brain Stimulator module

#### Questions
<ol class="questions">
<li>
Read this [IEEE Spectrum article from 2006](Moore2006.pdf). What are two stimulation therapies
that are FDA approved for treating depression. What are two other therapies that are being
tested for efficacy in depressed patients (as of 2006 - note that AFAIK, these tests are
on-going).</li>
<li>
To treat seizures, Company A and Company B both have systems which control stimulation in
"closed loop", i.e., in response to some detected signature. Assume the Company A system is
measuring variability in heartrate, and the Company B system is measuring the spectral power in
a "local field potential" rhythm with a center frequency of ~30 Hz. Which system do you think
requires more power for data acquisition and why? Which system do you think requires more power
for signal processing? Which system do you think will have lower latency?
</li>
<li>>
Let's try to reverse engineer the power consumption of a commercial IPG. Look at the energy use
data in Table 13 (for the Kinetra system from Medtronic). If the device consumes some ammount
of constant power (due to digital blocks) plus some amount of variable power depending on
stimulation intensity, we would expect the increase in energy consumption with increasing
stimulation current and pulse width to rise with a slope of approximately one. Is that what you
observe? Why might this not be the case?
</li>
<li>
Some dystonias are treated with DBS at 40 Hz rather than the standard 130 Hz for Parkinson's
disease. What would you expect the difference in battery life to be between the two conditions
for a Kinetra stimulator set to 5 mA stimulation and 60 us pulse widths (continuous
stimulation)?
</li>
</ol>

**Upload your answered questionsto owlspace.**


