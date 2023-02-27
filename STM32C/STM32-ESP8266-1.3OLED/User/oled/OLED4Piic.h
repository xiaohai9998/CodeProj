#ifndef __OLED4P_H_
#define	__OLED4P_H_
#include "stm32f10x.h"

/********************金逸晨**************************本公司模块SDA,SCK已内置上拉电阻，
*****************1.3  4PIN IIC OLED FOR STM32F103*************
*****STM32F103驱动**************************
***** PB5----3  SCK   ,  PB6----4  SDA   ,    
***** BY:GU 
********************************************************/

/**********SPI引脚分配，连接oled屏，更具实际情况修改*********/

#define IIC_SCK_PIN 5
#define IIC_SDA_PIN 6

#define OLED_COLUMN_NUMBER 128
#define OLED_LINE_NUMBER 64
#define OLED_COLUMN_OFFSET 2
#define OLED_PAGE_NUMBER OLED_LINE_NUMBER/8
/**********SPI引脚分配，连接oled屏，更具实际情况修改*********/

#define IIC_SCK_0  GPIOB->BRR=0X0020       // 设置sck接口到PB5   清零
#define IIC_SCK_1  GPIOB->BSRR=0X0020       //置位
#define IIC_SDA_0  GPIOB->BRR=0X0040       // 设置SDA接口到PB6
#define IIC_SDA_1  GPIOB->BSRR=0X0040




/*******时钟初始化******************/
void SYS_init(unsigned char PLL);

void IO_init(void);
void delay_us(unsigned int _us_time);

void delay_ms(unsigned int _ms_time);

/**************************IIC模块发送函数************************************************

 *************************************************************************/
//写入  最后将SDA拉高，以等待从设备产生应答
void IIC_write(unsigned char date);
//启动信号
//SCL在高电平期间，SDA由高电平向低电平的变化定义为启动信号
void IIC_start();
//停止信号
//SCL在高电平期间，SDA由低电平向高电平的变化定义为停止信号
void IIC_stop();
void OLED_send_cmd(unsigned char o_command);
void OLED_send_data(unsigned char o_data);
void Column_set(unsigned char column);
void Page_set(unsigned char page);
void OLED_clear(void);
void OLED_full(void);
void OLED_init(void);
void OLED_ShowCharChinese(uint8_t x,uint8_t y,const unsigned char *chr);
void OLED_ShowChar(uint8_t x,uint8_t y,const unsigned char *chr);
void OLED_ShowPage(uint8_t x,const unsigned char *chr);
void BPage_display(const unsigned char *ptr_pic0,const unsigned char *ptr_pic1,const unsigned char *ptr_pic2,const unsigned char *ptr_pic3);
//而我是一页一页的写下面一页代表8行即8各像素，而我自己为了方便在此函数规定一页为16行即16各像素
//第一个参数，代表第一页显示什么，第二个参数，代表第二页显示什么。。。。。
void Picture_display(const unsigned char *ptr_pic);
void Picture_ReverseDisplay(const unsigned char *ptr_pic);
#endif /* __OLED4P_H_ */
