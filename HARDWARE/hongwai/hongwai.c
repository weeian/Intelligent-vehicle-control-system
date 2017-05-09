////////////////////////////////////////////////////////////////
//ʵ�ֹ��ܣ�������ϱ���
//��Ӧ������������
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


void HONGWAI_Init(void)//��������GPIO�ڳ�ʼ��
{
	
	
 	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	
	//��ʼ��PC0 ��������
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;//PC1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //���óɸ���
 	GPIO_Init(GPIOC, &GPIO_InitStructure);


	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

//EXTI1 configure
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource1);	//PC1����ΪEXTI1

	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//���ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x2;//������ռ���ȼ� 0��� �͵���ռ�ߵ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x2;//�����ȼ�  ����ͬʱ����ʱ����Ӧ˳��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

void EXTI1_IRQHandler(void)//EXTI1�жϷ�����򣨺�����ϴ�������
{
  if(!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)){
			BEEP1();
}
	else 
	   {BEEP=0;}
	 EXTI_ClearITPendingBit(EXTI_Line1);
}
