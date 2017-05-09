//////////////////////////////////////////////////////////////////////////////////	 
//实现功能：超声波测量前方障碍物
//反应：亮红灯
//////////////////////////////////////////////////////////////////////////////////

#include "UltrasonicWave.h"
#include "usart.h"
#include "timer.h"
#include "delay.h"
#include "lcd.h"
#include "led.h"


#define	TRIG_PORT      GPIOC		//TRIG       
#define	ECHO_PORT      GPIOC		//ECHO 
#define	TRIG_PIN       GPIO_Pin_0   //TRIG       
#define	ECHO_PIN       GPIO_Pin_3	//ECHO   

float UltrasonicWave_Distance;      //计算出的距离    
int up = 0;
u8 b=0;

void LCD_Init(void);
void LED_Init(void);

/*
 * 函数名：UltrasonicWave_Config
 * 描述  ：超声波模块的初始化
 * 输入  ：无
 * 输出  ：无	
 */
void UltrasonicWave_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//关闭jtag
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;					 //PC0接TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //设为推挽输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(GPIOC, &GPIO_InitStructure);	                 //初始化TRIG

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				     //PC3接ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		 //设为输入
  GPIO_Init(GPIOC,&GPIO_InitStructure);						 //初始化ECHO
	
	//Line3-中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource3);

 	  EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	//设置成中断
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//设置成上升沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
			
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					//子优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}


void EXTI3_IRQHandler(void) //超声测距的中断服务程序
{
	delay_us(10);		                      //延时10us

	//LCD_ShowNum(30+40,280,UltrasonicWave_Distance,20,16);//在LCD上显示距离
    LED0=!LED0;		//检测到前方有物体亮红灯
	
		
	EXTI_ClearITPendingBit(EXTI_Line3);  //清除EXTI3线路挂起
}



/*
 * 函数名：UltrasonicWave_StartMeasure
 * 描述  ：开始测距，发送一个>10us的脉冲，然后测量返回的高电平时间
 * 输入  ：无
 * 输出  ：无	
 */
void UltrasonicWave_StartMeasure(void)
{
  GPIO_SetBits(GPIOC,GPIO_Pin_0); 		  //送>10US的高电平
  delay_us(20);		                      //延时20US
  GPIO_ResetBits(GPIOC,GPIO_Pin_0);
	
}

/******************* (C) 1209 Lab *****END OF FILE************/
