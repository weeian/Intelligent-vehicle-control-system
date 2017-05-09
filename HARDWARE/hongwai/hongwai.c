////////////////////////////////////////////////////////////////
//实现功能：红外避障报警
//反应：蜂鸣器响起
////////////////////////////////////////////////////////////////

#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "beep.h"

void INFR_Init(void);
void EXTIC_Init(void);
void KEYUP_Init(void);
void BEEP_Init(void);


void HONGWAI_Init(void)//红外输入GPIO口初始化
{
	
	
 	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	
	//初始化PC0 浮空输入
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;//PC1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //设置成浮空
 	GPIO_Init(GPIOC, &GPIO_InitStructure);


	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

//EXTI1 configure
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource1);	//PC1设置为EXTI1

	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//边沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x2;//设置抢占优先级 0最高 低的抢占高的
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x2;//亚优先级  决定同时发生时的响应顺序
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

void EXTI1_IRQHandler(void)//EXTI1中断服务程序（红外避障传感器）
{
  if(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)){
			BEEP1();
}
	else 
	   {BEEP=0;}
	 EXTI_ClearITPendingBit(EXTI_Line1);
}
