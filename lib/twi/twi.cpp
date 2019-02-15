/*
  twi.h - Library for twi comunication.
  Created by Mateusz Buta, October 20, 2018.
  Released into the public domain.
*/
#include "Arduino.h"
#include "twi.h"
#include "util.h"

//czas potrzebny na zmianę stanu pinu przy częstotliwości TWI 100kHz to 20ms
//czas potrzebny na zmianę stanu pinu przy częstotliwości TWI 400kHz to 12ms

void twiMasterBegin(){
  //Enable TWI
  TWCR |= (1<<TWEN);// | (1<<TWIE) | (1<<TWEA);

  // activate internal pullups for twi.
  digitalWrite(SDA, 1);
  digitalWrite(SCL, 1);

  #undef TWI_FREQ
  #define TWI_FREQ 100000L

  // initialize twi prescaler and bit rate
  TWBR = ((F_CPU / TWI_FREQ) - 16) / 2;
  //Prescaler to 64
  TWSR |= (1<<TWPS1) | (1<<TWPS0);
}

void twiSlaveBegin(uint8_t address){
  TWCR |= (1<<TWEN);
  TWAR = address<<1;
  TWAMR = 0;
}

void twiSlaveWait()
{
    while((TWSR & 0xF8)!= 0x60 || (TWSR & 0xF8)!= 0xA8)  // Loop till correct acknoledgement have been received
    {
        // Get acknowlegement, Enable TWI, Clear TWI interrupt flag
        TWCR=(1<<TWEA)|(1<<TWEN)|(1<<TWINT);    
        while (!(TWCR & (1<<TWINT)));  // Wait for TWINT flag
    }
} 

uint8_t twiSlaveRead()
{
    TWCR= (1<<TWINT)|(1<<TWEA)|(1<<TWEN);    
    while (!(TWCR & (1<<TWINT)));   

    if((TWSR & 0xF8)!=TW_SR_DATA_ACK);        
      Serial.print("twi Read Ack Error"); 
    return TWDR;                   
}

void twiSlaveWrite(uint8_t data) 
{
  TWDR = data;
  TWCR = (1<<TWINT) | (1<<TWEN);

  while (!(TWCR & (1<<TWINT))); 

  if ((TWSR & 0xF8) != TW_ST_DATA_NACK && TW_ST_DATA_ACK)
    Serial.print("twi Write Error");  
}





void twiMasterStart(){
  TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN); 
  while (!(TWCR & (1<<TWINT))); 
  
  if ((TWSR & 0xF8) != START) 
    Serial.print("twi Start Error");
}

void twiMasterWriteAddress(uint8_t address,uint8_t read){
  TWDR = address<<1 | read;
  TWCR = (1<<TWINT) | (1<<TWEN);
  while (!(TWCR & (1<<TWINT)));

  if (((TWSR & 0xF8) != MT_SLA_ACK) && ((TWSR & 0xF8) != MR_SLA_ACK))
    Serial.print("twi Write Error");    
}

void twiMasterWrite(uint8_t data){
  TWDR = data;
  TWCR = (1<<TWINT) | (1<<TWEN);
  while (!(TWCR & (1<<TWINT))); 

  if ((TWSR & 0xF8) != MT_DATA_ACK)
    Serial.print("twi Write Error");    
}

uint8_t twiMasterReadAck(){
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA); 
	while( !(TWCR & (1<<TWINT)) );

  if(((TWSR & 0xF8)!=MR_DATA_ACK))
    Serial.print("twi Read Ack Error"); 
	return TWDR;
}

uint8_t twiMasterReadNotAck(){
	TWCR = (1<<TWINT) | (1<<TWEN); 
	while( !(TWCR & (1<<TWINT)) );

  if(((TWSR & 0xF8)!=MR_DATA_NACK))
    Serial.print("twi Read Not Ack Error"); 
	return TWDR;
}

void twiMasterStop(){
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); // Transmit STOP condition
    
    while( !(TWCR & (1<<TWSTO)) );
    delay(10);
    //if(TWSR!=0xF8)
     // Serial.print("twi Stop Error");
    //digitalWrite(SDA, 0);
    //digitalWrite(SCL, 0);
}

void twiMasterSend(uint8_t address, uint8_t data){
  twiMasterStart();
  twiMasterWriteAddress(address,WRITE);
	twiMasterWrite(data); 
  twiMasterStop();
}

uint8_t twiMasterReceive(uint8_t address){
  twiMasterStart();
  twiMasterWriteAddress(address,READ);
	uint8_t data=twiMasterReadNotAck();
  twiMasterStop();
  return data;
}

void twiScan(){
  for(uint8_t address = 1; address < 127; address++){
    //if(address!=0b00000001	&& address!=0b0000001 && address!=0b0000010 && address!=0b0000011 && (address|00000111)!=0b00001111 && (address|00000111)!=0b11110111	&& (address|00000111)!=0b11111111){

    twiMasterStart();
    TWDR = address<<1;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if ((TWSR & 0xF8) == MT_SLA_ACK){
      Serial.print("Address ");
      Serial.print(address,HEX);
      Serial.print(" ");
      Serial.print(address,BIN);
      Serial.print(" is present\n");
    }
      
    twiMasterStop();
    delay(10);
  }
}


