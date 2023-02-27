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
	/* 串口初始化 */
	USART_Config();
	IO_init();
	OLED_init();	 //配置 SysTick 为 1ms 中断一次 	
	ESP8266_Init (); 	//初始化WiFi模块使用的接口和外设	
	Moter_Init ();//已配置刹车，初始化时是打开刹车的
	/* PWM定时器初始化 */	
	GENERAL_TIM3_GPIO_Config();	
	GENERAL_TIM3_Mode_Config(mo,mospeed);		
	/* 捕获定时器初始化 */
	GENERAL_TIM2_Init();
	GENERAL_TIM4_Init();	
	
	OLED_clear();
  	OLED_full();	
	
  	ESP8266_StaTcpClient_UnvarnishTest ();

		
}


/*********************************************END OF FILE**********************/
