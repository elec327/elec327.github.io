---
title: Lab 8
layout: default
group: labs-navigation
description: Deep Brain Stimulation Case Study
---

{::options parse_block_html="true" /}

## Lab #8: Deep Brain Stimulation Case Study

#### Deep Brain Stimulation Background

#### Deep Brain Stimulator module

Questions

To treat seizures, Company A and Company B both have systems which control stimulation in
"closed loop", i.e., in response to some detected signature. Assume the Company A system is
measuring variability in heartrate, and the Company B system is measuring the spectral power in
a "local field potential" rhythm with a center frequency of ~30 Hz. Which system do you think
requires more power for data acquisition and why? Which system do you think requires more power
for signal processing? Which system do you think will have lower latency?

Let's try to reverse engineer the power consumption of a commercial IPG. Look at the energy use
data in Table 13 (for the Kinetra system from Medtronic). If the device consumes some ammount
of constant power (due to digital blocks) plus some amount of variable power depending on
stimulation intensity, we would expect the increase in energy consumption with increasing
stimulation current and pulse width to rise with a slope of approximately one. Is that what you
observe? Why might this not be the case?

Some dystonias are treated with DBS at 40 Hz rather than the standard 130 Hz for Parkinson's
disease. What would you expect the difference in battery life to be between the two conditions
for a Kinetra stimulator set to 5 mA stimulation and 60 us pulse widths (continuous
stimulation)?

**Upload your answered questionsto owlspace.**


