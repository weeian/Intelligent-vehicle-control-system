/*****************************************************
ʵ�ֹ��ܣ�
v1.13�汾��
1����������жϴ���������������
2����������жϴ�������⵽���ϰ���ʱ���������
3���𶯷����жϴ�������⵽����ʱ���̵���˸��������������LCD��ʾcrush
4����б�����жϴ�������⵽��бʱ��LCD��ʾdanger����������������
5�������������٣���⵽�д���ʱ��LCD��ʾspeed up

v1.14:
   ��������ң�ع���
*****************************************************/
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "adc.h"
#include "tsensor.h"
#include "beep.h"
#include "dht11.h" 
#include "tpad.h"
#include "UltrasonicWave.h"
#include "hongwai.h"
#include "incline.h"
#include "timer.h"
#include "shake.h"
#include "remote.h"

int main(void)
 {
 	u8 t=0;
	u8 m=0;
	u8 n=0;
	u8 a=0;
  u8 key;//����ң�ؼ�ֵ
 	u8 *str=0;//��ֵ��ʾֵ
	u8 bus_state = 0;//��¼����״̬
 	u8 temperature;
	u8 humidity;    	 
	vu8 hour;
	vu8 min;
	vu8 sec;
	
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600 
	systick_init();			//ʱ�ӳ�ʼ��
	delay_init();				//��ʱ������ʼ��
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	UltrasonicWave_Configuration();//�������ģ���ʼ��
	Timerx_Init(5000,7199);   //10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms 
	 
	HONGWAI_Init();  //����ģ���ʼ��
 	LED_Init();			     //LED�˿ڳ�ʼ��
	LCD_Init();
	KEY_Init();  						//������ʼ��
	T_Adc_Init();		  		//ADC��ʼ��
	BEEP_Init();         	//��ʼ���������˿�
	BEEP=0;
  DHT11_Init();
	INCLINE_Init();  //��б����ģ���ʼ��
  SHAKE_Init();
	 
	TPAD_Init(72);   //��ʼ����������
	Remote_Init();//����ң��ģ���ʼ��
	
	
	//��ʾʱ��
	POINT_COLOR=BLUE;//��������Ϊ��ɫ  
	LED1=!LED1;  //�̵�����˵��û�з����𶯣���������ʱ���̵�Ϩ��
	
	LCD_ShowString(60,210,200,16,16,"  :  :  ");	//��ʾʱ���ʽ
	//��ʾ��ʪ��
	LCD_ShowString(30+30,250,200,16,16,"Temp:  C");	 
 	LCD_ShowString(30+30,270,200,16,16,"Humi:  %");	
	while(1)
	{
		  
			if(m%10==0)//ÿ100ms��ȡһ��
		{									  
			DHT11_Read_Data(&temperature,&humidity);		//��ȡ��ʪ��ֵ					    
			LCD_ShowNum(30+40+30,250,temperature,2,16);		//��ʾ�¶�	   		   
			LCD_ShowNum(30+40+30,270,humidity,2,16);			//��ʾʪ��	 	   
		}				   
	 	delay_ms(10);	
	
		
//����ʱ��
		hour = Systime_sec/3600;
		min = Systime_sec%3600/60;
		sec = Systime_sec%60;
		LCD_ShowNum(60,210,hour,2,16);									  
		LCD_ShowNum(84,210,min,2,16);									  
		LCD_ShowNum(108,210,sec,2,16);

		
 		t=KEY_Scan(0);		//�õ���ֵ
		if(t == KEY_UP)
				{
						if(bus_state== 0) 
							{bus_state = !bus_state;
							LCD_ShowString(60,30,200,16,16,"start");
							}
							else 
								{bus_state = !bus_state;
								LCD_ShowString(60,30,200,16,16,"-stop");}
				}
	  if(t&&bus_state)							
		{						   
			switch(t)
			{				 
				case KEY_UP:	//���Ƽ���
					LCD_ShowString(60,50,200,16,16,"ahead");
					break;
				case KEY_LEFT:	//������ת
					LCD_ShowString(60,50,200,16,16,"-left");
					break;
				case KEY_RIGHT:	//������ת
					LCD_ShowString(60,50,200,16,16,"right");
					break;
				case KEY_DOWN:	//ͬʱɲ��
					LCD_ShowString(60,50,200,16,16,"--off");
					break;
			}
		} 
			
		//������������
		if(TPAD_Scan(0))	//�ɹ�������һ��������(�˺���ִ��ʱ������15ms)
		{
			LCD_ShowString(30+30,170,200,16,16,"speed up");	//��ʾspeed up����ʱ1s
			delay_ms(1000);
			LCD_ShowString(30+30,170,200,16,16,"         ");	
		}
		n++;
		if(n==15)		 
		{
			n=0;
		}
		delay_ms(10);	
		
		//����ң��ģ����� 
    key=Remote_Scan();	
		if(key)
		{	 
			switch(key)
			{ 
				case 162:
					LCD_ShowString(60,30,200,16,16,"start");
				  break;	      
				case 98:
					LCD_ShowString(60,50,200,16,16,"ahead");
					break;
				case 2:
					LCD_ShowString(60,30,200,16,16,"-stop");
				  break;		 
				case 194:
					LCD_ShowString(60,50,200,16,16,"right");
				  break;	   
				case 34:
					LCD_ShowString(60,50,200,16,16,"-left");
					break;		   
				case 168:
					LCD_ShowString(60,50,200,16,16,"--off");
					break;		  
				default:
					break;		 
			}
		}
		a++;
		if(a==20)
		{
			a=0;
		}		

	}	 

}

