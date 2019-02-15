/** 
 * servo.h - Library for servo service.
 * Created by Mateusz Buta, November 10, 2018.
 * Released into the public domain.
*/

#ifndef Servo_h
#define Servo_h

#include "Arduino.h"

#define SERVO_PWM_PERIOD 1900 //20ms in 10us
#define MIN_PULSE_WIDTH 54 //1ms in 10us
#define DEFAULT_PULSE_WIDTH 150
#define MAX_PULSE_WIDTH 240 

#define SERVO_MAX_NUMBER 10


void ServoBegin();

class Servo
{
  public:
    Servo(uint8_t pin);
    void setPosition(uint16_t angle);
  private:
    uint8_t _idx;
};

#endif
