# MCP23017int

With this library you can easily set up an interrupt based setup for the MCP23017 port expander.

## Highlights
 - Non blocking solution
 - It utilizes the Adafruit_MCP23017 for driving the i2c communication.
 - Theoretically you can set up more MCP23017-s with different i2c ports.
 - Sets up MCP23017 interrupt pins as mirrored, so only one wire is required from either INTA or INTB.
 - Starts up input pins with internal pullups, so no external resistors required.
 - Both push and release are detected.
 - There can be simultaneously multiply buttons pressed and releases will be handled correctly.

## MCP23017 port naming
#pin| name | Adafruite mapping (used here)
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
When a push (FALLING) detected, the pin was reprogrammed to RISING detection.

Unfortunately some extra data stays on the interrupt buffer of MCP23017, and interrupt will not work correctly until the interrupt buffer is cleared. So there are some hooks in the code for some interrupt cleanup.

## TODO
Test/support sleep and powerdown modes.
