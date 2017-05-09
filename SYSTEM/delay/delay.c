#include "delay.h"
#include "sys.h"
u32 Systime_us;
u32 Systime_sec;
void SysTick_Handler(void)
{
	Systime_us++;	
	if (Systime_us == 600000)
	{
		Systime_us -= 60000;
		Systime_sec++;
	}
}

void systick_init(void)
{
	Systime_us = 0;
	Systime_sec = 0;
	SysTick_Config(72);//��Ƶϵ��
}

//��ʼ���ӳٺ���
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
//SYSCLK:ϵͳʱ��
void delay_init()	 
{
//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
//	fac_us=SystemCoreClock/8000000;	//Ϊϵͳʱ�ӵ�1/8  
//	fac_ms=(u16)fac_us*1000;//��ucos��,����ÿ��ms��Ҫ��systickʱ����   
}								    

//��ʱnus
//nusΪҪ��ʱ��us��.		    								   
void delay_us(u32 nus)
{		
	u32 temp, uscount;
	SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;//��ֹSysTick�ж�
	uscount = 0;
	while (uscount < nus)
	{
		temp=SysTick->CTRL;
		if (temp&(1<<16))
		{
		 	SysTick->CTRL &= ~SysTick_CTRL_COUNTFLAG_Msk;//��ѯSysTick�Ƿ�ݼ���0
		 	uscount++;
		}
	}
	//��ΪSysTick����ֹ�жϣ�����ʱ��ʱ�䲹�䵽ȫ��ʱ�����Systime_sec��Systime_us��
	Systime_sec += nus / 1000000;
	Systime_us += nus % 1000000;
	if ( Systime_us > 1000000)
	{
		Systime_us -= 1000000;
		Systime_sec++;
	}
	SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;//�ָ�SysTick�ж�
}
//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
	delay_us(nms * 1000);	  	    
} 

































