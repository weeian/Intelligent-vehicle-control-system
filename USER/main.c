/*****************************************************
实现功能：
v1.13版本：
1、红外避障中断触发，蜂鸣器报警
2、超声测距中断触发，检测到有障碍物时，点亮红灯
3、震动防盗中断触发，检测到有震动时，绿灯闪烁，蜂鸣器警报，LCD显示crush
4、倾斜报警中断触发，检测到倾斜时，LCD显示danger，蜂鸣器发出警报
5、触摸按键加速，检测到有触摸时，LCD显示speed up

v1.14:
   新增红外遥控功能
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
  u8 key;//红外遥控键值
 	u8 *str=0;//键值显示值
	u8 bus_state = 0;//记录汽车状态
 	u8 temperature;
	u8 humidity;    	 
	vu8 hour;
	vu8 min;
	vu8 sec;
	
	uart_init(9600);	 //串口初始化为9600 
	systick_init();			//时钟初始化
	delay_init();				//延时函数初始化
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	UltrasonicWave_Configuration();//超声测距模块初始化
	Timerx_Init(5000,7199);   //10Khz的计数频率，计数到5000为500ms 
	 
	HONGWAI_Init();  //红外模块初始化
 	LED_Init();			     //LED端口初始化
	LCD_Init();
	KEY_Init();  						//按键初始化
	T_Adc_Init();		  		//ADC初始化
	BEEP_Init();         	//初始化蜂鸣器端口
	BEEP=0;
  DHT11_Init();
	INCLINE_Init();  //倾斜报警模块初始化
  SHAKE_Init();
	 
	TPAD_Init(72);   //初始化触摸按键
	Remote_Init();//红外遥控模块初始化
	
	
	//显示时间
	POINT_COLOR=BLUE;//设置字体为蓝色  
	LED1=!LED1;  //绿灯亮起，说明没有发生震动，当发生震动时，绿灯熄灭
	
	LCD_ShowString(60,210,200,16,16,"  :  :  ");	//显示时间格式
	//显示温湿度
	LCD_ShowString(30+30,250,200,16,16,"Temp:  C");	 
 	LCD_ShowString(30+30,270,200,16,16,"Humi:  %");	
	while(1)
	{
		  
			if(m%10==0)//每100ms读取一次
		{									  
			DHT11_Read_Data(&temperature,&humidity);		//读取温湿度值					    
			LCD_ShowNum(30+40+30,250,temperature,2,16);		//显示温度	   		   
			LCD_ShowNum(30+40+30,270,humidity,2,16);			//显示湿度	 	   
		}				   
	 	delay_ms(10);	
	
		
//计算时间
		hour = Systime_sec/3600;
		min = Systime_sec%3600/60;
		sec = Systime_sec%60;
		LCD_ShowNum(60,210,hour,2,16);									  
		LCD_ShowNum(84,210,min,2,16);									  
		LCD_ShowNum(108,210,sec,2,16);

		
 		t=KEY_Scan(0);		//得到键值
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
				case KEY_UP:	//控制加速
					LCD_ShowString(60,50,200,16,16,"ahead");
					break;
				case KEY_LEFT:	//控制左转
					LCD_ShowString(60,50,200,16,16,"-left");
					break;
				case KEY_RIGHT:	//控制右转
					LCD_ShowString(60,50,200,16,16,"right");
					break;
				case KEY_DOWN:	//同时刹车
					LCD_ShowString(60,50,200,16,16,"--off");
					break;
			}
		} 
			
		//触摸按键部分
		if(TPAD_Scan(0))	//成功捕获到了一次上升沿(此函数执行时间至少15ms)
		{
			LCD_ShowString(30+30,170,200,16,16,"speed up");	//显示speed up并延时1s
			delay_ms(1000);
			LCD_ShowString(30+30,170,200,16,16,"         ");	
		}
		n++;
		if(n==15)		 
		{
			n=0;
		}
		delay_ms(10);	
		
		//红外遥控模块程序 
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

