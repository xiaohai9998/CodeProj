#ifndef __OLED4P_H_
#define	__OLED4P_H_
#include "stm32f10x.h"

/********************���ݳ�**************************����˾ģ��SDA,SCK�������������裬
*****************1.3  4PIN IIC OLED FOR STM32F103*************
*****STM32F103����**************************
***** PB5----3  SCK   ,  PB6----4  SDA   ,    
***** BY:GU 
********************************************************/

/**********SPI���ŷ��䣬����oled��������ʵ������޸�*********/

#define IIC_SCK_PIN 5
#define IIC_SDA_PIN 6

#define OLED_COLUMN_NUMBER 128
#define OLED_LINE_NUMBER 64
#define OLED_COLUMN_OFFSET 2
#define OLED_PAGE_NUMBER OLED_LINE_NUMBER/8
/**********SPI���ŷ��䣬����oled��������ʵ������޸�*********/

#define IIC_SCK_0  GPIOB->BRR=0X0020       // ����sck�ӿڵ�PB5   ����
#define IIC_SCK_1  GPIOB->BSRR=0X0020       //��λ
#define IIC_SDA_0  GPIOB->BRR=0X0040       // ����SDA�ӿڵ�PB6
#define IIC_SDA_1  GPIOB->BSRR=0X0040




/*******ʱ�ӳ�ʼ��******************/
void SYS_init(unsigned char PLL);

void IO_init(void);
void delay_us(unsigned int _us_time);

void delay_ms(unsigned int _ms_time);

/**************************IICģ�鷢�ͺ���************************************************

 *************************************************************************/
//д��  ���SDA���ߣ��Եȴ����豸����Ӧ��
void IIC_write(unsigned char date);
//�����ź�
//SCL�ڸߵ�ƽ�ڼ䣬SDA�ɸߵ�ƽ��͵�ƽ�ı仯����Ϊ�����ź�
void IIC_start();
//ֹͣ�ź�
//SCL�ڸߵ�ƽ�ڼ䣬SDA�ɵ͵�ƽ��ߵ�ƽ�ı仯����Ϊֹͣ�ź�
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
//������һҳһҳ��д����һҳ����8�м�8�����أ������Լ�Ϊ�˷����ڴ˺����涨һҳΪ16�м�16������
//��һ�������������һҳ��ʾʲô���ڶ�������������ڶ�ҳ��ʾʲô����������
void Picture_display(const unsigned char *ptr_pic);
void Picture_ReverseDisplay(const unsigned char *ptr_pic);
#endif /* __OLED4P_H_ */
