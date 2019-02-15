/*
  pcf8574.h - Library for Pcf8574 expander.
  Created by Mateusz Buta, October 20, 2018.
  Released into the public domain.
*/

#ifndef Pcf8574_h
#define Pcf8574_h

#include "Arduino.h"
typedef unsigned char uint8_t;

class PCF8574
{
  public:
    PCF8574();
    PCF8574(uint8_t address);
    void begin();
    void pinMode(uint8_t pin, uint8_t mode);
    void digitalWrite(uint8_t pin, uint8_t state);
    void write(uint8_t pinStates);
    uint8_t digitalRead(uint8_t pin);
    uint8_t read();
    void toggle(uint8_t pin);
    void clear();
    void set();


    uint8_t pinsChanged();

    void readGPIO();
    void writeGPIO();

  private:
    volatile uint8_t _pinModes; //INPUT->0 OUTPUT->1
    volatile uint8_t _pinStates; //LOW->0 HIGH->1
    volatile uint8_t _oldPinStates; 
    uint8_t _address;

};

#endif