/**
 * File: MCP23017int.h
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
  */

#ifndef MCP23017INT_H
#define MCP23017INT_H

#include "Arduino.h"
#include "Adafruit_MCP23017.h" // https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library from LM

#define MCP23017INT_BUTTON_ACTION_PRESSED 0
#define MCP23017INT_BUTTON_ACTION_RELEASED 1

class MCP23017int;
typedef void (*MCP23017intButtonCallback)(
  MCP23017int* mcpInt, byte mcpPin, byte action);
typedef struct MCP23017intButton
{
  byte mcpPin;
  MCP23017intButtonCallback callback;
};

class MCP23017int
{
public:
  void begin(
    Adafruit_MCP23017* mcp,
    byte arduinoInterruptPin,
    void (*interruptHandler)(),
    MCP23017intButton buttons[],
    byte size
  );
  void interruptOccurred();
  void checkInterrupt();

private:
  Adafruit_MCP23017* _mcp;
  byte _arduinoPin;
  int _arduinoPinInInterrupt;
  MCP23017intButton* _buttons;
  byte _size;
  void (*_interruptHandler)();
  volatile boolean _awakenByInterrupt = false;

  void cleanInterrupts();
  void processInterrupt();
};

#endif
