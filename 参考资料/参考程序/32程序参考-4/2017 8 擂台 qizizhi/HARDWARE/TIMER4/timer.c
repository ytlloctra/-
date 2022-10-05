#include "timer.h"
#include "usart.h"
#include "motor.h"
#include "math.h"

#define UPWARD (1400)  //1800,1300
#define FRONT (1600)  //1600,1500
#define BACK (1600)
#define SIDE (1600)
#define SCALE (2600)//huidu

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/4
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
u8 cmd=0,zisuo1=0,zisuo=0;
u16 rid,np;
double angle;
int run=0,count;
extern u16 juli[14];
const u16 fazhi[11]={UPWARD,UPWARD,FRONT,FRONT,SIDE,SIDE,SIDE,SIDE,BACK,BACK,BACK};
void TIM2_init(u32 arr,u32 psc)
{		 					 
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///??TIM3??
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//??????
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //?????
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//???TIM3
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //?????3????
	 //?????3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //???3??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //?????1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //????3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
}
void TIM2_IRQHandler(void)//�ҶȲ�����������ο���ֻ�Ƿ���
{
	//rid=(juli[10]+juli[11]+juli[12]+juli[13])/4;
	if((juli[11]>4000)||(juli[11]<3200))
		{
			np=23;
		}
		else
		{
			np=35;
		}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //???????
}
void TIM3_init(u32 arr,u32 psc)
{		 					 
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///??TIM3??
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//??????
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //?????
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//???TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //?????3????
	 //?????3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //???3??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //?????1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //????3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM3, ENABLE);
}

void TIM3_IRQHandler(void)
{
	u8 i=0;
	{
		if(zisuo==1)
		{
		if((juli[0]>fazhi[0])&&(juli[1]>fazhi[1]))
		{
			motor(32,32);//30,np+10,35
		}
		else
		{
			motor(25,25);//21,np+5
		}
		}
			if(zisuo!=1)
				{
					if(juli[0]>fazhi[0])
						{
							zisuo=1;siqu();
							motor(25,25);
						}
					else
						{
							if(juli[1]>fazhi[1])
								{
									zisuo=1;siqu();
									motor(25,25);
								}
							else
								{
									if(count>0){count--;}else {zisuo1=0;cmd=0;}
									if(zisuo1!=1)
										{
											for(i=2;i<11;i++)
												{
													if(juli[i]>fazhi[i])
													{
														cmd=i;
														zisuo1=1;
														break;
													}
												}
											if(cmd==0)
												{motor(20,20);}
											else 
											{
												count=30;
												if(cmd%2)
													{siqu();motor(-20,20);}//20
												else 
													{siqu();motor(20,-20);}
											}
										}
								}	
						}
				}
	}
//	switch(cmd)
//	{
//		case 12:motor(20,20);break;//attack
//		case 0:motor(15,15);break;//normal
//		case 2:motor(-15,15);count=1;break;
//		case 3:motor(15,-15);count=1;break;
//		case 4:motor(-15,15);count=1;break;
//		case 5:motor(15,-15);count=1;break;
//		case 6:motor(-15,15);count=1;break;
//		case 7:motor(15,-15);count=1;break;
//		case 8:motor(-15,15);count=1;break;
//		case 9:motor(15,-15);count=1;break;
//	}//�˷�����Ѱ�ҵ��˹����У�������⣬���Ի�����תһ���Ƕȣ���ʵ�飬ԭ����û��ת�����ƣ����������ٶȣ�ֹͣ����ǰ���⵽��

	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //???????
}
	

void TIM12duoji_init(u16 arr,u32 psc)
{		 					 
	//????????IO???
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);  	//TIM14????    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//??PORTF??	
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM12); //GPIOF9??????14
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//??100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //??????
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //??
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //???PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //?????
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
	TIM_TimeBaseStructure.TIM_Period=arr;   //??????
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM12,&TIM_TimeBaseStructure);//??????14
	
	//???TIM14 Channel1 PWM??	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //???????:TIM????????2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //??????
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //????:TIM???????
	TIM_OC1Init(TIM12, &TIM_OCInitStructure);  //??T??????????TIM1 4OC1

	TIM_OC1PreloadConfig(TIM12, TIM_OCPreload_Enable);  //??TIM14?CCR1????????
 
  TIM_ARRPreloadConfig(TIM12,ENABLE);//ARPE?? 
	
	TIM_Cmd(TIM12, ENABLE);  //??TIM14
 
										  
}  
void TIM4motor_init(u16 arr,u32 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM14???? 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//??PORTF??	
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM4); //GPIOF9??????14
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM4);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_4|GPIO_Pin_8|GPIO_Pin_9;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//??100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //??????
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //??
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //???PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //?????
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
	TIM_TimeBaseStructure.TIM_Period=arr;   //??????
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//??????14
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	//???TIM14 Channel1 PWM??	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //???????:TIM????????2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //??????
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //????:TIM???????
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //??T??????????TIM1 4OC1
	TIM_OC1Init(TIM3, &TIM_OCInitStructure); 
	TIM_OC3Init(TIM4, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM4, &TIM_OCInitStructure); 
	

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //??TIM14?CCR1????????
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_SetCompare1(TIM4,0);
	TIM_SetCompare1(TIM3,0);
	TIM_SetCompare3(TIM4,0);
	TIM_SetCompare4(TIM4,0);
 
  TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPE?? 
	TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPE?? 
	
	TIM_Cmd(TIM4, ENABLE);  //??TIM14
	TIM_Cmd(TIM3, ENABLE);  //??TIM14
}

  

/*TIM_ICInitTypeDef  TIM5_ICInitStructure;

//��ʱ��5ͨ��1���벶������
//arr���Զ���װֵ(TIM2,TIM5��32λ��!!)
//psc��ʱ��Ԥ��Ƶ��
void TIM5_CH1_Cap_Init(u32 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTAʱ��	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //GPIOA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA0

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //PA0����λ��ʱ��5
  
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
	

	//��ʼ��TIM5���벶�����
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  TIM_ICInit(TIM5, &TIM5_ICInitStructure);
		
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�	
	
  TIM_Cmd(TIM5,ENABLE ); 	//ʹ�ܶ�ʱ��5

 
  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
	
	
}
//����״̬
//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//[5:0]:����͵�ƽ������Ĵ���(����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
u8  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u32	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ(TIM2/TIM5��32λ)
//��ʱ��5�жϷ������	 
void TIM5_IRQHandler(void)
{ 		    

 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{
		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//���
		{	     
			if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
					TIM5CH1_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
		if(TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//����1���������¼�
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
			  TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);//��ȡ��ǰ�Ĳ���ֵ.
	 			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM5CH1_CAPTURE_STA=0;			//���
				TIM5CH1_CAPTURE_VAL=0;
				TIM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
				TIM_Cmd(TIM5,DISABLE ); 	//�رն�ʱ��5
	 			TIM_SetCounter(TIM5,0);
	 			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
				TIM_Cmd(TIM5,ENABLE ); 	//ʹ�ܶ�ʱ��5
			}		    
		}			     	    					   
 	}
	TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
}*/

