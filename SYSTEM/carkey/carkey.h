#ifndef __CARKEY_H
#define __CARKEY_H 			   
#include "sys.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "car.h"
#include "tpad.h"
#include "UltrasonicWave.h"
#include "infr.h"
//////////////////////////////////////////////////////////////////////////////////	 
//���� ����̴

//��Ȩ���У�����ؾ���

////////////////////////////////////////////////////////////////////////////////// 	  	 
void carkeyscan(void);
void carbreak(void);
extern int bbreak;
#endif





























