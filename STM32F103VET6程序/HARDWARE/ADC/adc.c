 #include "adc.h"
 #include "delay.h"
 #include "stm32f10x_dma.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK miniSTM32������
//ADC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
	   
	__IO uint32_t ADC1_Buff[10];	   
//��ʼ��ADC
//�������ǽ��Թ���ͨ��Ϊ��
//����Ĭ�Ͻ�����ͨ��0~3																	   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
//	DMA_InitTypeDef    DMA_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC |RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOB	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 // RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
	
/*		DMA_DeInit(DMA1_Channel1);
	 DMA_InitStructure.DMA_BufferSize=120;                                            //�������ݸ���
	 DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;                                //������Ϊ����Դ
	 DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;                                      //��ʹ���ڴ浽�ڴ�
	 DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)ADC1_Buff;           //�ڴ��д洢DMA������������ݻ���ַ
	 DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;               //�ڴ�����Ϊ���� 16λ��ADC����Ϊ12λ��
	 DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;                           //�ڴ��ַҪ����
	 DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;                                   //DMA������ѭ��ģʽ
	 DMA_InitStructure.DMA_PeripheralBaseAddr= (uint32_t)&ADC1->DR;                  //����Դ��ַ  ADC���ݼĴ�����ַ
	 DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;       //DMA�������ݿ�� 
	 DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;                  //�����ַ����
	 DMA_InitStructure.DMA_Priority=DMA_Priority_High; 	                             //DMA���ȼ���
	 DMA_Init(DMA1_Channel1, &DMA_InitStructure);                                    //DMA��ʼ��
	 DMA_Cmd(DMA1_Channel1, ENABLE);    	                                         //ʹ��DMA
       
 // DMA_Cmd(DMA1_Channel1,ENABLE);                          //??DMA??
	*/
	
	

	//PA1 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_1|GPIO_Pin_7|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//|GPIO_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOC, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 15;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   



  ADC_RegularChannelConfig(ADC1,ADC_Channel_0, 10, ADC_SampleTime_239Cycles5);//A0
 	ADC_RegularChannelConfig(ADC1,ADC_Channel_1, 9, ADC_SampleTime_239Cycles5);//A1
 	ADC_RegularChannelConfig(ADC1,ADC_Channel_2, 8, ADC_SampleTime_239Cycles5);//A2
  ADC_RegularChannelConfig(ADC1,ADC_Channel_3, 7, ADC_SampleTime_239Cycles5);//A3
	ADC_RegularChannelConfig(ADC1,ADC_Channel_4, 6, ADC_SampleTime_239Cycles5);//A4
	ADC_RegularChannelConfig(ADC1,ADC_Channel_5, 5, ADC_SampleTime_239Cycles5);//A5
	ADC_RegularChannelConfig(ADC1,ADC_Channel_6, 4, ADC_SampleTime_239Cycles5);//A6
	ADC_RegularChannelConfig(ADC1,ADC_Channel_7, 3, ADC_SampleTime_239Cycles5);//A7
  ADC_RegularChannelConfig(ADC1,ADC_Channel_8,14, ADC_SampleTime_239Cycles5);//B0
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_9,15, ADC_SampleTime_239Cycles5);//B1
	ADC_RegularChannelConfig(ADC1,ADC_Channel_10,15, ADC_SampleTime_239Cycles5);//C0
	ADC_RegularChannelConfig(ADC1,ADC_Channel_11,13, ADC_SampleTime_239Cycles5);//C1
	ADC_RegularChannelConfig(ADC1,ADC_Channel_12,12, ADC_SampleTime_239Cycles5);//C2
	ADC_RegularChannelConfig(ADC1,ADC_Channel_13,11, ADC_SampleTime_239Cycles5);//C3
	ADC_RegularChannelConfig(ADC1,ADC_Channel_14,2, ADC_SampleTime_239Cycles5);//C4
	ADC_RegularChannelConfig(ADC1,ADC_Channel_15,1, ADC_SampleTime_239Cycles5);//C5
	/*ADC_RegularChannelConfig(ADC1,ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_7, 10, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2, 2, ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(ADC1,ADC_Channel_3, 3, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_4, 4, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_6, 5, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_5, 11, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1, 6, ADC_SampleTime_239Cycles5);
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_9, 7, ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(ADC1,ADC_Channel_10,7, ADC_SampleTime_239Cycles5);
	//ADC_RegularChannelConfig(ADC1,ADC_Channel_11,1, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_12,8, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_14,9, ADC_SampleTime_239Cycles5);*/
	
  ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
	
//  ADC_DMACmd(ADC1, ENABLE);                      //ADC1 DMA?????? 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

}				  
//���ADCֵ
//ch:ͨ��ֵ 0~3
u16 Get_Adc(u8 ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	
	
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
	
}

u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	//ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
	return temp_val/times;
} 	 



























