/*
  pcf8574.h - Library for Pcf8574 expander.
  Created by Mateusz Buta, October 20, 2018.
  Released into the public domain.
*/

#include "Arduino.h"
#include "pcf8574.h"
#include "twi.h"


PCF8574::PCF8574(){
  _address=1;
}

PCF8574::PCF8574(uint8_t address){
  _address=address;
}

void PCF8574::begin(){
  readGPIO();
  _oldPinStates=_pinStates;
}

void PCF8574::pinMode(uint8_t pin, uint8_t mode){
	switch (mode) {
    case INPUT:
      _pinModes &= ~(1 << pin);
      _pinStates &= ~(1 << pin);
      break;

    case INPUT_PULLUP:
      _pinModes &= ~(1 << pin);
      _pinStates |= (1 << pin);
      break;

    case OUTPUT:
      _pinModes |= (1 << pin);
      _pinStates &= ~(1 << pin);
      break;
   }
	//writeGPIO();
}

void PCF8574::digitalWrite(uint8_t pin, uint8_t state){
	switch (state) {
    case HIGH:
      _pinStates |= (1 << pin);
      break;

    case LOW:
      _pinStates &= ~(1 << pin);
      break;
  }
  //writeGPIO();
}

uint8_t PCF8574::digitalRead(uint8_t pin){
  //readGPIO();
  return (_pinStates & (1 << pin)) ? HIGH : LOW;
}

void PCF8574::write(uint8_t pinStates) {
  _pinStates=pinStates;
	//writeGPIO();
}

uint8_t PCF8574::read() {
	//readGPIO();
  return _pinStates;
}

void PCF8574::clear() {
	write(0x00);
}

void PCF8574::set() {
	write(0xFF);
}

void PCF8574::toggle(uint8_t pin){
  _pinStates ^= (1 << pin);
  //writeGPIO();
}

uint8_t PCF8574::pinsChanged(){
  //readGPIO();
  return _oldPinStates ^ _pinStates;
}

void PCF8574::readGPIO(){
  _oldPinStates=_pinStates;
  _pinStates=twiMasterReceive(_address);
}

void PCF8574::writeGPIO() {
  uint8_t val = ~_pinModes | _pinStates;
  twiMasterSend(_address,val);
}