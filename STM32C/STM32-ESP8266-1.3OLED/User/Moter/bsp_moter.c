#include "bsp_Moter.h"   



static void                         Moter_GPIO_Config                  ( void );





static void Moter_GPIO_Config ( void )
{		
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;


	/* ���� Moter ���� */
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
  * @brief  LED ��ʼ������
  * @param  ��
  * @retval ��
  */
void Moter_Init ( void )
{
  Moter_GPIO_Config ();
	
	Moter1_CW_ON();//��ת
	Moter1_BR_ON();//�ر�ɲ��
	Moter1_Power_OFF();//�رյ�Դ
	
	Moter2_CW_ON();//��ת
	Moter2_BR_ON();//��ɲ��
	Moter2_Power_OFF();//�رյ�Դ
	

	
}



/*********************************************END OF FILE**********************/
