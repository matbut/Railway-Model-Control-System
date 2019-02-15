#include "Arduino.h"
#include "pcf8574.h"
#include "pcfPin.h"


    
PCF8574pin::PCF8574pin(PCF8574 *expander1, uint8_t pin1){
    expander = expander1;
    pin = pin1;
}

void PCF8574pin::pinMode(uint8_t mode){
    expander->pinMode(pin,mode);
}

void PCF8574pin::digitalWrite(uint8_t state){
    expander->digitalWrite(pin,state);
}

uint8_t PCF8574pin::digitalRead(){
    return expander->digitalRead(pin);
}
