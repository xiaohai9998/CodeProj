
#include "bsp_GeneralTim3.h" 

void GENERAL_TIM3_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // ����Ƚ�ͨ��1 GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(GENERAL_TIM3_CH1_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM3_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GENERAL_TIM3_CH1_PORT, &GPIO_InitStructure);
	
	// ����Ƚ�ͨ��2 GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(GENERAL_TIM3_CH2_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM3_CH2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GENERAL_TIM3_CH2_PORT, &GPIO_InitStructure);
	
}


///*
// * ע�⣺TIM_TimeBaseInitTypeDef�ṹ��������5����Ա��TIM6��TIM7�ļĴ�������ֻ��
// * TIM_Prescaler��TIM_Period������ʹ��TIM6��TIM7��ʱ��ֻ���ʼ����������Ա���ɣ�
// * ����������Ա��ͨ�ö�ʱ���͸߼���ʱ������.
// *-----------------------------------------------------------------------------
// *typedef struct
// *{ TIM_Prescaler            ����
// *	TIM_CounterMode			     TIMx,x[6,7]û�У���������
// *  TIM_Period               ����
// *  TIM_ClockDivision        TIMx,x[6,7]û�У���������
// *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]����
// *}TIM_TimeBaseInitTypeDef; 
// *-----------------------------------------------------------------------------
// */

/* ----------------   PWM�ź� ���ں�ռ�ձȵļ���--------------- */
// ARR ���Զ���װ�ؼĴ�����ֵ
// CLK_cnt����������ʱ�ӣ����� Fck_int / (psc+1) = 72M/(psc+1)
// PWM �źŵ����� T = ARR * (1/CLK_cnt) = ARR*(PSC+1) / 72M
// ռ�ձ�P=CCR/(ARR+1)

void GENERAL_TIM3_Mode_Config(uint16_t i ,uint16_t speed)
{
  // ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
	GENERAL_TIM3_APBxClock_FUN(GENERAL_TIM3_CLK,ENABLE);

/*--------------------ʱ���ṹ���ʼ��-------------------------*/
  	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM3_Prescaler;// ���õ���Ԥ��Ƶ��������CNT��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM3_Period ;	// �Զ���װ�ؼĴ�����ֵ��������TIM_Period+1�������һ�����»����жϣ�Ȼ�����������
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�	
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	// �߼���ʱ�����У��ظ���������ֵ��������������TIM_Period+1���󲻻����һ�����»����жϣ��������ֵ��1��  �����ֵ�Ƶ��������õ�ֵ�Ż�������»��жϡ�û�õ����ù�
	TIM_TimeBaseInit(GENERAL_TIM3, &TIM_TimeBaseStructure);// ��ʼ����ʱ��
	/*--------------------����ȽϽṹ���ʼ��-------------------*/	
	// ռ�ձ�����
	uint16_t CCR1_Val;
	uint16_t CCR2_Val;
	if(i==0)
	{
		CCR1_Val=speed;
	}
	if(i==1)
	{
		CCR2_Val=speed;
	}
	if(i==2)
	{
		CCR1_Val=speed;
		CCR2_Val=speed;
	}
	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// ����Ƚ�ͨ�� 1
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	TIM_OC1Init(GENERAL_TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(GENERAL_TIM3, TIM_OCPreload_Enable);//������
	
	// ����Ƚ�ͨ�� 2
	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
	TIM_OC2Init(GENERAL_TIM3, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(GENERAL_TIM3, TIM_OCPreload_Enable);
	
	
	// ʹ�ܼ�����
	TIM_Cmd(GENERAL_TIM3, ENABLE);
}



/*********************************************END OF FILE**********************/
