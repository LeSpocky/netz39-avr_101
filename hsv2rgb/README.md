hsv2rgb
=======

What's this?
------------

This is more or less an example implementation of an HSV to RGB
algorithm optimized for fast execution on 8 bit microcontrollers. Some
simplifications are made so don't expect everything as exact as it could
be. Output is RGB with 8bit per channel. Input for brightness (V) and
saturation (S) assume 0 for zero and 255 for full, aka interval [0,1] is
mapped to [0,255]. However for color hue (H) we project the circle
[0°,360°) to [0,256) so 0 is not equivalent to 255 but we get in fact
all colors and don't have to fiddle with the 0 and 360 equivalent.

You can not take it as is and put it onto your uC, however this projects
includes thorough tests to ensure the algorithm produces the right
output. For a uC you would extract the needed parts and not put
everything into separate functions.

Hue can be handled a little different than saturation and value,
provided are two functions for 8 bit or 10 bit input. For S and V more
than 8 bit would cost a lot of computing power but for H it's just a
little wider integers needed. You see how it's done and you can adapt it
to 12 bit, and as you might guess this is handy for different ADC input
precision.

For display I would recommend to use a PWM with more than 8 bit
resolution (e.g. 10 bit), and a brightness lookup table as big as
your flash memory allows it, up to all 256 values for a channel.

ToDo
----

  * comparision with and deviation to a precise algorithm would be
    interesting, or even comparision with existing algorithms
