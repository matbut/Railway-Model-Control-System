/** 
 * Railway Model Control System
 * Created by Mateusz Buta, October 20, 2018.
 * Released into the public domain.
*/

#include "Arduino.h"
#include "pcf8574.h"
#include "pcfPin.h"

#include "twi.h"

#define DIFF 400
#define LEDS 4 
#define BUTTONS 4 
#define SLAVE_ADDRESS 0x29

PCF8574 buttonPanel(0x38);
PCF8574 ledPanel(0x20);

PCF8574pin buttonPin1(&buttonPanel,4);
PCF8574pin buttonPin2(&buttonPanel,5);
PCF8574pin buttonPin3(&buttonPanel,6);
PCF8574pin buttonPin4(&buttonPanel,7);
PCF8574pin buttonPins[BUTTONS] = {buttonPin1,buttonPin2,buttonPin3,buttonPin4};

PCF8574pin ledPin1(&ledPanel,4);
PCF8574pin ledPin2(&ledPanel,5);
PCF8574pin ledPin3(&ledPanel,6);
PCF8574pin ledPin4(&ledPanel,7);
PCF8574pin ledPins[LEDS] = {ledPin1,ledPin2,ledPin3,ledPin4};



/*
Section section12(&detector1,&detector2,&panel1);
Section section23(&detector2,&detector3,&panel2);
Section section34(&detector3,&detector4,&panel3);
*/
/*
const uint8_t background = A1;
const uint8_t detector1right = A2;
const uint8_t detector1left = A3;
const uint8_t detector2right = A4;
const uint8_t detector2left = A5;
*/
/*
int value;	
int backgroundValue;
int diff;
*/


uint8_t detectorStates = 0;
uint8_t turnoutStates = 0;
unsigned int state = LOW;
void setup()
{
  Serial.begin(9600);

  /*
  pinMode(background, INPUT);
  
  pinMode(detector1right, INPUT);
  pinMode(detector1left, INPUT);
  pinMode(detector2right, INPUT);
  pinMode(detector2left, INPUT);
  */
  
  
  twiMasterBegin();
  buttonPanel.begin();
  ledPanel.begin();

  //section12.begin();
  //section23.begin();
  //section34.begin();

  for(int i=0;i<BUTTONS;i++){
    buttonPins[i].pinMode(INPUT_PULLUP);
  }
  buttonPanel.writeGPIO();
  
  for(int i=0;i<LEDS;i++){
    ledPins[i].pinMode(OUTPUT);
    ledPins[i].digitalWrite(HIGH);
  }
  ledPanel.writeGPIO();
  
}
 
void loop()
{
  while(true){

    twiScan();
    /*
    detectorStates = twiMasterReceive(SLAVE_ADDRESS);
    //Serial.println(detectorStates);
    for(int i=0;i<LEDS;i++){
      state = (detectorStates >> i) & 1U;
      ledPins[i].digitalWrite(!state);
    }
    ledPanel.writeGPIO();

    buttonPanel.readGPIO();
    
    if(!buttonPin1.digitalRead())
      turnoutStates &= ~(1UL << 0);
    else if(!buttonPin2.digitalRead())
      turnoutStates |= 1UL << 0;

    if(!buttonPin3.digitalRead())
      turnoutStates &= ~(1UL << 1);
    else if(!buttonPin4.digitalRead())
      turnoutStates |= 1UL << 1;

    Serial.println(turnoutStates);
    twiMasterSend(SLAVE_ADDRESS,turnoutStates);
  */


    
    /*
    tracks.readGPIO();

    section12.update();
    section23.update();
    section34.update();

    panel.writeGPIO();
    */


    //backgroundValue = analogRead(background);
   
    
    //Serial.println(backgroundValue);

    /*
    Serial.println(analogRead(detector1right)-backgroundValue);
    Serial.println(analogRead(detector1left)-backgroundValue);
    Serial.println(analogRead(detector2right)-backgroundValue);
    Serial.println(analogRead(detector2left)-backgroundValue);
    Serial.println("-----------------");
    
    delay(1000);
    */
    
    //diff = DIFF;
    /*
    if(analogRead(detector1right)-backgroundValue>diff)
      panel1.digitalWrite(LOW);
    else
      panel1.digitalWrite(HIGH);

    if(analogRead(detector1left)-backgroundValue>diff)
      panel2.digitalWrite(LOW);
    else
      panel2.digitalWrite(HIGH);

    if(analogRead(detector2right)-backgroundValue>diff)
      panel3.digitalWrite(LOW);
    else
      panel3.digitalWrite(HIGH);

    if(analogRead(detector2left)-backgroundValue>diff)
      panel4.digitalWrite(LOW);
    else
      panel4.digitalWrite(HIGH);
    
    panel.writeGPIO();   
    */
    
  }

}       

