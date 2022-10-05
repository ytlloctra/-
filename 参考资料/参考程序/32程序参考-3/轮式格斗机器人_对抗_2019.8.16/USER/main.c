//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�����˼���Ƽ����޹�˾
//
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : �����ֵ�
//  ��������   :2018-5-23
//  ����޸�   : 
//  ��������   :��̨�Կ�����
//��Ȩ���У�����ؾ���
//Copyright(C) �����˼���Ƽ����޹�˾
//All rights reserved
//PD6��ǰצ�ĻҶ�
//******************************************************************************/

#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "pwm.h"
#include "delay.h"
#include "adc.h"
#include "move.h"
#include "scan.h"
#include "buzzer.h"
#include "dma.h"
#include "timer.h"
#define TEST 0   //1Ϊ���ԣ�0Ϊ������
void understage_move(void);
void delay(int t);
void TIM3_IRQHandler(void);   //TIM3�ж�
void DMA1_Channel1_IRQHandler(void);
void bianyuanshibiex(void);
void check(void);
void show(void);
void set_num(void);
void understage_onstage_ide(void);
void data_filter(void);
void UP_stage(void);
void speed_init(void);
u8 set_led(u8 a);
extern u32 GROUP;
extern unsigned char zheng_or_fan;
extern u32	TIM3CH1_CAPTURE_VAL;	//���벶��ֵ	 
extern int time;
u32 temp_z1=0,//��һ
		temp_z2=0,
		temp_z3=0,
		temp_z4=0,
		temp_z5=0,
		temp_z6=0,
		temp_y1=0,
		temp_y2=0,
		temp_y3=0,
		temp_y4=0,
		temp_y5=0,
		temp_y6=0,
		temp_Qz=0,//ǰ��
		temp_Hz=0,//����
		temp_back_H=0	,
		temp_back_H1=0 ,
		THRE_VALUE =1300;
		
u8  mm1,//���ֺ�����
		mm2,//�Ҷ���
		mm2last,
		mm3,//���ֺ�����
		mm4,
		key=0,
		avr_mm2=0,
		key_flag=0,//�м䰴��
		front_flag = 0,//ǰ�����ϰ���
		left_flag  = 0,
		right_flag = 0,
		back_flag  = 0,
		except_left_flag = 0,
		except_right_flag = 0,
		except_front_flag = 0,
		except_back_flag = 0,
		location_flag	 = 0,//��̨���±�־��0����̨�ϣ�1����̨��
		allaheadflag=0,
		backflag		=0,
		backflag1=0,
		ltxback=0,//��û��
		ltxahead=0,//��û��
		ltsbin=0,//��û��
		enemyflag=0;//
u32  yj=0,
		 zj=0,//ǰ����־λ����
		 ot=0,
		 speed_upstage = 1000;
u16 value[15];
u8 	chr[]="mm2",
		chr1[]="INIT SUCCESS",
		chr2[]="normal",
		chr3[]="enemy",
		chr4[]="Iinit Success",
		chr5[] = "upstage";
int x1=0,
		i,
		speed_normal = 650,
		speed_enemy = 900, 
		xj=0,
		kp=2,
		kd=1,
		lasttime=0,
		apwm=0,
		expectspeed=0,
		error=0,
		key_num=0,
		up_stage_delay=0,				//��̨��ʱ��־
		enemy_monitor=0,				//��̨�ϵ��˼���
		understage_enemy = 0,  //��̨���е���
		circle=0;	
