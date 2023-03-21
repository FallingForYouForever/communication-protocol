#ifndef PROTOCOL_H
#define PROTOCOL_H
#include "public.h"

#define FRAME_HEAD_FIRST  (uint8_t) 0xA5    //帧头1
#define FRAME_HEAD_SECOND  (uint8_t) 0x5A   //帧头2
#define FRAME_TAIL (uint8_t)  0xFF        //帧尾

#define MAX_SIZE 512

/**模块***/
enum CtrMod{
             DRIVERBOARD=0,
             ULTRASONIC,
             VALVE,
             MOTOR
           };

#define MAX_CAN_PER_SEND_DATA 0x08

uint16_t CRC16_Check (const uint8_t *data,uint8_t len); //CRC16

typedef unsigned int (*AnalysisFunc) (unsigned char *);
void initAnalysisInterface (unsigned char type, AnalysisFunc pFunc);

typedef void (*SendFunc) (unsigned char *,unsigned int len);
void initSendInterface (unsigned char type, SendFunc pFunc);
#endif