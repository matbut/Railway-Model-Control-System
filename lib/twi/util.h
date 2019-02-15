/*
  twi/util.h - Library for twi comunication.
  Created by Mateusz Buta, October 20, 2018.
  Released into the public domain.
*/
#ifndef TwiUtil_h
#define TwiUtil_h

#define START   0x08        
#define REP_START   0x10    
//Master Transmiter
#define MT_SLA_ACK   0x18
#define MT_SLA_NACK   0x20
#define MT_DATA_ACK   0x28
#define MT_DATA_NACK   0x30
#define MT_ARB_LOST   0x38
//Master Receiver
#define MR_ARB_LOST   0x38
#define MR_SLA_ACK   0x40
#define MR_SLA_NACK   0x48
#define MR_DATA_ACK   0x50
#define MR_DATA_NACK   0x58
//Slave Transmiter
#define TW_ST_SLA_ACK   0xA8
#define TW_ST_ARB_LOST_SLA_ACK   0xB0
#define TW_ST_DATA_ACK   0xB8
#define TW_ST_DATA_NACK   0xC0
#define TW_ST_LAST_DATA   0xC8
 //Slave Receiver
#define TW_SR_SLA_ACK   0x60
#define TW_SR_ARB_LOST_SLA_ACK   0x68
#define TW_SR_GCALL_ACK   0x70
#define TW_SR_ARB_LOST_GCALL_ACK   0x78
#define TW_SR_DATA_ACK   0x80
#define TW_SR_DATA_NACK   0x88
#define TW_SR_GCALL_DATA_ACK   0x90
#define TW_SR_GCALL_DATA_NACK   0x98
#define TW_SR_STOP   0xA0

#define NO_INFO   0xF8
#define BUS_ERROR   0x00
#define STATUS_MASK
#define STATUS   (TWSR & TW_STATUS_MASK)
#define READ   1
#define WRITE   0

#endif