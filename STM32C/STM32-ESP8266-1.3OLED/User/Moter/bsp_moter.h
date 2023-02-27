#ifndef __MOTER_H_
#define	__MOTER_H_



#include "stm32f10x.h"
 
 

/****************************** Moter 引脚配置参数定义***************************************/
#define             Moter1_GPIO_CW_APBxClock_FUN              RCC_APB2PeriphClockCmd//控制正反的GPIO
#define             Moter1_GPIO_CW_CLK                        RCC_APB2Periph_GPIOB
#define             Moter1_GPIO_CW_PORT                       GPIOB
#define             Moter1_GPIO_CW_PIN                        GPIO_Pin_11

#define             Moter1_GPIO_BR_APBxClock_FUN              RCC_APB2PeriphClockCmd//控制刹车的GPIO
#define             Moter1_GPIO_BR_CLK                        RCC_APB2Periph_GPIOB
#define             Moter1_GPIO_BR_PORT                       GPIOB
#define             Moter1_GPIO_BR_PIN                        GPIO_Pin_0

#define             Moter1_GPIO_Power_APBxClock_FUN           RCC_APB2PeriphClockCmd//控制电机电源的GPIO
#define             Moter1_GPIO_Power_CLK                     RCC_APB2Periph_GPIOA
#define             Moter1_GPIO_Power_PORT                    GPIOA
#define             Moter1_GPIO_Power_PIN                     GPIO_Pin_4



#define             Moter2_GPIO_CW_APBxClock_FUN              RCC_APB2PeriphClockCmd//控制正反的GPIO
#define             Moter2_GPIO_CW_CLK                        RCC_APB2Periph_GPIOB
#define             Moter2_GPIO_CW_PORT                       GPIOB
#define             Moter2_GPIO_CW_PIN                        GPIO_Pin_3

#define             Moter2_GPIO_BR_APBxClock_FUN              RCC_APB2PeriphClockCmd//控制刹车的GPIO
#define             Moter2_GPIO_BR_CLK                        RCC_APB2Periph_GPIOB
#define             Moter2_GPIO_BR_PORT                       GPIOB
#define             Moter2_GPIO_BR_PIN                        GPIO_Pin_1

#define             Moter2_GPIO_Power_APBxClock_FUN           RCC_APB2PeriphClockCmd//控制电机电源的GPIO
#define             Moter2_GPIO_Power_CLK                     RCC_APB2Periph_GPIOA
#define             Moter2_GPIO_Power_PORT                    GPIOA
#define             Moter2_GPIO_Power_PIN                     GPIO_Pin_5

/****************************** LED 函数宏定义***************************************/
#define             Moter1_CW_OFF()                            GPIO_ResetBits ( Moter1_GPIO_CW_PORT, Moter1_GPIO_CW_PIN )
#define             Moter1_CW_ON()                           GPIO_SetBits ( Moter1_GPIO_CW_PORT, Moter1_GPIO_CW_PIN )
#define             Moter1_CW_TOGGLE()                        GPIO_ReadOutputDataBit ( Moter1_GPIO_CW_PORT, Moter1_GPIO_CW_PIN ) ? \

#define             Moter1_BR_OFF()                            GPIO_ResetBits ( Moter1_GPIO_BR_PORT, Moter1_GPIO_BR_PIN )
#define             Moter1_BR_ON()                           GPIO_SetBits ( Moter1_GPIO_BR_PORT, Moter1_GPIO_BR_PIN )
#define             Moter1_BR_TOGGLE()                        GPIO_ReadOutputDataBit (Moter1_GPIO_BR_PORT, Moter1_GPIO_BR_PIN ) ? \
                                                            GPIO_ResetBits ( Moter1_GPIO_BR_PORT, Moter1_GPIO_BR_PIN ) : GPIO_SetBits ( Moter1_GPIO_BR_PORT, Moter1_GPIO_BR_PIN )
#define             Moter1_Power_OFF()                            GPIO_ResetBits ( Moter1_GPIO_Power_PORT, Moter1_GPIO_Power_PIN )
#define             Moter1_Power_ON()                           GPIO_SetBits ( Moter1_GPIO_Power_PORT, Moter1_GPIO_Power_PIN )
#define             Moter1_Power_TOGGLE()                        GPIO_ReadOutputDataBit ( Moter1_GPIO_Power_PORT, Moter1_GPIO_Power_PIN ) ? \
																														GPIO_ResetBits ( Moter1_GPIO_Power_PORT, Moter1_GPIO_Power_PIN ) : GPIO_SetBits ( Moter1_GPIO_Power_PORT, Moter1_GPIO_Power_PIN )


#define             Moter2_CW_OFF()                            GPIO_ResetBits ( Moter2_GPIO_CW_PORT, Moter2_GPIO_CW_PIN )
#define             Moter2_CW_ON()                           GPIO_SetBits ( Moter2_GPIO_CW_PORT, Moter2_GPIO_CW_PIN )
#define             Moter2_CW_TOGGLE()                        GPIO_ReadOutputDataBit ( Moter2_GPIO_CW_PORT, Moter2_GPIO_CW_PIN ) ? \
                                                            GPIO_ResetBits ( Moter2_GPIO_CW_PORT, Moter2_GPIO_CW_PIN ) : GPIO_SetBits ( Moter2_GPIO_CW_PORT, Moter2_GPIO_CW_PIN )
#define             Moter2_BR_OFF()                            GPIO_ResetBits ( Moter2_GPIO_BR_PORT, Moter2_GPIO_BR_PIN )
#define             Moter2_BR_ON()                           GPIO_SetBits ( Moter2_GPIO_BR_PORT, Moter2_GPIO_BR_PIN )
#define             Moter2_BR_TOGGLE()                        GPIO_ReadOutputDataBit (Moter2_GPIO_BR_PORT, Moter2_GPIO_BR_PIN ) ? \

#define             Moter2_Power_OFF()                            GPIO_ResetBits ( Moter2_GPIO_Power_PORT, Moter2_GPIO_Power_PIN )
#define             Moter2_Power_ON()                           GPIO_SetBits ( Moter2_GPIO_Power_PORT, Moter2_GPIO_Power_PIN )
#define             Moter2_Power_TOGGLE()                        GPIO_ReadOutputDataBit ( Moter2_GPIO_Power_PORT, Moter2_GPIO_Power_PIN ) ? \
                                                            GPIO_ResetBits ( Moter2_GPIO_Power_PORT, Moter2_GPIO_Power_PIN ) : GPIO_SetBits ( Moter2_GPIO_Power_PORT, Moter2_GPIO_Power_PIN )																														                                    
																														
/************************** PAD 函数声明********************************/
void                               Moter_Init                         ( void );
 
 

#endif /* __MOTER_H_ */

