#ifndef __BSP_GENERALTIM3E_H
#define __BSP_GENERALTIM3E_H


#include "stm32f10x.h"


/************通用定时器TIM参数定义，只限TIM2、3、4、5************/
// 当使用不同的定时器的时候，对应的GPIO是不一样的，这点要注意
// 我们这里默认使用TIM3

#define            GENERAL_TIM3                   TIM3
#define            GENERAL_TIM3_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM3_CLK               RCC_APB1Periph_TIM3
#define            GENERAL_TIM3_Prescaler         (720-1)	// 设置的是预分频器，驱动CNT计数器的时钟 = Fck_int/(psc+1),现在是100k，是10us

//#define            GENERAL_TIM3_Period            (10-1)     //设置的重载计数器的值即PWM周期即ARR，从零计数到9，也就是说100us后产生一次更新或中断
//                                                            //Pwm = 72M/(psc+1)*(ARR+1),此PWM频率为10kHZ  
#define            GENERAL_TIM3_Period            (100-1)     //设置的重载计数器的值即PWM周期即ARR，从零计数到99，也就是说1000us后产生一次更新或中断
                                                            //Pwm = 72M/(psc+1)*(ARR+1),此PWM频率为1kHZ
                                                          
// TIM3 输出比较通道1
#define            GENERAL_TIM3_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM3_CH1_PORT          GPIOA
#define            GENERAL_TIM3_CH1_PIN           GPIO_Pin_6

// TIM3 输出比较通道2
#define            GENERAL_TIM3_CH2_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM3_CH2_PORT          GPIOA
#define            GENERAL_TIM3_CH2_PIN           GPIO_Pin_7


/**************************函数声明********************************/
void GENERAL_TIM3_GPIO_Config(void);
void GENERAL_TIM3_Mode_Config(uint16_t i ,uint16_t speed);


#endif	/* __BSP_GENERALTIM3E_H */