u32 check45_PWM=900,check90_PWM=900,check45_TIME=100,check90_TIME=200,checkback_PWM=700,checkback_TIME=200;  //check��������
 int main(void)
 {
	  
	delay_init();               //��ʱ������ʼ��	
  delay_ms(1000);	 
  delay_ms(1000);	 
	NVIC_Configuration(); 	    //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 	LED_Init();			     //LED�˿ڳ�ʼ��
	BUZZER_GPIO_Config();		  	//
	OLED_Init();			          //��ʼ��OLED	
	MYDMA_Config(DMA1_Channel1,(u32)&ADC1->DR,(u32)&value,15);//��ʼ��DMA
	Adc_Init();               	//��ʼ��ADC 
  TIM1_PWM_Init(1799,3);     //���PWMƵ��=72000/(1799+1)=40Khz	
	TIM2_Int_Init(2499,143);                        //��ʱ��	
	mm_scan_GPIO_Config();     //����Թܹܽų�ʼ������ͨIO���룩	 	 
	OLED_Clear();          //OLED ����
	
	logo();
		
	delay_ms(1000);
	delay_ms(1000);
	 OLED_Clear(); 
//	 while(1)
//	 {
//			ahead(500);
//	 }
	while(key_flag==0)       //�ȴ�����������key_flag�ǰ�����־
	{
		set_num();   
		speed_init();
//BUZZER(1);
	//OLED_Clear(); 
	}
	OLED_Clear();          //OLED ����

	while(value[2]<2000)
	{
			OLED_ShowString(0,0,chr4);
	}
	OLED_Clear();          //OLED ����
	back(700,700)	;
	delay_ms(180)	; 
	stop();
	delay_ms(1000);
	back(speed_upstage,speed_upstage);
	delay_ms(1000);
	//delay_ms(300);
	left(1100);
	delay_ms(300);
	while(1)
				{
				#if TEST==1
					{
				//	backST(500);
				//backST(300);
			//			show();
			//			if(zhengorfan()==1) circle+=1;
			//			else if(zhengorfan()==2) circle-=1;
			//			//set_num();
			//mm2last=mm2;
					}  
				#else
					{
						
						show();                //��ʾ����
						understage_onstage_ide();//�ж�̨��̨��
						if(location_flag==0)
						//if(1)
							bianyuanshibiex();     //��̨�ϱ�Եʶ��
						else
							understage_move();                //��̨��ʶ��
						if(xj/160==1) {xj=0;}
						set_led(xj/20+1);
						if(mm2==0) {x1 = 1;}
						xj++;//��LED�й�
						mm2last			 = mm2;
						ltxback=0;
						
					
															
					}
					#endif
			}
}
			 

/******************delay �Ľ�*********************/


/**************************************************/
void delay(int t)
{
	int i;
	for(i=t/1000 ; i>0 ;i-- )
	{      
		delay_ms(1000);
	}
	delay_ms(t%1000);
}


/******************��Ե�Ľ�*********************/


/**************************************************/
void bianyuanshibiex(void)//��̨���ö�ʱ��ˢ�����ݣ�����ʹ�ܣ��ر�ʹ��
{
				{	 
								if(value[5]>THRE_VALUE||value[6]>THRE_VALUE )    // two sensor front find enemy 2  
							{	
								 if((mm_scan(GPIOD,GPIO_Pin_7)==1||mm_scan(GPIOD,GPIO_Pin_2)==1))  {back(500,500);backflag=1;}
								 else  
											{
												if(backflag==1)
													{
														if(value[6]>2700||value[5]>2700) backflag=0;
														else 
														stop();
													 }
											else		allahead(speed_enemy);
																
											}
								backflag1=0;	
								BUZZER(1);											
							}
				else if((mm_scan(GPIOD,GPIO_Pin_7)==1||mm_scan(GPIOD,GPIO_Pin_2)==1)) 
							{
									back(600,600);backflag1=1;xj=0;backflag=0;//
							}			
				else if( value[4]>THRE_VALUE||value[3]>THRE_VALUE||value[2]>THRE_VALUE||value[0]>THRE_VALUE) //one sensor  right and right back  find enemy  and right back   2   temp_ahead_right>1500 || temp_right>1500  ||
							{
									left(1100);		//temp_z3~temp_z6
									yj=0;
								BUZZER(1);
//									delay_ms(100);		//test								
							}
				else if( value[7]>THRE_VALUE||value[8]>THRE_VALUE||value[9]>THRE_VALUE||value[11]>THRE_VALUE)  //one sensor left and left back find enemy 2    temp_left>1500 ||temp_back>1500 ||
							{ 
									right(1100);//temp_y3~temp_y6
									yj=1;
									BUZZER(1);
//									delay_ms(100);		//test
							}
				else 
								{
									backflag=0;
									if(backflag1==1)
											{											
												back(800,800);delay_ms(100);
												if(yj==1)	
													{
														 right(1100);														
													}
												else 
													{
														 left(1100);														
													}
													delay_ms(200);			//��Ե��ת										
													backflag1=0;
											}									
						//		else if((hui1==0&&hui2==0&&hui3==0&&hui4==0)&&GROUP==1) ahead(500);//����550
									else if(mm4 == 1) ahead(350);
									else	ahead(speed_normal);
											BUZZER(0);
								}							
				
				}
}




/*****************λ��ʶ��************************/


