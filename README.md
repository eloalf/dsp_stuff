# dsp_stuff

Experiments and material for understanding Digital Signal Processing.

### ggT3.c
Simple tool to calculate **Greatest common divisor** and **Least common multiple** out of 2 positive integer numbers.<br/>
Can be applied to design a Rational resampler circuitry or software function.<br/>
Example usage:<br/>
`./ggT3 123456 432`
`    ggT(123456,432) = 48`
`    kgV(123456,432) = 1111104`
`    1111104/123456 = 9 = Interpolationsfaktor`
`    1111104/432 = 2572 = Dezimations-Divisor`
