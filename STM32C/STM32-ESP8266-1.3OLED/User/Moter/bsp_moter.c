#include "bsp_Moter.h"   



static void                         Moter_GPIO_Config                  ( void );





static void Moter_GPIO_Config ( void )
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;


	/* 配置 Moter 引脚 */
	RCC_APB2PeriphClockCmd ( Moter1_GPIO_CW_CLK, ENABLE ); 															   
	GPIO_InitStructure.GPIO_Pin = Moter1_GPIO_CW_PIN ;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init ( Moter1_GPIO_CW_PORT, & GPIO_InitStructure );	
	
	RCC_APB2PeriphClockCmd ( Moter1_GPIO_BR_CLK, ENABLE ); 															   
	GPIO_InitStructure.GPIO_Pin = Moter1_GPIO_BR_PIN ;	 
	GPIO_Init ( Moter1_GPIO_BR_PORT, & GPIO_InitStructure );

	RCC_APB2PeriphClockCmd ( Moter1_GPIO_Power_CLK, ENABLE ); 															   
	GPIO_InitStructure.GPIO_Pin = Moter1_GPIO_Power_PIN ;	
	GPIO_Init ( Moter1_GPIO_Power_PORT, & GPIO_InitStructure );	

	RCC_APB2PeriphClockCmd ( Moter2_GPIO_BR_CLK, ENABLE ); 															   
	GPIO_InitStructure.GPIO_Pin = Moter2_GPIO_BR_PIN ;	 
	GPIO_Init ( Moter2_GPIO_BR_PORT, & GPIO_InitStructure );

	RCC_APB2PeriphClockCmd ( Moter2_GPIO_Power_CLK, ENABLE ); 															   
	GPIO_InitStructure.GPIO_Pin = Moter2_GPIO_Power_PIN ;	
	GPIO_Init ( Moter2_GPIO_Power_PORT, & GPIO_InitStructure );
	
	
	RCC_APB2PeriphClockCmd ( Moter2_GPIO_Power_CLK, ENABLE ); 															   
	GPIO_InitStructure.GPIO_Pin = Moter2_GPIO_Power_PIN ;	
	GPIO_Init ( Moter2_GPIO_Power_PORT, & GPIO_InitStructure );
}


 /**
  * @brief  LED 初始化函数
  * @param  无
  * @retval 无
  */
void Moter_Init ( void )
{
  Moter_GPIO_Config ();
	
	Moter1_CW_ON();//正转
	Moter1_BR_ON();//关闭刹车
	Moter1_Power_OFF();//关闭电源
	
	Moter2_CW_ON();//正转
	Moter2_BR_ON();//打开刹车
	Moter2_Power_OFF();//关闭电源
	

	
}



/*********************************************END OF FILE**********************/
