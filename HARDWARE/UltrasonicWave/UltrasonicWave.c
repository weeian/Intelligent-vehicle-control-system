//////////////////////////////////////////////////////////////////////////////////	 
//ʵ�ֹ��ܣ�����������ǰ���ϰ���
//��Ӧ�������
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

float UltrasonicWave_Distance;      //������ľ���    
int up = 0;
u8 b=0;

void LCD_Init(void);
void LED_Init(void);

/*
 * ��������UltrasonicWave_Config
 * ����  ��������ģ��ĳ�ʼ��
 * ����  ����
 * ���  ����	
 */
void UltrasonicWave_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//�ر�jtag
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;					 //PC0��TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //��Ϊ�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(GPIOC, &GPIO_InitStructure);	                 //��ʼ��TRIG

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				     //PC3��ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		 //��Ϊ����
  GPIO_Init(GPIOC,&GPIO_InitStructure);						 //��ʼ��ECHO
	
	//Line3-�ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource3);

 	  EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	//���ó��ж�
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//���ó������ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		
			
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					//�����ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}


void EXTI3_IRQHandler(void) //���������жϷ������
{
	delay_us(10);		                      //��ʱ10us

	//LCD_ShowNum(30+40,280,UltrasonicWave_Distance,20,16);//��LCD����ʾ����
    LED0=!LED0;		//��⵽ǰ�������������
	
		
	EXTI_ClearITPendingBit(EXTI_Line3);  //���EXTI3��·����
}



/*
 * ��������UltrasonicWave_StartMeasure
 * ����  ����ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
 * ����  ����
 * ���  ����	
 */
void UltrasonicWave_StartMeasure(void)
{
  GPIO_SetBits(GPIOC,GPIO_Pin_0); 		  //��>10US�ĸߵ�ƽ
  delay_us(20);		                      //��ʱ20US
  GPIO_ResetBits(GPIOC,GPIO_Pin_0);
	
}

/******************* (C) 1209 Lab *****END OF FILE************/
