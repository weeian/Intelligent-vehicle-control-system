#include "carkey.h"
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//���� ����̴

//��Ȩ���У�����ؾ���

////////////////////////////////////////////////////////////////////////////////// 	  
int bbreak = 0;


void carbreak(void);
u8 key=0;						//�洢������Ϣ
u8 shift=0;					//ǰ�����˵�λ
u8 start = 0;				//����
u8 lr = 0;    			//�����м���
void carkeyscan(void) {
	if(TPAD_Scan(0)){			//��������
			shift = !shift;
			
		}
		if(shift){
			LCD_ShowString(100,180,200,16,16,"Back! ");
			UltrasonicWave_StartMeasure();                //��ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
			delay_ms(100);
		} else {
			LCD_ShowString(100,180,200,16,16,"Ahead!");
		}
		
		if((lr == 0 && KEY_Scan_0(1) == 1)&&KEY_Scan_2(1) == 3 ) {
			start = !start;
			lr = 1;
		}else {
			lr = 0;
		}
		
		if(start==1){
			LCD_ShowString(30,50,200,16,16,"Engine Start!!");	
		} else{
			LCD_ShowString(30,50,200,16,16,"Engine OFF!!  ");	
		}
			
		
		
		
		
		if(KEY_Scan_0(1) == 1)
			{
				LCD_ShowString(150,130,200,16,16,"go Right!");
				TRIGHT = 1;
			} 
			else {
				LCD_ShowString(150,130,200,16,16,"          ");	
				TRIGHT = 0;
			}
			

			if(KEY_Scan_2(1) == 3)
			{
				LCD_ShowString(30,130,200,16,16,"go LEFT !");
				TLEFT = 1;
			} 
			else {
				LCD_ShowString(30,130,200,16,16,"          ");	
				TLEFT = 0;
			}
			
		if(KEY_Scan_1(1) == 2 || infr0 == 0)
			{
				carbreak();
			} 
			else {
				LCD_ShowString(100,160,200,16,16,"          ");
		
				if(start==1){
		
					if(KEY_Scan_3(1) == 4)
					{
						LCD_ShowString(100,100,200,16,16,"go!      ");
						if(shift){
							BACK = 1;
						} else {
							GO = 1;
						}
					} 
					else {
						LCD_ShowString(100,100,200,16,16,"          ");	
						GO = 0;
						BACK = 0;
					}
			} else {
				GO = 0;
				BACK = 0;
				TRIGHT = 0;
				TLEFT = 0;
				LCD_ShowString(100,100,200,16,16,"          ");	
				LCD_ShowString(100,160,200,16,16,"          ");
			}
		}
}

void carbreak(void){
	
		LCD_ShowString(100,160,200,16,16,"Break!   ");
		GO = 0;
		BACK = 0;
	
}
