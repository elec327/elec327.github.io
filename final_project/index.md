---
title: Final Project
lab: 12
layout: default
group: labs-navigation
description: Final Project
---
{::options parse_block_html="true" /}
## Final Project: Closed-Loop Low-Power Embedded Systems
#### Final Project Goals
The goal for the final project is to create a low-power embedded system that interacts with the
world in an interesting way. In previous years, we have focused on motion as a means to
requiring the tight timing that bare-metal embedded systems can provide.
#### Logistics
You should work in teams of between 2 and 4. The project will be due on the last day of finals.
#### Instructions
Please put together a written report, 2-3 pages, which includes a description of your concept
and actual design. Include pedagogical information about any sensors or special devices you
have used. Diagrams, pictures, and drawings are welcome. In addition, create two videos: one
longer, formed as a presentation (i.e., with slides) of your design and implementation, and one
shorter (two minutes or less) functioning as a brief advertisement mainly focused on showing off
your working product. On Canvas, submit either a link to a project site or your written
presentation, your code, and links to both videos.

For extra credit, create a GitHub project (for your code and other design files) and an
associated website with your written presentation content.

#### Rubric

Scores range from **0 to 120**. A functional device that meets all core requirements earns an 80.
The remaining 40 points are complexity bonuses awarded for ambitious code, sophisticated PCB
design, and exceptional demo videos.

---

<p style="font-size:0.85em; font-weight:600; letter-spacing:0.05em; text-transform:uppercase; color:#555; margin-bottom:0.25em;">Core requirements — 80 points</p>

**1. Functional product (30 pts)**

<table style="width:100%; border-collapse:collapse; font-size:0.9em; margin-bottom:1em;">
  <thead>
    <tr style="background:#f0f4f8;">
      <th style="text-align:left; padding:7px 10px; border:1px solid #d0d7de;">Criterion</th>
      <th style="text-align:right; padding:7px 10px; border:1px solid #d0d7de; white-space:nowrap;">Points</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="padding:6px 10px; border:1px solid #d0d7de;">Device powers on independently and can be handed to the instructor</td>
      <td style="text-align:right; padding:6px 10px; border:1px solid #d0d7de;">10</td>
    </tr>
    <tr style="background:#fafafa;">
      <td style="padding:6px 10px; border:1px solid #d0d7de;">Real inputs and real outputs working together in real time</td>
      <td style="text-align:right; padding:6px 10px; border:1px solid #d0d7de;">10</td>
    </tr>
    <tr>
      <td style="padding:6px 10px; border:1px solid #d0d7de;">Final product matches the proposal <em>(partial credit if scope changed — document why)</em></td>
      <td style="text-align:right; padding:6px 10px; border:1px solid #d0d7de;">10</td>
    </tr>
  </tbody>
</table>

**2. Custom PCB & hardware (20 pts)**

<table style="width:100%; border-collapse:collapse; font-size:0.9em; margin-bottom:0.5em;">
  <thead>
    <tr style="background:#f0f4f8;">
      <th style="text-align:left; padding:7px 10px; border:1px solid #d0d7de;">Criterion</th>
      <th style="text-align:right; padding:7px 10px; border:1px solid #d0d7de; white-space:nowrap;">Points</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="padding:6px 10px; border:1px solid #d0d7de;">MSPM0 is the computational brain on a custom PCB <em>(using the Launchpad for compute = 0/15)</em></td>
      <td style="text-align:right; padding:6px 10px; border:1px solid #d0d7de;">15</td>
    </tr>
    <tr style="background:#fafafa;">
      <td style="padding:6px 10px; border:1px solid #d0d7de;">Device is self-powered — not drawing from the Launchpad's power rail</td>
      <td style="text-align:right; padding:6px 10px; border:1px solid #d0d7de;">5</td>
    </tr>
  </tbody>
</table>

<p style="font-size:0.9em; color:#555; margin-top:0.25em;">Note: breakout boards hanging from wires will reduce your score. The more things are dangling, the less impressed I'll be.</p>

**3. New MSPM0 module — required (10 pts)**

<table style="width:100%; border-collapse:collapse; font-size:0.9em; margin-bottom:0.5em;">
  <thead>
    <tr style="background:#f0f4f8;">
      <th style="text-align:left; padding:7px 10px; border:1px solid #d0d7de;">Criterion</th>
      <th style="text-align:right; padding:7px 10px; border:1px solid #d0d7de; white-space:nowrap;">Points</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="padding:6px 10px; border:1px solid #d0d7de;">Uses at least one MSPM0 hardware module not covered in labs</td>
      <td style="text-align:right; padding:6px 10px; border:1px solid #d0d7de;">10</td>
    </tr>
  </tbody>
