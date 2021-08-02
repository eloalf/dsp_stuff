# dsp_stuff

Experiments and notes for understanding **Digital Signal Processing** and other numerical stuff.

### ggT3.c
Simple tool to calculate **Greatest common divisor** and **Least common multiple** out of 2 positive integer numbers.<br/>
Can be applied to design a Rational resampler circuitry or software function.<br/>
Example usage:  `./ggT3 123456 432`

### bin2gray.c
Tiny program to calculate a **Cyclic gray code**.<br/>

### lfsr.c
Simple program to demonstrate how to create a PRBS (**Pseudo random binary sequence**) using a 16-bit **Maximum length sequence**
register with **Galois LFSR** architecture having 4 feedback taps and a period of 65535 clock cycles.<br/>
Usage:  `./lfsr` <br/>
Two files will be created: `lfsr.log` and `lfsr.dat` <br/>
