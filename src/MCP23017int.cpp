/**
 * File: MCP23017int.cpp
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

#include "MCP23017int.h"

void MCP23017int::begin(
  Adafruit_MCP23017* mcp,
  byte arduinoInterruptPin,
  void (*interruptHandler)(),
  MCP23017intButton buttons[],
  byte size
)
{
  this->_mcp = mcp;
  this->_arduinoPin = arduinoInterruptPin;
  this->_arduinoPinInInterrupt =
   digitalPinToInterrupt(this->_arduinoPin);
  this->_interruptHandler = interruptHandler;
  this->_buttons = buttons;
  this->_size = size;

  pinMode(this->_arduinoPin, INPUT_PULLUP); // Initialize the interrupt pin as input

  this->_mcp->setupInterrupts(true, true, LOW);

  for(int i = 0; i < size; i++)
  {
    this->_mcp->pinMode(this->_buttons[i].mcpPin, INPUT);
    this->_mcp->pullUp(this->_buttons[i].mcpPin, HIGH);  // turn on a 100K pullup internally
    this->_mcp->setupInterruptPin(this->_buttons[i].mcpPin, FALLING); 
  }

  attachInterrupt(this->_arduinoPinInInterrupt, this->_interruptHandler, FALLING);
  while(MCP23017_INT_ERR != this->_mcp->getLastInterruptPinValue())
  {
    // Some interrupts may be left in buffer that should be cleared.
  }
}

void MCP23017int::processInterrupt()
{
  //TODO: handle bouncing
  
  // Get more information from the MCP from the INT
  uint8_t pin = this->_mcp->getLastInterruptPin();
  if (pin == MCP23017_INT_ERR)
  {
    cleanInterrupts();
    return;
  }
  uint8_t val = this->_mcp->getLastInterruptPinValue();
  for(int i = 0; i < this->_size; i++)
  {
    if (this->_buttons[i].mcpPin == pin)
    {
      this->_buttons[i].callback(pin, val);
      break;
    }
  }

  this->_mcp->setupInterruptPin(pin, val == 0 ? RISING : FALLING);

  // and clean queued INT signal
  cleanInterrupts();
}

void MCP23017int::cleanInterrupts()
{
  this->_awakenByInterrupt = false;
}

/*
 * Should be called from Arduino interrupt handler.
 */
void MCP23017int::interruptOccurred()
{
  this->_awakenByInterrupt = true;
}

void MCP23017int::checkInterrupt()
{
  this->_mcp->getLastInterruptPinValue(); // Some interrupts may be left in buffer that should be cleared to enable next interrupt.
  if (this->_awakenByInterrupt)
  {
    // disable interrupts while handling them.
    detachInterrupt(this->_arduinoPinInInterrupt);

    this->processInterrupt();

    attachInterrupt(this->_arduinoPinInInterrupt, this->_interruptHandler, FALLING);
  }
}
