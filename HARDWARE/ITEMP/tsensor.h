#ifndef __TSENSOR_H
#define __TSENSOR_H	
#include "stm32f10x.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//ADC ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/6/7 
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
 		 
#define ADC_CH_TEMP  	ADC_Channel_16 //�¶ȴ�����ͨ��
   
u16  T_Get_Temp(void);  //ȡ���¶�ֵ
void T_Adc_Init(void); //ADCͨ����ʼ��
u16  T_Get_Adc(u8 ch); //���ĳ��ͨ��ֵ  
u16  T_Get_Adc_Average(u8 ch,u8 times);//�õ�ĳ��ͨ��10�β�����ƽ��ֵ 	  
#endif 
