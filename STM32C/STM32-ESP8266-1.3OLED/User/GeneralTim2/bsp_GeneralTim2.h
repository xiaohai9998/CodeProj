#ifndef __BSP_GENERALTIM2E_H
#define __BSP_GENERALTIM2E_H


#include "stm32f10x.h"


/************通用定时器TIM参数定义，只限TIM2、3、4、5************/
// 当使用不同的定时器的时候，对应的GPIO是不一样的，这点要注意

#define            GENERAL_TIM2                   TIM2
#define            GENERAL_TIM2_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM2_CLK               RCC_APB1Periph_TIM2
#define            GENERAL_TIM2_PERIOD            0XFFFF
#define            GENERAL_TIM2_PSC              (72-1)

// TIM 输入捕获通道GPIO相关宏定义
#define            GENERAL_TIM2_CH2_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM2_CH2_PORT          GPIOA
#define            GENERAL_TIM2_CH2_PIN           GPIO_Pin_1
#define            GENERAL_TIM2_CHANNEL_2         TIM_Channel_2

// 中断相关宏定义
#define            GENERAL_TIM2_IT_CC2            TIM_IT_CC2
#define            GENERAL_TIM2_IRQ               TIM2_IRQn
#define            GENERAL_TIM2_INT_FUN           TIM2_IRQHandler

// 获取捕获寄存器值函数宏定义
#define            GENERAL_TIM2_GetCapture2_FUN                 TIM_GetCapture2
// 捕获信号极性函数宏定义
#define            GENERAL_TIM2_OC2PolarityConfig_FUN           TIM_OC2PolarityConfig

// 测量的起始边沿
#define            GENERAL_TIM2_STRAT_ICPolarity                TIM_ICPolarity_Rising
// 测量的结束边沿
#define            GENERAL_TIM2_END_ICPolarity                  TIM_ICPolarity_Falling


// 定时器输入捕获用户自定义变量结构体声明
typedef struct
{   
	uint8_t   Capture_FinishFlag;   // 捕获结束标志位
	uint8_t   Capture_StartFlag;    // 捕获开始标志位
	uint16_t  Capture_CcrValue;     // 捕获寄存器的值
	uint16_t  Capture_Period;       // 自动重装载寄存器更新标志 
}TIM2_ICUserValueTypeDef;

extern TIM2_ICUserValueTypeDef TIM2_ICUserValueStructure;

/**************************函数声明********************************/
void GENERAL_TIM2_Init(void);


#endif	/* __BSP_GENERALTIM2E_H */


