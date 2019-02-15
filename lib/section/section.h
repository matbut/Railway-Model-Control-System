/*
  section.h - Library for train sections.
  Created by Mateusz Buta, October 30, 2018.
  Released into the public domain.
*/
#ifndef Section_h
#define Section_h

#include "Arduino.h"
#include "section.h"
#include "pcfPin.h"
#include "pcf8574.h"

#define DETECTED LOW

#define EMPTY 0
#define ENTERING 1
#define PASSING 2
#define LEAVING 3

#define NONE 0
#define FORWARD 1
#define BACKWARD 2

#define LED_EMPTY HIGH
#define LED_OCCUPIED LOW

class Section
{
  public:
    Section(PCF8574pin *begin,PCF8574pin *end,PCF8574pin *led);
    void begin();
    void update();
    uint8_t getState();
  private:
    uint8_t beginState();
    uint8_t endState();

    PCF8574pin *_begin;
    PCF8574pin *_end;
    PCF8574pin *_led;
    uint8_t _state;
    uint8_t _direction;
};


#endif