# MCP23017int

With this library you can easily set up an interrupt based setup for the MCP23017 port expander.

## Highlights
 - Non blocking solution
 - It utilizes the Adafruit_MCP23017 library for driving the I2C communication.
 - Theoretically you can set up more MCP23017s with different I2C ports. (In this case I recommend you to connect the interrupt pin to Arduino via a 1K resistor to be on the safe side.)
 - Sets up MCP23017 interrupt pins as mirrored, so only one wire is required from either INTA or INTB.
 - Starts up input pins with internal pullups, so no external resistors required.
 - Both push and release are detected.
 - There can be multiple buttons simultaneously pressed and releases will be handled correctly.

## MCP23017 port naming
#pin| name | Adafruit mapping (used here)
----|------|------------------------------
21 | GPA0 | 0
22 | GPA1 | 1
23 | GPA2 | 2
24 | GPA3 | 3
25 | GPA4 | 4
26 | GPA5 | 5
27 | GPA6 | 6
28 | GPA7 | 7
1 | GPB0 |  8
2 | GPB1 |  9
3 | GPB2 | 10
4 | GPB3 | 11
5 | GPB4 | 12
6 | GPB5 | 13
7 | GPB6 | 14
8 | GPB7 | 15

## Background
The Arduino interrupt pin is set to pullups, and MCP23017 interrupt output is set to open drain. This means, that when there is no data on the interrupt pin, the level is pulled high by the Arduino and the MCP23017 pulls that down to ground only when required.

When a button press (FALLING) is detected, the corresponding MCP23017 pin is reprogrammed to RISING detection.

Unfortunately there is a strange behaviour of the MCP23017. It keeps sending interrupts as long as the button is pressed. That is why the interrupt detection is changed at runtime. Also, there is an "interrupt queue"-like thing inside, and interrupts will not work correctly until the interrupt buffer is cleared. So there are some extra hooks involved in the code for the interrupt cleanup.

## TODO
 - Test/support sleep and powerdown modes.
 - Investigate whether is it possible to eliminate extra interrupt-queue cleaning hooks.
 - Use different license for wider integration options.

**Please feel free to post contributions!**

## Tested on
Library known to be working with the following setups.

IDE versions:
 - Arduino 1.8.5
 
Hardware:
 - ESP8266
 
**Please feel free to post an issue with your tested hardware!**