</table>

<p style="font-size:0.9em; color:#555;">Modules already covered in labs: TIMG/TIMA timer interrupts, PWM, SPI transmit. Everything else counts — ADC, I²C, UART, DMA, DAC, comparator, RTC, etc. The module must be evident in your code and explained in your report.</p>

**4. Code quality (10 pts)**

<table style="width:100%; border-collapse:collapse; font-size:0.9em; margin-bottom:1em;">
  <thead>
    <tr style="background:#f0f4f8;">
      <th style="text-align:left; padding:7px 10px; border:1px solid #d0d7de;">Criterion</th>
      <th style="text-align:right; padding:7px 10px; border:1px solid #d0d7de; white-space:nowrap;">Points</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="padding:6px 10px; border:1px solid #d0d7de;">Code is readable and well commented</td>
      <td style="text-align:right; padding:6px 10px; border:1px solid #d0d7de;">5</td>
    </tr>
    <tr style="background:#fafafa;">
      <td style="padding:6px 10px; border:1px solid #d0d7de;">Good system architecture — hardware modules used where appropriate, minimal busy-waiting</td>
      <td style="text-align:right; padding:6px 10px; border:1px solid #d0d7de;">5</td>
    </tr>
  </tbody>
</table>

**5. Presentation (10 pts)**

<table style="width:100%; border-collapse:collapse; font-size:0.9em; margin-bottom:1em;">
  <thead>
    <tr style="background:#f0f4f8;">
      <th style="text-align:left; padding:7px 10px; border:1px solid #d0d7de;">Criterion</th>
      <th style="text-align:right; padding:7px 10px; border:1px solid #d0d7de; white-space:nowrap;">Points</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="padding:6px 10px; border:1px solid #d0d7de;">Written report (2–3 pages): concept, architecture, and pedagogical content on sensors/devices used</td>
      <td style="text-align:right; padding:6px 10px; border:1px solid #d0d7de;">4</td>
    </tr>
    <tr style="background:#fafafa;">
      <td style="padding:6px 10px; border:1px solid #d0d7de;">Long presentation video with slides — explains design and implementation decisions</td>
      <td style="text-align:right; padding:6px 10px; border:1px solid #d0d7de;">3</td>
    </tr>
    <tr>
      <td style="padding:6px 10px; border:1px solid #d0d7de;">Short demo video (≤ 2 min) — shows the product working</td>
      <td style="text-align:right; padding:6px 10px; border:1px solid #d0d7de;">3</td>
    </tr>
  </tbody>
</table>

---

<p style="font-size:0.85em; font-weight:600; letter-spacing:0.05em; text-transform:uppercase; color:#555; margin-bottom:0.25em;">Complexity bonuses — up to +40 points</p>

**6. Code complexity bonus (up to +15 pts)**

Significant lines of code (SLOC, excluding blanks and comments) as a proxy for implementation
depth. Please include a SLOC count in your report — run `cloc` on your source directory.

<table style="width:100%; border-collapse:collapse; font-size:0.9em; margin-bottom:1em;">
  <thead>
    <tr style="background:#eaf3de;">
      <th style="text-align:left; padding:7px 10px; border:1px solid #c0dd97;">SLOC</th>
      <th style="text-align:right; padding:7px 10px; border:1px solid #c0dd97; white-space:nowrap;">Points</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="padding:6px 10px; border:1px solid #d0d7de;">&lt; 200</td>
      <td style="text-align:right; padding:6px 10px; border:1px solid #d0d7de;">0</td>
    </tr>
    <tr style="background:#fafafa;">
      <td style="padding:6px 10px; border:1px solid #d0d7de;">200 – 400</td>
      <td style="text-align:right; padding:6px 10px; border:1px solid #d0d7de;">5</td>
    </tr>
    <tr>
      <td style="padding:6px 10px; border:1px solid #d0d7de;">400 – 700</td>
      <td style="text-align:right; padding:6px 10px; border:1px solid #d0d7de;">8</td>
    </tr>
    <tr style="background:#fafafa;">
      <td style="padding:6px 10px; border:1px solid #d0d7de;">700 – 1000</td>
      <td style="text-align:right; padding:6px 10px; border:1px solid #d0d7de;">11</td>
    </tr>
    <tr>
      <td style="padding:6px 10px; border:1px solid #d0d7de;">1000 – 1500</td>
      <td style="text-align:right; padding:6px 10px; border:1px solid #d0d7de;">13</td>
    </tr>
    <tr style="background:#fafafa;">
      <td style="padding:6px 10px; border:1px solid #d0d7de;">&gt; 1500</td>
      <td style="text-align:right; padding:6px 10px; border:1px solid #d0d7de;">15</td>
    </tr>
  </tbody>