/**************************************************/
void understage_onstage_ide()
{
	front_flag 	 			= 0;
	left_flag  	 			= 0;
	right_flag   			= 0;
	back_flag    			= 0;
	except_left_flag = 0;
	except_right_flag = 0;
	except_front_flag = 0;
	except_back_flag = 0;
	if(temp_z1>THRE_VALUE||temp_y1>THRE_VALUE)
			front_flag 			 = 1;
	if( temp_z3>THRE_VALUE||temp_z4>THRE_VALUE)
			left_flag  			 = 1;
	if( temp_y3>THRE_VALUE||temp_y4>THRE_VALUE)
			right_flag 			 = 1;
	if( temp_z6>THRE_VALUE||temp_y6>THRE_VALUE)
			back_flag  			 = 1;
	if(front_flag == 1 && (back_flag == 1 || temp_z4>THRE_VALUE || temp_y4>THRE_VALUE))
		  except_front_flag = 1;
	if(back_flag == 1 && (front_flag == 1 || temp_z4>THRE_VALUE||temp_z3>THRE_VALUE || temp_y4>THRE_VALUE||temp_y3>THRE_VALUE))
		  except_back_flag = 1;
	if(left_flag == 1 && (right_flag == 1 || temp_y1>THRE_VALUE || temp_y6>THRE_VALUE))
		  except_left_flag = 1;
	if(right_flag == 1 && (left_flag == 1 || temp_z1>THRE_VALUE || temp_z6>THRE_VALUE))
		  except_right_flag = 1;
	
	if(except_front_flag == 1 ||  except_back_flag == 1 || except_left_flag == 1 || except_right_flag == 1)
			location_flag 	 = 1;				//��̨��
	else
			location_flag 	 = 0;					//��̨��
}

/****************��̨�³���**************************/


/**************************************************/
void understage_move()
{		BUZZER(0);
			if(temp_z1>(THRE_VALUE+1000)&&temp_y1>THRE_VALUE&&temp_y6>THRE_VALUE&&temp_z6>THRE_VALUE&&(temp_back_H<600&&temp_back_H1<600)&&temp_y4<THRE_VALUE&&temp_z4<THRE_VALUE&&location_flag==1)		//if(front_flag==1&&back_flag==1&&temp_Qz>1300)test
				{				
						up_stage_delay += 1;
				//		delay_ms(50);
						if(up_stage_delay>3)		
						{
								ahead(500);
								delay_ms(1700);
//								back(600,600)	;
//								delay_ms(180)	; 
//								stop();
//								delay_ms(1000);
								UP_stage();
								x1=0;
								up_stage_delay = 0;
						}	
				}
				else if((temp_z1>1700||temp_y1>1700)&&temp_y3>1700&&temp_y4>1700)  
					{
						ahead(400);
						ltxback=1;
					}
		      else if((temp_z1>1700||temp_y1>1700)&&temp_z3>1700&&temp_z4>1700)   
					{
						ahead(400);
						ltxback=2;
						
					}
				else
				{
					if(value[5]>3000||value[6]>3000) back(350,350);
					else 	right(400);
				}		
			
			if(ltxback==1||ltxback==2) zj++;
			else zj=0;
			if(zj>100) 
				{
			   if(ltxback==2)
				 {
					 back(700,700);
					 delay_ms(100);
					 while(value[5]>500&&value[6]>500) right(400);
					 ahead(700);
					 delay_ms(1000);
					 left(700);
					 delay_ms(300);
						zj=0;
				 }
				 else if(ltxback==1)
				 {
					back(700,700);
					 delay_ms(100); 
					while(value[5]>500&&value[6]>500) left(400);
					 ahead(700);
					 delay_ms(1000);
					 right(700);
					 delay_ms(300);
					 zj=0;
				 }
			 }
}


/****************��ʾ����**************************/



