/**
 * File: InterruptBasics.ino
 * Description:
 * MCP23017int is a library to make it easy to use the interrupts on the MCP23017 port expander.
 *
 * Author: Balazs Kelemen
 * Contact: prampec+arduino@gmail.com
 * Copyright: 2012 Balazs Kelemen
 * Copying permission statement:
    This file is part of MCP23017int.
    MCP23017int is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Hardware setup for this example:
    MCP23017 - GPA0 - connected to ground via a push button
    MCP23017 - GPA1 - connected to ground via a push button
    MCP23017 - A0,A1,A2 - connected to ground
    MCP23017 - !RESET - connected to VCC via a 10K resistor
    
    MCP23017 Arduino
    INTA     D2
    SCL      A5
    SDA      A4
    GND      GND

    Hardware notes:
    - You can add more push buttons if you like. See button mapping below.
    - You can specify different I2C bus address by configuring the
      A0,A1,A2 pins but you have to initialize the Adafruit_MCP23017 library accordingly.
    - You can connect either INTA or INTB or both to the Arduino interrupt pin.
    - You can choose any interrupt pin. These differ on different models.
    - SCL and SDA might be mapped on a different pin of your Arduino, please check!

    MCP23017 port naming
    #pin name Adafruit mapping (used here)
    21   GPA0  0
    22   GPA1  1
    23   GPA2  2
    24   GPA3  3
    25   GPA4  4
    26   GPA5  5
    27   GPA6  6
    28   GPA7  7
     1   GPB0  8
     2   GPB1  9
     3   GPB2 10
     4   GPB3 11
     5   GPB4 12
     6   GPB5 13
     7   GPB6 14
     8   GPB7 15
*/

#include <Adafruit_MCP23017.h> // https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library from Library Manager
#include <MCP23017int.h>

#define ARDUINO_INT_PIN 2

// -- Interrupt handler predefinitions
void buttonCallback(byte mcpPin, byte action);
void arduinoInterruptHandler();

Adafruit_MCP23017 mcp;
MCP23017int mcpInt;

MCP23017intButton buttons[] = {
  { 0, buttonCallback },
  { 1, buttonCallback }
};

void setup() {
  Serial.begin(9600);

  mcp.begin();
  mcpInt.begin(&mcp, ARDUINO_INT_PIN, arduinoInterruptHandler,
    buttons, sizeof(buttons) / sizeof(MCP23017intButton));

  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output

  Serial.println("Ready");
}

void loop() {
  // put your main code here, but often call:
  mcpInt.checkInterrupt();
}

void buttonCallback(byte mcpPin, byte action)
{
  Serial.print("Pin ");
  Serial.print(mcpPin);
  Serial.print(" is ");
  Serial.println(
    action == MCP23017INT_BUTTON_ACTION_PRESSED ?
    "pressed" : "released");
}

/*
 * This is a rather stupid form of implementing callback functions, 
 * but this a limitation of the Arduino compiler.
 */
 void arduinoInterruptHandler()
{
  mcpInt.interruptOccurred();
}
