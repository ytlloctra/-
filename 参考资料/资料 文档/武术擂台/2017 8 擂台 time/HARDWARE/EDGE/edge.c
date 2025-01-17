#include "edge.h"

void edge_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOF时钟

  //GPIOF9,F10初始化设置
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_11;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输出模式
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始�
}