/*********************************************/
void show()
{
    
	
		data_filter();
//    mm1=mm_scan(GPIOD,GPIO_Pin_7);// 
//		mm2=mm_scan(GPIOD,GPIO_Pin_6);                   
//	 	mm3=mm_scan(GPIOD,GPIO_Pin_2);                  
		mm4=mm_scan(GPIOD,GPIO_Pin_6);                    
	                  
	if(temp_z1>500)	 OLED_ShowNum(0,0,temp_z1,4,12);
	else OLED_ShowNum(0,0,0,4,12);
	if(temp_z2>500)	 OLED_ShowNum(0,2,temp_z2,4,12);
	else OLED_ShowNum(0,2,0,4,12);
	if(temp_z3>500)	 OLED_ShowNum(0,4,temp_z3,4,12);
	else OLED_ShowNum(0,4,0,4,12);
	if(temp_z4>500)	 OLED_ShowNum(0,6,temp_z4,4,12);
	else OLED_ShowNum(0,6,0,4,12);
//	if(temp_z5>500)   OLED_ShowNum(26,2,temp_z5,4,12);
//	else OLED_ShowNum(26,2,0,4,12);
	if(temp_z6>500)	 OLED_ShowNum(26,4, temp_z6,4,12);
	else OLED_ShowNum(26,4, 0,4,12);
	if(temp_y1>500)	 OLED_ShowNum(78,0,temp_y1,4,12);
	else OLED_ShowNum(78,0,0,4,12);
	if(temp_y2>500)	 OLED_ShowNum(78,2,temp_y2,4,12);
	else OLED_ShowNum(78,2,0,4,12);
 	if(temp_y3>500)  OLED_ShowNum(78,4,temp_y3,4,12);
	else OLED_ShowNum(78,4,0,4,12);
	if(temp_y4>500)  OLED_ShowNum(78,6,temp_y4,4,12);
	else OLED_ShowNum(78,6,0,4,12);
//	if(temp_y5>500)  OLED_ShowNum(52,2,temp_y5,4,12); 
//	else OLED_ShowNum(52,2,0,4,12); 
	if(temp_y6>500)		OLED_ShowNum(52,4,temp_y6,4,12); 	
	else OLED_ShowNum(52,4,0,4,12);
	if(temp_back_H>500)		OLED_ShowNum(26,6,temp_back_H,4,12); 
	else 	OLED_ShowNum(26,6,0,4,12); 
	if(temp_back_H1>500)		OLED_ShowNum(52,6,temp_back_H1,4,12); 
	else 	OLED_ShowNum(52,6,0,4,12); 
		
		set_num();
		OLED_ShowNum(104,0,speed_normal,3,12); 
		OLED_ShowNum(104,2,speed_enemy,3,12); 
		OLED_ShowNum(104,4,mm_scan(GPIOD,GPIO_Pin_2),1,5); 
		OLED_ShowNum(104,6,mm_scan(GPIOD,GPIO_Pin_7),1,5);
}

 
char huodejianzhi()
{ //1 left   2 right   3 up    4 down   5 mid
	u8 key_l=0,key_r=0,key_up=0,key_down=0,key_mid=0;
	key_l=key_get(GPIOC,GPIO_Pin_6);      //d13
	key_r=key_get(GPIOD,GPIO_Pin_13);     //d12
	key_up=key_get(GPIOD,GPIO_Pin_12);     //c6
	key_down=key_get(GPIOD,GPIO_Pin_14);   //d15
	key_mid=key_get(GPIOD,GPIO_Pin_15);    //d14
	//OLED_Clear()  	;
	/* OLED_ShowNum(0,2,key_l,4,12);
	 OLED_ShowNum(52,2,key_r,4,12);
	 OLED_ShowNum(26,0,key_up,4,12);
	 OLED_ShowNum(26,4,key_down,4,12);
	 OLED_ShowNum(26,2,key_mid,4,12);*/
	
   if(key_l ==  1)   //left
  {
     key=1;
	}



if(key_r ==  1)   //right
{ 
{key=2;
}
}



if(key_up ==  1)   //up
{ 
{key=3;
}
}





if(key_down ==  1) //down
{
  
  {key=4;
}
}
 
if(key_mid ==  1)   //mid
{
  
  {key=5;
}
}

return key;		}


void set_num()
 {
		switch(huodejianzhi())//the value of key
			{
			 case 5:   //mid
							{
								key=0;
								delay_ms(150);
								if(key_flag==1)
										{
											key_flag=0;
										}
								else if(key_flag==0)
										{
											key_flag=1;
										}
								delay_ms(150);
								//xj-=1;
								} break;   
		default: break;
		case 4:   //down
			{
			key=0;
			 delay_ms(120);
			 key_num+=1;
				delay_ms(120);
				if(key_num > 2 ) key_num = 0;
			} break;

		case 3:  //up
			{
			key=0;
			 delay_ms(120);
			key_num-=1;
			 delay_ms(120);
				if(key_num < 0 ) key_num = 2;
		 
			}break;

		 case 2:  //right
						if(key_num==0)
					{
					
				 key=0;
					 delay_ms(120);
					 speed_normal+=50; 
					 delay_ms(120);
					}
					else if(key_num==1)
					{
					
						key=0;
					 delay_ms(120);
					 speed_enemy+=50; 
					 delay_ms(120);
					}
					else if(key_num==2)
					{
					
						key=0;
					 delay_ms(120);
					 speed_upstage+=50; 
					 delay_ms(120);
					}
        break;


case 1: //left
         if(key_num==0)
      {
      
     key=0;
       delay_ms(120);
       speed_normal-=50; 
       delay_ms(120);
      }
			else if(key_num==1)
      {
      
     key=0;
       delay_ms(120);
       speed_enemy-=50; 
       delay_ms(120);
      }
			else if(key_num==2)
      {
      
     key=0;
       delay_ms(120);
       speed_upstage-=50; 
       delay_ms(120);
      }
         break;
}
			
	
}

