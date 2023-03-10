
#include "bsp_GeneralTim3.h" 

void GENERAL_TIM3_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // 输出比较通道1 GPIO 初始化
	RCC_APB2PeriphClockCmd(GENERAL_TIM3_CH1_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM3_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GENERAL_TIM3_CH1_PORT, &GPIO_InitStructure);
	
	// 输出比较通道2 GPIO 初始化
	RCC_APB2PeriphClockCmd(GENERAL_TIM3_CH2_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM3_CH2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GENERAL_TIM3_CH2_PORT, &GPIO_InitStructure);
	
}


///*
// * 注意：TIM_TimeBaseInitTypeDef结构体里面有5个成员，TIM6和TIM7的寄存器里面只有
// * TIM_Prescaler和TIM_Period，所以使用TIM6和TIM7的时候只需初始化这两个成员即可，
// * 另外三个成员是通用定时器和高级定时器才有.
// *-----------------------------------------------------------------------------
// *typedef struct
// *{ TIM_Prescaler            都有
// *	TIM_CounterMode			     TIMx,x[6,7]没有，其他都有
// *  TIM_Period               都有
// *  TIM_ClockDivision        TIMx,x[6,7]没有，其他都有
// *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]才有
// *}TIM_TimeBaseInitTypeDef; 
// *-----------------------------------------------------------------------------
// */

/* ----------------   PWM信号 周期和占空比的计算--------------- */
// ARR ：自动重装载寄存器的值
// CLK_cnt：计数器的时钟，等于 Fck_int / (psc+1) = 72M/(psc+1)
// PWM 信号的周期 T = ARR * (1/CLK_cnt) = ARR*(PSC+1) / 72M
// 占空比P=CCR/(ARR+1)

void GENERAL_TIM3_Mode_Config(uint16_t i ,uint16_t speed)
{
  // 开启定时器时钟,即内部时钟CK_INT=72M
	GENERAL_TIM3_APBxClock_FUN(GENERAL_TIM3_CLK,ENABLE);

/*--------------------时基结构体初始化-------------------------*/
  	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM3_Prescaler;// 配置的是预分频器，驱动CNT计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM3_Period ;	// 自动重装载寄存器的值，计数到TIM_Period+1个后产生一个更新或者中断，然后计数器清零
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		// 时钟分频因子 ，配置死区时间时需要用到	
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	// 高级定时器才有，重复计数器的值，计数器计数到TIM_Period+1个后不会产生一个更新或者中断，而是这个值加1。  当这个值计到我们设置的值才会产生更新或中断。没用到不用管
	TIM_TimeBaseInit(GENERAL_TIM3, &TIM_TimeBaseStructure);// 初始化定时器
	/*--------------------输出比较结构体初始化-------------------*/	
	// 占空比配置
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
	// 配置为PWM模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// 输出比较通道 1
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	TIM_OC1Init(GENERAL_TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(GENERAL_TIM3, TIM_OCPreload_Enable);//有问题
	
	// 输出比较通道 2
	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
	TIM_OC2Init(GENERAL_TIM3, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(GENERAL_TIM3, TIM_OCPreload_Enable);
	
	
	// 使能计数器
	TIM_Cmd(GENERAL_TIM3, ENABLE);
}



/*********************************************END OF FILE**********************/
