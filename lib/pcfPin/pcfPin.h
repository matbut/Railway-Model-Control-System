#ifndef PcfPin_h
#define PcfPin_h

#include "Arduino.h"
#include "pcf8574.h"

typedef unsigned char uint8_t;

class PCF8574pin{
    volatile PCF8574 *expander;
    volatile uint8_t pin;
public:
    PCF8574pin(PCF8574 *expander1, uint8_t pin1);
    void pinMode(uint8_t mode);
    void digitalWrite(uint8_t state);
    uint8_t digitalRead();
};

#endif