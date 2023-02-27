#ifndef __BSP_GENERALTIM4E_H
#define __BSP_GENERALTIM4E_H


#include "stm32f10x.h"


/************ͨ�ö�ʱ��TIM�������壬ֻ��TIM2��3��4��5************/
// ��ʹ�ò�ͬ�Ķ�ʱ����ʱ�򣬶�Ӧ��GPIO�ǲ�һ���ģ����Ҫע��
// ��������Ĭ��ʹ��TIM5

#define            GENERAL_TIM4                   TIM4
#define            GENERAL_TIM4_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM4_CLK               RCC_APB1Periph_TIM4
#define            GENERAL_TIM4_PERIOD            0XFFFF
#define            GENERAL_TIM4_PSC              (72-1)

// TIM ���벶��ͨ��GPIO��غ궨��
#define            GENERAL_TIM4_CH2_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            GENERAL_TIM4_CH2_PORT          GPIOB
#define            GENERAL_TIM4_CH2_PIN           GPIO_Pin_7
#define            GENERAL_TIM4_CHANNEL_2         TIM_Channel_2

// �ж���غ궨��
#define            GENERAL_TIM4_IT_CC2            TIM_IT_CC2
#define            GENERAL_TIM4_IRQ               TIM4_IRQn
#define            GENERAL_TIM4_INT_FUN           TIM4_IRQHandler

// ��ȡ����Ĵ���ֵ�����궨��
#define            GENERAL_TIM4_GetCapture2_FUN                 TIM_GetCapture2
// �����źż��Ժ����궨��
#define            GENERAL_TIM4_OC2PolarityConfig_FUN           TIM_OC2PolarityConfig

// ��������ʼ����
#define            GENERAL_TIM4_STRAT_ICPolarity                TIM_ICPolarity_Rising
// �����Ľ�������
#define            GENERAL_TIM4_END_ICPolarity                  TIM_ICPolarity_Falling


// ��ʱ�����벶���û��Զ�������ṹ������
typedef struct
{   
	uint8_t   Capture_FinishFlag;   // ���������־λ
	uint8_t   Capture_StartFlag;    // ����ʼ��־λ
	uint16_t  Capture_CcrValue;     // ����Ĵ�����ֵ
	uint16_t  Capture_Period;       // �Զ���װ�ؼĴ������±�־ 
}TIM4_ICUserValueTypeDef;

extern TIM4_ICUserValueTypeDef TIM4_ICUserValueStructure;

/**************************��������********************************/
void GENERAL_TIM4_Init(void);


#endif	/* __BSP_GENERALTIM4E_H */


