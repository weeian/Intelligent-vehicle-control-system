////////////////////////////////////////////////////
//实现功能：倾斜报警
//表现形式：蜂鸣器响起,并在LCD上显示crush
////////////////////////////////////////////////////
#include "delay.h"
#include "sys.h"
#include "beep.h"
#include "led.h"
#include "lcd.h"

void BEEP_Init(void);           //蜂鸣器端口初始化
void LED_Init(void);			     //LED端口初始化
void LCD_Init(void);
void delay_init(void);

void INCLINE_Init(void)//倾斜模块初始化
{
	
	
 	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	
	//初始化PC2 浮空输入
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;//PC2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //设置成浮空
 	GPIO_Init(GPIOC, &GPIO_InitStructure);


	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

//EXTI2 configure
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource2);	//PC2设置为EXTI2

	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x2;//设置抢占优先级 0最高 低的抢占高的
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x2;//亚优先级  决定同时发生时的响应顺序
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

void EXTI2_IRQHandler(void)//EXTI2中断服务程序（倾斜报警传感器）
{
  if(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2)){//读到电平就响起蜂鸣器
			
		BEEP1();
		LCD_ShowString(60,130,200,16,16,"crush");//显示翻车提示
		delay_ms(1000);
		LCD_ShowString(60,130,200,16,16,"     ");	
	
}
	else 
	   {BEEP=0;}
	 EXTI_ClearITPendingBit(EXTI_Line2);
}
