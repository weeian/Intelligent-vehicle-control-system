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
	SysTick_Config(72);//分频系数
}

//初始化延迟函数
//SYSTICK的时钟固定为HCLK时钟的1/8
//SYSCLK:系统时钟
void delay_init()	 
{
//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
//	fac_us=SystemCoreClock/8000000;	//为系统时钟的1/8  
//	fac_ms=(u16)fac_us*1000;//非ucos下,代表每个ms需要的systick时钟数   
}								    

//延时nus
//nus为要延时的us数.		    								   
void delay_us(u32 nus)
{		
	u32 temp, uscount;
	SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;//禁止SysTick中断
	uscount = 0;
	while (uscount < nus)
	{
		temp=SysTick->CTRL;
		if (temp&(1<<16))
		{
		 	SysTick->CTRL &= ~SysTick_CTRL_COUNTFLAG_Msk;//查询SysTick是否递减到0
		 	uscount++;
		}
	}
	//因为SysTick被禁止中断，把延时的时间补充到全局时间变量Systime_sec和Systime_us中
	Systime_sec += nus / 1000000;
	Systime_us += nus % 1000000;
	if ( Systime_us > 1000000)
	{
		Systime_us -= 1000000;
		Systime_sec++;
	}
	SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;//恢复SysTick中断
}
//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对72M条件下,nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
	delay_us(nms * 1000);	  	    
} 

































