What is it?
===========

**PCD8544** is a library for the [Arduino](http://arduino.cc/) to interface with LCDs based on the
Philips PCD8544 controller ([datasheet](https://github.com/carlosefr/pcd8544/blob/master/docs/pcd8544.pdf?raw=true))
or compatibles. These displays are commonly found on older monochrome mobile phones, such as the
[Nokia 3310](http://en.wikipedia.org/wiki/Nokia_3310) or [5110](http://en.wikipedia.org/wiki/Nokia_5110),
so if you have one of these stuck in a drawer, take it out and start hacking away! :)

![PCD8544.png](http://cloud.carlos-rodrigues.com/projects/pcd8544/PCD8544.png)

Installation
============

Uncompress the ".zip" file into your `_<arduino sketch folder>_/libraries` folder (you may need to create it first).
After restarting the Arduino IDE, it should appear in the libraries and examples menus.

How it Works
============

To use this library, you must first connect your LCD to the proper pins on the Arduino.
For a Nokia 3310 display the connections would be the following:

Display Pin       | Arduino Pin
------------------|------------
Pin 1             | +3.3V Pin
Pin 2 (SCLK)      | Digital Pin 3
Pin 3 (SDIN/MOSI) | Digital Pin 4
Pin 4 (D/C)       | Digital Pin 5
Pin 5 (SCE)       | Digital Pin 7
Pin 6             | Ground Pin
Pin 7             | 10uF capacitor to Ground Pin
Pin 8 (RST)       | Digital Pin 6

For this display model, "Pin 1" is the leftmost pin when facing the back of the display with the connector on top.

Nokia 5110 displays are slightly different. They have an external oscillator pin between pins 5 and 6 which should
be connected to +3.3V. I haven't used one of these myself, so please see the diagrams on
[this page](http://serdisplib.sourceforge.net/ser/pcd8544.html) for more details.

Since these LCDs are **3.3V** devices, you have to add
[extra components](http://www.sparkfun.com/commerce/tutorial_info.php?tutorials_id=65) to
connect it to the digital pins of the Arduino (not necessary if you are using a 3.3V variant
of the Arduino, such as the [Arduino Pro](http://www.arduino.cc/en/Main/ArduinoBoardPro)).

Now, take a moment and read through the included [`HelloWorld.ino`](examples/HelloWorld/HelloWorld.ino) example.
It shows how to use the basic features of the library. There is also another
[`Thermometer.ino`](examples/Thermometer/Thermometer.ino) example that demonstrates bitmapped graphics and charts.

Custom Symbols
==============

The library allows the use of custom bitmap symbols (5x8), defined by an array of five bytes.
To make it easy to create custom symbols, there's a graphical glyph editor
[available online](http://cloud.carlos-rodrigues.com/projects/pcd8544/).
