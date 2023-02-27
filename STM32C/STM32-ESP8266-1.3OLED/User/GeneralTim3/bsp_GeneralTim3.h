#ifndef __BSP_GENERALTIM3E_H
#define __BSP_GENERALTIM3E_H


#include "stm32f10x.h"


/************ͨ�ö�ʱ��TIM�������壬ֻ��TIM2��3��4��5************/
// ��ʹ�ò�ͬ�Ķ�ʱ����ʱ�򣬶�Ӧ��GPIO�ǲ�һ���ģ����Ҫע��
// ��������Ĭ��ʹ��TIM3

#define            GENERAL_TIM3                   TIM3
#define            GENERAL_TIM3_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM3_CLK               RCC_APB1Periph_TIM3
#define            GENERAL_TIM3_Prescaler         (720-1)	// ���õ���Ԥ��Ƶ��������CNT��������ʱ�� = Fck_int/(psc+1),������100k����10us

//#define            GENERAL_TIM3_Period            (10-1)     //���õ����ؼ�������ֵ��PWM���ڼ�ARR�����������9��Ҳ����˵100us�����һ�θ��»��ж�
//                                                            //Pwm = 72M/(psc+1)*(ARR+1),��PWMƵ��Ϊ10kHZ  
#define            GENERAL_TIM3_Period            (100-1)     //���õ����ؼ�������ֵ��PWM���ڼ�ARR�����������99��Ҳ����˵1000us�����һ�θ��»��ж�
                                                            //Pwm = 72M/(psc+1)*(ARR+1),��PWMƵ��Ϊ1kHZ
                                                          
// TIM3 ����Ƚ�ͨ��1
#define            GENERAL_TIM3_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM3_CH1_PORT          GPIOA
#define            GENERAL_TIM3_CH1_PIN           GPIO_Pin_6

// TIM3 ����Ƚ�ͨ��2
#define            GENERAL_TIM3_CH2_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM3_CH2_PORT          GPIOA
#define            GENERAL_TIM3_CH2_PIN           GPIO_Pin_7


/**************************��������********************************/
void GENERAL_TIM3_GPIO_Config(void);
void GENERAL_TIM3_Mode_Config(uint16_t i ,uint16_t speed);


#endif	/* __BSP_GENERALTIM3E_H */


