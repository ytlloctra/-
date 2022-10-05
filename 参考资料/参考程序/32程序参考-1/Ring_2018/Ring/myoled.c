#include "myoled.h"
#include "oled.h"

void GD_oled(void)
{
	int a;
	//����
  a=up_for_lift;
	OLED_ShowNum( 0,0,a,1,12);
  a=up_for_right;
	OLED_ShowNum(18,0,a,1,12);
	up_back_left;
	OLED_ShowNum(36,0,a,1,12);
	a=up_back_right;
	OLED_ShowNum(54,0,a,1,12);
	
	//ǰ
	a=for_1 ;
	OLED_ShowNum( 0,2,a,1,12);
  a=for_3;
	OLED_ShowNum(18,2,a,1,12);
	a=for_lift          ;
	OLED_ShowNum(36,2,a,1,12);
	a=for_right;
	OLED_ShowNum(54,2,a,1,12);
	
	//��
	a=left_1;
	OLED_ShowNum( 0,4,a,1,12);
  a=left_2;
	OLED_ShowNum(18,4,a,1,12);
	a=right_1;
	OLED_ShowNum(36,4,a,1,12);
	a=right_2;
	OLED_ShowNum(54,4,a,1,12);
	
	//��
	a=back_1;
	OLED_ShowNum( 0,6,a,1,12);
  a= back_2 ;
	OLED_ShowNum(18,6,a,1,12);
	a=back_lift;
	OLED_ShowNum(36,6,a,1,12);
	a= back_right;
	OLED_ShowNum(54,6,a,1,12);	
	
	delay_ms(800);//ˢ��ʱ��
	OLED_Clear();//����
	
}
void normal_oled(void)
{
   	OLED_ShowCHinese(0,0,7);  //��
		OLED_ShowCHinese(18,0,8); //��
		OLED_ShowCHinese(36,0,9); //��
		OLED_ShowCHinese(54,0,10);//��
}
//void test_oled(void)
//{
//		OLED_ShowString(0,2,"KEY1");
//		OLED_ShowCHinese(36,2,11);//��
//		OLED_ShowCHinese(54,2,12);//��
//		OLED_ShowCHinese(72,2,13);//��
//		OLED_ShowCHinese(90,2,14);//��
//}
//void ranking_oled(void)
//{
//		OLED_ShowString(0,4,"KEY2");
//		OLED_ShowCHinese(36,4,15);//��
//		OLED_ShowCHinese(54,4,16);//λ
//		OLED_ShowCHinese(72,4,17);//��
//		OLED_ShowCHinese(90,4,18);//��
//}
//void weedout_oled(void)
//{
//		OLED_ShowString(0,6,"KEY3");
//		OLED_ShowCHinese(36,6,19);//��
//		OLED_ShowCHinese(54,6,20);//̭
//		OLED_ShowCHinese(72,6,21);//��
//		OLED_ShowCHinese(90,6,22);//��
//}
//void enter_test_oled(void)
//{
//		OLED_ShowCHinese(0,3,23);//��
//		OLED_ShowCHinese(18,3,24);//��
//		OLED_ShowCHinese(36,3,11);//��
//		OLED_ShowCHinese(54,3,12);//��
//		OLED_ShowCHinese(72,3,13);//��
//		OLED_ShowCHinese(90,3,14);//��
//}
//void enter_ranking_oled(void)
//{
//		OLED_ShowCHinese(0,3,23);//��
//		OLED_ShowCHinese(18,3,24);//��
//		OLED_ShowCHinese(36,3,15);//��
//		OLED_ShowCHinese(54,3,16);//λ
//		OLED_ShowCHinese(72,3,17);//��
//		OLED_ShowCHinese(90,3,18);//��
//}
//void enter_weedout_oled(void)
//{
//		OLED_ShowCHinese(0,3,23);//��
//		OLED_ShowCHinese(18,3,24);//��
//		OLED_ShowCHinese(36,3,19);//��
//		OLED_ShowCHinese(54,3,20);//̭
//		OLED_ShowCHinese(72,3,21);//��
//		OLED_ShowCHinese(90,3,22);//��
//}
//void pitch_oled(void)
//{
//		OLED_ShowCHinese(0,2,25);//��
//		OLED_ShowCHinese(18,2,26);//��
//		OLED_ShowCHinese(36,2,27);//��
//}
//void yaw_oled(void)
//{
//		OLED_ShowCHinese(0,4,28);//ƫ
//		OLED_ShowCHinese(18,4,29);//��
//		OLED_ShowCHinese(36,4,30);//��
//}
//void roll_oled(void)
//{
//		OLED_ShowCHinese(0,6,31);//��
//		OLED_ShowCHinese(18,6,32);//��
//		OLED_ShowCHinese(36,6,33);//��
//}
//void temp_oled(void)
//{
//		OLED_ShowCHinese(0,0,34);//��
//		OLED_ShowCHinese(18,0,35);//��
//}
//void zzsp_oled(void)
//{
//		OLED_ShowCHinese(0,4,36);//��
//		OLED_ShowCHinese(18,4,37);//��
//		OLED_ShowCHinese(36,4,38);//��
//		OLED_ShowCHinese(54,4,39);//��
//}
//void cpu_oled(void)
//{
//		OLED_ShowCHinese(0,4,40);//��
//		OLED_ShowCHinese(18,4,41);//��
//		OLED_ShowCHinese(36,4,42);//ռ
//		OLED_ShowCHinese(54,4,43);//��
//		OLED_ShowCHinese(72,4,44);//��
//}
//void GDJC_oled(void)
//{
//	 	OLED_ShowString(0,0,"KEY1");
//		OLED_ShowCHinese(36,0,45);//��
//		OLED_ShowCHinese(54,0,46);//��
//		OLED_ShowCHinese(72,0,49);//��
//		OLED_ShowCHinese(90,0,50);//��
//}
//void FSJC_oled(void)
//{
//    OLED_ShowString(0,2,"KEY2");
//		OLED_ShowCHinese(36,2,51);//��
//		OLED_ShowCHinese(54,2,52);//��
//		OLED_ShowCHinese(72,2,49);//��
//		OLED_ShowCHinese(90,2,50);//��
//}
//void HDJC_oled(void)
//{
//    OLED_ShowString(0,4,"KEY3");
//		OLED_ShowCHinese(36,4,53);//��
//		OLED_ShowCHinese(54,4,54);//��
//		OLED_ShowCHinese(72,4,49);//��
//		OLED_ShowCHinese(90,4,50);//��
//}
//void enter_HDJC_oled(void)
//{
//		OLED_ShowCHinese(0,4,23);//��
//		OLED_ShowCHinese(18,4,24);//��
//		OLED_ShowCHinese(36,4,53);//��
//		OLED_ShowCHinese(54,4,54);//��
//		OLED_ShowCHinese(72,4,49);//��
//		OLED_ShowCHinese(90,4,50);//��
//}
//void enter_GDJC_oled(void)
//{
//		OLED_ShowCHinese(0,0,23);//��
//		OLED_ShowCHinese(18,0,24);//��
//		OLED_ShowCHinese(36,0,45);//��
//		OLED_ShowCHinese(54,0,46);//��
//		OLED_ShowCHinese(72,0,49);//��
//		OLED_ShowCHinese(90,0,50);//��
//}
//void enter_FSJC_oled(void)
//{
//		OLED_ShowCHinese(0,2,23);//��
//		OLED_ShowCHinese(18,2,24);//��
//		OLED_ShowCHinese(36,2,51);//��
//		OLED_ShowCHinese(54,2,52);//��
//		OLED_ShowCHinese(72,2,49);//��
//		OLED_ShowCHinese(90,2,50);//��
//}
//void GJMS_oled(void)
//{
//	 	OLED_ShowString(0,0,"KEY1");
//		OLED_ShowCHinese(36,0,55);//��
//		OLED_ShowCHinese(54,0,56);//��
//		OLED_ShowCHinese(72,0,57);//ģ
//		OLED_ShowCHinese(90,0,58);//ʽ
//}
//void FYMS_oled(void)
//{
//    OLED_ShowString(0,2,"KEY2");
//		OLED_ShowCHinese(36,2,59);//��
//		OLED_ShowCHinese(54,2,60);//��
//		OLED_ShowCHinese(72,2,57);//ģ
//		OLED_ShowCHinese(90,2,58);//ʽ
//}
//void BBMS_oled(void)
//{
//    OLED_ShowString(0,4,"KEY3");
//		OLED_ShowCHinese(36,4,61);//��
//		OLED_ShowCHinese(54,4,62);//��
//		OLED_ShowCHinese(72,4,57);//ģ
//		OLED_ShowCHinese(90,4,58);//ʽ
//}
//void enter_GJMS_oled(void)
//{
//		OLED_ShowCHinese(0,4,23);//��
//		OLED_ShowCHinese(18,4,24);//��
//		OLED_ShowCHinese(36,4,55);//��
//		OLED_ShowCHinese(54,4,56);//��
//		OLED_ShowCHinese(72,4,57);//ģ
//		OLED_ShowCHinese(90,4,58);//ʽ
//}
//void enter_FYMS_oled(void)
//{
//		OLED_ShowCHinese(0,0,23);//��
//		OLED_ShowCHinese(18,0,24);//��
//		OLED_ShowCHinese(36,0,59);//��
//		OLED_ShowCHinese(54,0,60);//��
//		OLED_ShowCHinese(72,0,57);//ģ
//		OLED_ShowCHinese(90,0,58);//ʽ
//}
//void enter_BBMS_oled(void)
//{
//		OLED_ShowCHinese(0,2,23);//��
//		OLED_ShowCHinese(18,2,24);//��
//		OLED_ShowCHinese(36,2,61);//��
//		OLED_ShowCHinese(54,2,62);//��
//		OLED_ShowCHinese(72,2,57);//ģ
//		OLED_ShowCHinese(90,2,58);//ʽ
//}







