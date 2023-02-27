#include "stdio.h"
#include "stm32f10x.h"
#include "bsp_SysTick.h"
#include "bsp_esp8266.h"
#include "test.h"
#include "bsp_moter.h"
#include "OLED4Piic.h"
#include "bsp_GeneralTim3.h"  
#include "bsp_GeneralTim2.h"  
#include "bsp_GeneralTim4.h"  
#include "bsp_usart.h"
uint16_t mo=2 ;
uint16_t mospeed=1;
extern const unsigned char FNum[];
extern const unsigned char FChineseDian[];
int main ( void )
{

	SysTick_Init ();  	
	/* ���ڳ�ʼ�� */
	USART_Config();
	IO_init();
	OLED_init();	 //���� SysTick Ϊ 1ms �ж�һ�� 	
	ESP8266_Init (); 	//��ʼ��WiFiģ��ʹ�õĽӿں�����	
	Moter_Init ();//������ɲ������ʼ��ʱ�Ǵ�ɲ����
	/* PWM��ʱ����ʼ�� */	
	GENERAL_TIM3_GPIO_Config();	
	GENERAL_TIM3_Mode_Config(mo,mospeed);		
	/* ����ʱ����ʼ�� */
	GENERAL_TIM2_Init();
	GENERAL_TIM4_Init();	
	
	OLED_clear();
  	OLED_full();	
	
  	ESP8266_StaTcpClient_UnvarnishTest ();

		
}


/*********************************************END OF FILE**********************/
