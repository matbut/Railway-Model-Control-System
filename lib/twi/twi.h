/*
  twi.h - Library for twi comunication.
  Created by Mateusz Buta, October 20, 2018.
  Released into the public domain.
*/
#ifndef Twi_h
#define Twi_h

#include "Arduino.h"
#ifndef TWI_FREQ
#define TWI_FREQ 100000L
#endif

void twiMasterBegin();
void twiSlaveBegin(uint8_t address);
void twiScan();
void twiMasterSend(uint8_t address,uint8_t data);
uint8_t twiMasterReceive(uint8_t address);

#endif