u8 set_led(u8 a)

{
		switch(a)
		{
			case 1:
			GPIO_ResetBits(GPIOD,GPIO_Pin_11);   //a
			GPIO_ResetBits(GPIOD,GPIO_Pin_10);    //b
			GPIO_ResetBits(GPIOD,GPIO_Pin_9);    //c
			break;  
			case 2:
			GPIO_SetBits(GPIOD,GPIO_Pin_11);   //a
			GPIO_ResetBits(GPIOD,GPIO_Pin_10);    //b
			GPIO_ResetBits(GPIOD,GPIO_Pin_9);    //c
			break;  
			case 3:
			GPIO_ResetBits(GPIOD,GPIO_Pin_11);   //a
			GPIO_SetBits(GPIOD,GPIO_Pin_10);    //b
			GPIO_ResetBits(GPIOD,GPIO_Pin_9);    //c
			break;  
			case 4:
			GPIO_SetBits(GPIOD,GPIO_Pin_11);   //a
			GPIO_SetBits(GPIOD,GPIO_Pin_10);    //b
			GPIO_ResetBits(GPIOD,GPIO_Pin_9);    //c
			break;  
			case 5:
			GPIO_ResetBits(GPIOD,GPIO_Pin_11);   //a
			GPIO_ResetBits(GPIOD,GPIO_Pin_10);    //b
			GPIO_SetBits(GPIOD,GPIO_Pin_9);    //c
			break;  
			case 6:
			GPIO_SetBits(GPIOD,GPIO_Pin_11);   //a
			GPIO_ResetBits(GPIOD,GPIO_Pin_10);    //b
			GPIO_SetBits(GPIOD,GPIO_Pin_9);    //c
			break;  
			case 7:
			GPIO_ResetBits(GPIOD,GPIO_Pin_11);   //a
			GPIO_SetBits(GPIOD,GPIO_Pin_10);    //b
			GPIO_SetBits(GPIOD,GPIO_Pin_9);    //c
			break;  
			case 8:
			GPIO_SetBits(GPIOD,GPIO_Pin_11);   //a
			GPIO_SetBits(GPIOD,GPIO_Pin_10);    //b
			GPIO_SetBits(GPIOD,GPIO_Pin_9);    //c
			break;  
			
		}
		return 0;
}


void data_filter(void)
{
		u8 i;
    temp_z1=0;
	  temp_z2=0;
    temp_z3=0;
	  temp_z4=0;
	  temp_z5=0;   
	  temp_z6=0;//      
    temp_y1=0;//     
		temp_y2=0;//  
		temp_y3=0;//   
	  temp_y4=0;//  
	  temp_y5=0;// 
	  temp_y6=0;//
	  temp_Hz=0;
		temp_back_H=0;
		temp_back_H1=0;

		for(i=0;i<2;i++)
				{
					temp_z1=(value[5]>>1)+temp_z1;// 
					temp_z2=(value[4]>>1)+temp_z2;//					
					temp_z3=(value[3]>>1)+temp_z3;//   
					temp_z4=(value[2]>>1)+temp_z4;//    
					temp_z5=(value[1]>>1)+temp_z5;//     
					temp_z6=(value[0]>>1)+temp_z6;//      
					temp_y1=(value[6]>>1)+temp_y1;// 
					temp_y2=(value[7]>>1)+temp_y2;// 
					temp_y3=(value[8]>>1)+temp_y3;//   
					temp_y4=(value[9]>>1)+temp_y4;//  
					temp_y5=(value[10]>>1)+temp_y5;// 
					temp_y6=(value[11]>>1)+temp_y6;//
					temp_back_H1=(value[12]>>1)+temp_back_H1;//
					temp_back_H=(value[13]>>1)+temp_back_H;//
				}
}


void UP_stage()
{	
	back(speed_upstage,speed_upstage);
	delay_ms(1000);
	delay_ms(100);
	right(1000);
	delay_ms(300);
}

void speed_init(void)
{
		speed_normalx(0, 0, 1);
		speed_enemyx(0, 2, 1);
		speed_upstagex(0, 4, 1);
		OLED_ShowNum(75,0,speed_normal,4,12); 
		OLED_ShowNum(75,2,speed_enemy,4,12); 
		OLED_ShowNum(75,4,speed_upstage,4,12); 

	switch(key_num)
	{
		case 0: speed_normalx(60, 6, 0);break;
		case 1: speed_enemyx(60, 6, 0);break;
		case 2: speed_upstagex(60, 6, 0);break;		
	} 
}
