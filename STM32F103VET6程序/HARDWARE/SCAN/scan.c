/******************* ********************
 * �ļ���  ��led.c
 * ����    ��led Ӧ�ú�����
 *          
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103C8T6
 * Ӳ�����ӣ�-----------------
 *          |   PC13 - LED1   |
 *          |       
 *          |                 |
 *           ----------------- 
 * ��汾  ��ST3.0.0  																										  
*********************************************************/
#include "scan.h"
#include "delay.h"

//C6 up  D15 down D14 mid D13 left  D12 right
 /***************  ����LED�õ���I/O�� *******************/
void mm_scan_GPIO_Config(void)	
{
 /* GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE); // ʹ��PC�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_7;	//ѡ���Ӧ������//GPIO_Pin_0|
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  //��ʼ��PC�˿�
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); // ʹ��PC�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3;	//ѡ���Ӧ������//GPIO_Pin_0|
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  //��ʼ��PC�˿�
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); // ʹ��PC�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_15;//ѡ���Ӧ������//GPIO_Pin_0|
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PC�˿�*/
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); // ʹ��PC�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_15;	//ѡ���Ӧ������//GPIO_Pin_0|
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  //��ʼ��PC�˿�
	GPIO_ResetBits(GPIOA, GPIO_Pin_13);	 // �ر�����LED
	GPIO_ResetBits(GPIOA, GPIO_Pin_15);	 // �ر�����LED
 
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE); // ʹ��PC�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;	//ѡ���Ӧ������//GPIO_Pin_0|
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  //��ʼ��PC�˿�
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE); // ʹ��PC�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	//ѡ���Ӧ������//GPIO_Pin_0|
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  //��ʼ��PC�˿�

RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); // ʹ��PC�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	//ѡ���Ӧ������//GPIO_Pin_0|
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  //��ʼ��PC�˿�

}

u8 mm_scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{			   
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == mm_OFF ) 
	  	  
		return mm_OFF;
		
	else
		return mm_ON;
}
u8 key_get(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == mm_OFF ) 
		{	
			delay_ms(20);	
			if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == mm_OFF ) 
				return mm_ON;
			//else return mm_OFF;
		}
		//return mm_OFF;
		//else
		return mm_OFF;
}
/*GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE); // ʹ��PC�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;	//ѡ���Ӧ������//GPIO_Pin_0|
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  //��ʼ��PC�˿�
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE); // ʹ��PC�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//ѡ���Ӧ������//GPIO_Pin_0|
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  //��ʼ��PC�˿�*/
