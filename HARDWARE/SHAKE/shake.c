////////////////////////////////////////////////////
//ʵ�ֹ��ܣ��𶯷���
//������ʽ���̵���˸�����������������LCD����ʾdanger
////////////////////////////////////////////////////
#include "delay.h"
#include "sys.h"
#include "beep.h"
#include "led.h"
#include "lcd.h"

void BEEP_Init(void);           //�������˿ڳ�ʼ��
void LED_Init(void);			     //LED�˿ڳ�ʼ��
void LCD_Init(void);              //LCDģ���ʼ��
void delay_init(void);

void SHAKE_Init(void)//��бģ���ʼ��
{
	
	
 	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	
	//��ʼ��PC4 ��������
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//PC4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //���óɸ���
 	GPIO_Init(GPIOC, &GPIO_InitStructure);


	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

//EXTI2 configure
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource4);	//PC4����ΪEXTI4

	EXTI_InitStructure.EXTI_Line = EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x2;//������ռ���ȼ� 0��� �͵���ռ�ߵ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x2;//�����ȼ�  ����ͬʱ����ʱ����Ӧ˳��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

void EXTI4_IRQHandler(void)//EXTI2�жϷ��������б������������
{
  if(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4)){
				  
		LED1=!LED1;//��ʱ��ɫָʾ����˸
		BEEP1();//�������𾯱�
		LCD_ShowString(60,150,200,16,16,"danger");	//��ʾΣ����ʾ
		delay_ms(1000);
	  LCD_ShowString(60,150,200,16,16,"      ");	
}
	else 
	   {LED1=LED1;}//����ʱ��ɫָʾ��������ʾ��ȫ��ʻ
	 EXTI_ClearITPendingBit(EXTI_Line4);
}
