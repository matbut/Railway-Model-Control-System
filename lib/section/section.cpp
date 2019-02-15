/*
  section.h - Library for train sections.
  Created by Mateusz Buta, October 30, 2018.
  Released into the public domain.
*/
#include "section.h"

Section::Section(PCF8574pin *begin,PCF8574pin *end,PCF8574pin *led){
    _begin = begin;
    _end = end;
    _led = led;
}
void Section::begin(){
    _state = EMPTY;
    _direction = NONE;

    _begin->pinMode(INPUT_PULLUP);
    _end->pinMode(INPUT_PULLUP);
    _led->pinMode(OUTPUT);
}

uint8_t Section::beginState(){
    if(_direction==FORWARD)
        return _begin->digitalRead();
    return _end->digitalRead();
}

uint8_t Section::endState(){
    if(_direction==FORWARD)
        return _end->digitalRead();
    return _begin->digitalRead();
}


void Section::update(){

    if(_state == EMPTY){
        if(_begin->digitalRead() == DETECTED){
            _direction = FORWARD;
            _state = ENTERING;
        }else if(_end->digitalRead() == DETECTED){
            _direction = BACKWARD;
            _state = ENTERING;
        }
    }
    if((_state == ENTERING) && (beginState() != DETECTED)){
        _state = PASSING;
    }
    if((_state == ENTERING || _state == PASSING) && (endState() == DETECTED)){
        _state = LEAVING;
    }
    if((_state == LEAVING) && (endState() != DETECTED)){
        _state = EMPTY;
    }

    if(_state==EMPTY)
        _led->digitalWrite(LED_EMPTY);
    else
        _led->digitalWrite(LED_OCCUPIED);
}

uint8_t Section::getState(){
    return _state;
}