</table>

**7. PCB design complexity bonus (up to +15 pts)**

<table style="width:100%; border-collapse:collapse; font-size:0.9em; margin-bottom:0.75em;">
  <thead>
    <tr style="background:#eaf3de;">
      <th style="text-align:left; padding:7px 10px; border:1px solid #c0dd97;">Signal types present on board</th>
      <th style="text-align:right; padding:7px 10px; border:1px solid #c0dd97; white-space:nowrap;">Points</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="padding:6px 10px; border:1px solid #d0d7de;">Power + simple digital I/O only</td>
      <td style="text-align:right; padding:6px 10px; border:1px solid #d0d7de;">3</td>
    </tr>
    <tr style="background:#fafafa;">
      <td style="padding:6px 10px; border:1px solid #d0d7de;">+ analog signals or RF</td>
      <td style="text-align:right; padding:6px 10px; border:1px solid #d0d7de;">6</td>
    </tr>
    <tr>
      <td style="padding:6px 10px; border:1px solid #d0d7de;">+ high-speed or impedance-matched traces</td>
      <td style="text-align:right; padding:6px 10px; border:1px solid #d0d7de;">9</td>
    </tr>
    <tr style="background:#fafafa;">
      <td style="padding:6px 10px; border:1px solid #d0d7de;">+ mixed-signal layout with ground plane partitioning</td>
      <td style="text-align:right; padding:6px 10px; border:1px solid #d0d7de;">12</td>
    </tr>
  </tbody>
</table>

<table style="width:100%; border-collapse:collapse; font-size:0.9em; margin-bottom:1em;">
  <thead>
    <tr style="background:#eaf3de;">
      <th style="text-align:left; padding:7px 10px; border:1px solid #c0dd97;">Integration bonus</th>
      <th style="text-align:right; padding:7px 10px; border:1px solid #c0dd97; white-space:nowrap;">Points</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="padding:6px 10px; border:1px solid #d0d7de;">All external components soldered directly — no dangling breakout boards</td>
      <td style="text-align:right; padding:6px 10px; border:1px solid #d0d7de;">+3</td>
    </tr>
  </tbody>
</table>

**8. Video joy bonus (up to +10 pts)**

The short demo video is genuinely fun to watch. It shows ambition, craft, or just makes me smile.
Awarded at instructor discretion — think of it as the "would I show this in a recruitment video
for the class?" bonus.


**Additional Extra credit:** 

GitHub repo with code and design files, plus an associated project website → up to +5 pts.

---


#### Projects from previous years
**2015**
- [A Biometric Security Application for Vending Machine & Safe Box](__http://zjelec.github.io/ELEC-327-Final-Project/__)
- [The "Kemere Shoe"](__http://va17.github.io/ELEC327-Final-Project/__)
- [My Heart Is A Stereo](__http://ryanlidesign.wix.com/portfolio#!designs/c1dru__)  
- [The "IR-controlled Car"](__http://xyh1.github.io/Rice_University_ELEC327_MSP430_IR-Motors/__)
- [The "Longboard Light-Painting Speedometer"](__http://ethanwhassat.github.io/LONGBOARD-LIGHT-PAINTING-SPEEDOMETER/__)
**2014**
- [Fan Controller](__https://www.youtube.com/watch?v=mhptsetAkEA__)
- [Robot](__https://www.youtube.com/watch?v=cXXAIJgqIdM__)
- [Whiteboard Eraser](__http://youtu.be/5l_BqY-AgVQ__)
- [Light Follower](__https://www.youtube.com/watch?v=1jrtxBQFj9A__)
- [Robot](__https://www.youtube.com/watch?v=pwvoO46o1E8__)
- [Laser Targeting](__https://www.youtube.com/watch?v=hBBP-9Gh-Sk__)
- [Maze Game](__https://www.youtube.com/watch?v=vogIEGx5ChQ__)