#ifndef __BSP_GENERALTIM2E_H
#define __BSP_GENERALTIM2E_H


#include "stm32f10x.h"


/************ͨ�ö�ʱ��TIM�������壬ֻ��TIM2��3��4��5************/
// ��ʹ�ò�ͬ�Ķ�ʱ����ʱ�򣬶�Ӧ��GPIO�ǲ�һ���ģ����Ҫע��

#define            GENERAL_TIM2                   TIM2
#define            GENERAL_TIM2_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM2_CLK               RCC_APB1Periph_TIM2
#define            GENERAL_TIM2_PERIOD            0XFFFF
#define            GENERAL_TIM2_PSC              (72-1)

// TIM ���벶��ͨ��GPIO��غ궨��
#define            GENERAL_TIM2_CH2_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM2_CH2_PORT          GPIOA
#define            GENERAL_TIM2_CH2_PIN           GPIO_Pin_1
#define            GENERAL_TIM2_CHANNEL_2         TIM_Channel_2

// �ж���غ궨��
#define            GENERAL_TIM2_IT_CC2            TIM_IT_CC2
#define            GENERAL_TIM2_IRQ               TIM2_IRQn
#define            GENERAL_TIM2_INT_FUN           TIM2_IRQHandler

// ��ȡ����Ĵ���ֵ�����궨��
#define            GENERAL_TIM2_GetCapture2_FUN                 TIM_GetCapture2
// �����źż��Ժ����궨��
#define            GENERAL_TIM2_OC2PolarityConfig_FUN           TIM_OC2PolarityConfig

// ��������ʼ����
#define            GENERAL_TIM2_STRAT_ICPolarity                TIM_ICPolarity_Rising
// �����Ľ�������
#define            GENERAL_TIM2_END_ICPolarity                  TIM_ICPolarity_Falling


// ��ʱ�����벶���û��Զ�������ṹ������
typedef struct
{   
	uint8_t   Capture_FinishFlag;   // ���������־λ
	uint8_t   Capture_StartFlag;    // ����ʼ��־λ
	uint16_t  Capture_CcrValue;     // ����Ĵ�����ֵ
	uint16_t  Capture_Period;       // �Զ���װ�ؼĴ������±�־ 
}TIM2_ICUserValueTypeDef;

extern TIM2_ICUserValueTypeDef TIM2_ICUserValueStructure;

/**************************��������********************************/
void GENERAL_TIM2_Init(void);


#endif	/* __BSP_GENERALTIM2E_H */


