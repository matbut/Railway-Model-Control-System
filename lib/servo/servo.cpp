/** 
 * servo.h - Library for servo service.
 * Created by Mateusz Buta, November 10, 2018.
 * Released into the public domain.
*/

#include "Arduino.h"
#include "servo.h"


static uint16_t volatile servoHighTimes[SERVO_MAX_NUMBER];
static uint8_t volatile servoPins[SERVO_MAX_NUMBER];

static uint8_t volatile servoNumber=0;

uint16_t servoHighTime = DEFAULT_PULSE_WIDTH;

uint16_t pulse_width;
uint16_t counter = 0;
uint16_t ledCounter = 0;
uint8_t ledState = HIGH;

ISR(TIMER3_COMPA_vect)
{
  counter++;

  if(counter >= SERVO_PWM_PERIOD){
    counter=0;
    for(uint8_t idx=0;idx<servoNumber;idx++)
      digitalWrite(servoPins[idx],HIGH);

    ledCounter++;
    if(ledCounter>=50){
      ledState = !ledState;
      ledCounter=0;
      digitalWrite(13,ledState);
    }

  }else{
    for(uint8_t idx=0;idx<servoNumber;idx++)
      if(counter == servoHighTimes[idx])
        digitalWrite(servoPins[idx],LOW);
  }
}
    /*
    for(uint8_t idx=0;idx<servoNumber;idx++)
      servoExpanders[idx].digitalWrite(servoPins[idx],HIGH);

    ledCounter++;
    if(ledCounter>=50){
      ledState = !ledState;
      ledCounter=0;
      digitalWrite(13,ledState);
    }
    */


       /*
    for(uint8_t idx=0;idx<servoNumber;idx++)
      if(counter == servoHighTimes[idx])
        servoExpanders[idx].digitalWrite(servoPins[idx],LOW);
    */
 
void ServoBegin(){
  cli();
  TCCR3A = 0;
  TCCR3B = 0;

  // Turn on CTC mode. 
  TCCR3B |= (1 << WGM32);
  // Set a 1:8 prescaler.
  TCCR3B |= (1 << CS31);
   
  // Count from 0 to 20.
  TCNT3 = 0;
  OCR3A = 20;
   
  TIMSK3 |= (1 << OCIE3A);  // Enable timer compare interrupt.
  sei();   // Enable interrupts.
}

Servo::Servo(uint8_t pin){
  if(servoNumber<SERVO_MAX_NUMBER){
    _idx = servoNumber;
    servoHighTimes[_idx] = DEFAULT_PULSE_WIDTH;
    servoPins[_idx] = pin;
    pinMode(pin,OUTPUT);

    TIMSK3 &= ~(1 << OCIE3A); // disable timer compare interrupt
    servoNumber++;
    TIMSK3 |= (1 << OCIE3A); // enable timer compare interrupt
  }
}
 
void Servo::setPosition(uint16_t angle)
{
  pulse_width = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  TIMSK3 &= ~(1 << OCIE3A); // disable timer compare interrupt
  servoHighTimes[_idx] = pulse_width;
  TIMSK3 |= (1 << OCIE3A); // enable timer compare interrupt
}

