//////////////////////////////////////////////////////////////////////////////////
//���������ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//FLASH��������
//���ߣ�������
//�汾��V1.0
//�޸�����:2018/10/03
//
//������CAUCȭ��
//�鳤��ʷ����
//��Ա����  �� ��  �� ������ ������
//////////////////////////////////////////////////////////////////////////////////
#include "flash.h"
#include "delay.h"

#define STM_SECTOR_SIZE	2048

u16 STMFLASH_BUF[STM_SECTOR_SIZE/2];

/** 
	* @brief	��ȡָ����ַ������
	* @param	faddr		��Ҫ��ȡ���������ڵ�ַ
	* @return ��Ӧ����
	* @since	v1.0
	*/
u16 STMFLASH_ReadHalfWord(u32 faddr)
{
	return *(vu16*)faddr; 
}



/** 
	* @brief	������д��
	* @param	WriteAddr		�洢��ַ
	* @param	pBuffer			��Ҫ�洢���������ڵ�ַ
	* @param	NumToWrite	Ҫд���16λ���ݵĸ���
	* @since	v1.0
	*/
void STMFLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
{ 			 		 
	u16 i;
	for(i=0;i<NumToWrite;i++)
	{
		FLASH_ProgramHalfWord(WriteAddr,pBuffer[i]);
	    WriteAddr+=2;
	}  
} 



/** 
	* @brief	��ָ����ַ��ʼд��ָ�����ȵ�����
	* @param	WriteAddr		�洢��ַ
	* @param	pBuffer			��Ҫ�洢���������ڵ�ַ
	* @param	NumToWrite	Ҫд���16λ���ݵĸ���
	* @since	v1.0
	*/
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)	
{
	u32 secpos;	
	u16 secoff;	
	u16 secremain; 
 	u16 i;    
	u32 offaddr; 
	if(WriteAddr<STM32_FLASH_BASE||(WriteAddr>=(STM32_FLASH_BASE+1024*STM32_FLASH_SIZE)))return;
	FLASH_Unlock();
	offaddr=WriteAddr-STM32_FLASH_BASE;
	secpos=offaddr/STM_SECTOR_SIZE;
	secoff=(offaddr%STM_SECTOR_SIZE)/2;
	secremain=STM_SECTOR_SIZE/2-secoff;
	if(NumToWrite<=secremain)secremain=NumToWrite;
	while(1) 
	{	
		STMFLASH_Read(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);
		for(i=0;i<secremain;i++)
		{
			if(STMFLASH_BUF[secoff+i]!=0XFFFF)break;
		}
		if(i<secremain)
		{
			FLASH_ErasePage(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE);
			for(i=0;i<secremain;i++)
			{
				STMFLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			STMFLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);
		}else STMFLASH_Write_NoCheck(WriteAddr,pBuffer,secremain);
		if(NumToWrite==secremain)break;
		else
		{
			secpos++;	
			secoff=0;	
		   	pBuffer+=secremain;
			WriteAddr+=secremain;	
		   	NumToWrite-=secremain;
			if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;
			else secremain=NumToWrite;
		}	 
	};	
	FLASH_Lock();
}



/** 
	* @brief	��ָ����ַ��ʼ����ָ�����ȵ�����
	* @param	ReadAddr		�洢��ַ
	* @param	pBuffer			��ȡ�����ݴ�ŵ�ַ
	* @param	NumToWrite	Ҫд���16λ���ݵĸ���
	* @since	v1.0
	*/
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)   	
{
	u16 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadHalfWord(ReadAddr);
		ReadAddr+=2;
	}
}
