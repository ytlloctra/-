#ifndef __MPUINIT_H
#define __MPUINIT_H	 
#include "sys.h"
#include "mpu6050.h"
#include "mpuiic.h"
#include "inv_mpu.h"
#include "mpuiic.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "oled.h"

float pitch,roll,yaw,oldyaw=0,yawsta=0; 		//ŷ����
short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
short gyrox,gyroy,gyroz;	//������ԭʼ���� 
u16 j,value[9],y=0;
int mpu[6]={0},sum[6]={0},sub[6]={0};
	
void mpuinit(void);

#endif
