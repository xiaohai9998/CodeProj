#ifndef __BSP_GENERALTIM4E_H
#define __BSP_GENERALTIM4E_H


#include "stm32f10x.h"


/************通用定时器TIM参数定义，只限TIM2、3、4、5************/
// 当使用不同的定时器的时候，对应的GPIO是不一样的，这点要注意
// 我们这里默认使用TIM5

#define            GENERAL_TIM4                   TIM4
#define            GENERAL_TIM4_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM4_CLK               RCC_APB1Periph_TIM4
#define            GENERAL_TIM4_PERIOD            0XFFFF
#define            GENERAL_TIM4_PSC              (72-1)

// TIM 输入捕获通道GPIO相关宏定义
#define            GENERAL_TIM4_CH2_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            GENERAL_TIM4_CH2_PORT          GPIOB
#define            GENERAL_TIM4_CH2_PIN           GPIO_Pin_7
#define            GENERAL_TIM4_CHANNEL_2         TIM_Channel_2

// 中断相关宏定义
#define            GENERAL_TIM4_IT_CC2            TIM_IT_CC2
#define            GENERAL_TIM4_IRQ               TIM4_IRQn
#define            GENERAL_TIM4_INT_FUN           TIM4_IRQHandler

// 获取捕获寄存器值函数宏定义
#define            GENERAL_TIM4_GetCapture2_FUN                 TIM_GetCapture2
// 捕获信号极性函数宏定义
#define            GENERAL_TIM4_OC2PolarityConfig_FUN           TIM_OC2PolarityConfig

// 测量的起始边沿
#define            GENERAL_TIM4_STRAT_ICPolarity                TIM_ICPolarity_Rising
// 测量的结束边沿
#define            GENERAL_TIM4_END_ICPolarity                  TIM_ICPolarity_Falling


// 定时器输入捕获用户自定义变量结构体声明
typedef struct
{   
	uint8_t   Capture_FinishFlag;   // 捕获结束标志位
	uint8_t   Capture_StartFlag;    // 捕获开始标志位
	uint16_t  Capture_CcrValue;     // 捕获寄存器的值
	uint16_t  Capture_Period;       // 自动重装载寄存器更新标志 
}TIM4_ICUserValueTypeDef;

extern TIM4_ICUserValueTypeDef TIM4_ICUserValueStructure;

/**************************函数声明********************************/
void GENERAL_TIM4_Init(void);


#endif	/* __BSP_GENERALTIM4E_H */


