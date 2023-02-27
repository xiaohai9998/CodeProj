
/********************���ݳ�**************************����˾ģ��SDA,SCK�������������裬
*****************1.3  4PIN IIC OLED FOR STM32F103*************
*****STM32F103����**************************
***** PB5----3  SCK   ,  PB6----4  SDA   ,    
***** BY:GU 
********************************************************/
#include "OLED4Piic.h"
const unsigned char  OLED_init_cmd[25]=			//SH1106
{
  
  /*0xae,0X00,0X10,0x40,0X81,0XCF,0xff,0xa1,0xa4,
  0xA6,0xc8,0xa8,0x3F,0xd5,0x80,0xd3,0x00,0XDA,0X12,
  0x8d,0x14,0xdb,0x40,0X20,0X02,0xd9,0xf1,0xAF*/
       0xAE,//�ر���ʾ
	
       0xD5,//����ʱ�ӷ�Ƶ����,��Ƶ��
       0x80,  //[3:0],��Ƶ����;[7:4],��Ƶ��

       0xA8,//��������·��
       0X3F,//Ĭ��(1/64)
	
       0xD3,//������ʾƫ��
       0X00,//Ĭ��Ϊ0
	
       0x40,//������ʾ��ʼ�� [5:0],����.
	
       0x8D,//��ɱ�����
       0x14,//bit2������/�ر�
       0x20,//�����ڴ��ַģʽ
       0x02,//[1:0],00���е�ַģʽ;01���е�ַģʽ;10,ҳ��ַģʽ;Ĭ��10;
       0xA1,//���ض�������,bit0:0,0->0;1,0->127;  A1
	
       0xC8,//����COMɨ�跽��;bit3:0,��ͨģʽ;1,�ض���ģʽ COM[N-1]->COM0;N:����·�� (C0 ��ת��ʾ) C8
	   
       0xDA,//����COMӲ����������
       0x12,//[5:4]����  
	   
       0x81,//�Աȶ�����
       0x66,//1~255;Ĭ��0X7F (��������,Խ��Խ��)
	   
       0xD9,//����Ԥ�������
       0xf1,//[3:0],PHASE 1;[7:4],PHASE 2;
	   
       0xDB,//����VCOMH ��ѹ����
       0x30,//[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;
	   
       0xA4,//ȫ����ʾ����;bit0:1,����;0,�ر�;(����/����)
	   
       0xA6,//������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ 
       
       0xAF,//������ʾ     
};


unsigned char ACK=0;
/*******ʱ�ӳ�ʼ��******************/
void SYS_init(unsigned char PLL)
{
	
		 
	RCC->APB1RSTR = 0x00000000;//��λ����			 
	RCC->APB2RSTR = 0x00000000; 	  
  	RCC->AHBENR = 0x00000014;  //˯��ģʽ�����SRAMʱ��ʹ��.�����ر�.	  
  	RCC->APB2ENR = 0x00000000; //����ʱ�ӹر�.			   
  	RCC->APB1ENR = 0x00000000;   
	RCC->CR |= 0x00000001;     //ʹ���ڲ�����ʱ��HSION
	
	RCC->CFGR &= 0xF8FF0000;   //��λSW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]					 
	RCC->CR &= 0xFEF6FFFF;     //��λHSEON,CSSON,PLLON
	RCC->CR &= 0xFFFBFFFF;     //��λHSEBYP	   	  
	RCC->CFGR &= 0xFF80FFFF;   //��λPLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE
	while(((RCC->CFGR>>2)& 0x03 )!=0x00); 	
	RCC->CIR = 0x00000000;     //�ر������ж�		 
	//����������				  
  
//	SCB->VTOR = 0x08000000|(0x0 & (u32)0x1FFFFF80);//����NVIC��������ƫ�ƼĴ���
	
 	RCC->CR|=0x00010000;  //�ⲿ����ʱ��ʹ��HSEON
	while(((RCC->CR>>17)&0x00000001)==0);//�ȴ��ⲿʱ�Ӿ���
	RCC->CFGR=0X00000400; //APB1=DIV2;APB2=DIV1;AHB=DIV1;
	PLL-=2;//����2����λ
	RCC->CFGR|=PLL<<18;   //����PLLֵ 2~16
	RCC->CFGR|=1<<16;	  //PLLSRC ON 
	

	RCC->CR|=0x01000000;  //PLLON
	while(!(RCC->CR>>25));//�ȴ�PLL����
	RCC->CFGR|=0x00000002;//PLL��Ϊϵͳʱ��	 
	while(((RCC->CFGR>>2)&0x03)!=0x02);   //�ȴ�PLL��Ϊϵͳʱ�����óɹ�
	
	
}

void IO_init(void)
{
	RCC->APB2ENR|=1<<3;    //ʹ��PORTBʱ�� 
	GPIOB->CRL&=0X00FFFFFF;				//��B56������Ϊͨ�ÿ�©���,���50MH
	GPIOB->CRL|=0X07700000;				//B7����Ϊͨ���������,���50MH
	GPIOB->ODR=0XFFFF;
}
void delay_us(unsigned int _us_time)
{       
  unsigned char x=0;
  for(;_us_time>0;_us_time--)
  {
    x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;
	  x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;
	  
  }
}

void delay_ms(unsigned int _ms_time)
  {
    unsigned int i,j;
    for(i=0;i<_ms_time;i++)
    {
    for(j=0;j<900;j++)
      {;}
    }
  }

/**************************IICģ�鷢�ͺ���************************************************

 *************************************************************************/
//д��  ���SDA���ߣ��Եȴ����豸����Ӧ��
void IIC_write(unsigned char date)
{
	unsigned char i, temp;
	temp = date;
			
	for(i=0; i<8; i++)
	{	IIC_SCK_0;
		
        if ((temp&0x80)==0)
            IIC_SDA_0;
        else IIC_SDA_1;
		temp = temp << 1;
		delay_us(1);			  
		IIC_SCK_1;
		delay_us(1);
		
	}
	IIC_SCK_0;
	delay_us(1);
	IIC_SDA_1;
	delay_us(1);
	IIC_SCK_1;
//								����ҪӦ��
//	if (READ_SDA==0)
//		ACK = 1;
//	else ACK =0;
	delay_us(1);
	IIC_SCK_0;
	delay_us(1);
	

}
//�����ź�
//SCL�ڸߵ�ƽ�ڼ䣬SDA�ɸߵ�ƽ��͵�ƽ�ı仯����Ϊ�����ź�
void IIC_start()
{
	IIC_SDA_1;
	delay_us(1);
	IIC_SCK_1;
	delay_us(1);				   //���в��������ͷ�SCL	
	IIC_SDA_0;
	delay_us(3);
	IIC_SCK_0;
	
        IIC_write(0x78);
        
}

//ֹͣ�ź�
//SCL�ڸߵ�ƽ�ڼ䣬SDA�ɵ͵�ƽ��ߵ�ƽ�ı仯����Ϊֹͣ�ź�
void IIC_stop()
{
	IIC_SDA_0;
	delay_us(1);
	IIC_SCK_1;
	delay_us(3);
	IIC_SDA_1;
	
}

void OLED_send_cmd(unsigned char o_command)
  {
    
    IIC_start();
    IIC_write(0x00); 
    IIC_write(o_command);
    IIC_stop();
    
  }
void OLED_send_data(unsigned char o_data)
  { 
    IIC_start();
    IIC_write(0x40);
    IIC_write(o_data);
    IIC_stop();
   }
void Column_set(unsigned char column)
  {
	column+=OLED_COLUMN_OFFSET;
    OLED_send_cmd(0x10|(column>>4));    //�����е�ַ��λ
    OLED_send_cmd(0x00|(column&0x0f));   //�����е�ַ��λ  
    	 
  }
void Page_set(unsigned char page)
  {
    OLED_send_cmd(0xb0+page);
  }
	
/*һҳ����8�����أ���ѡ���һҳ��Ȼ�������еĵ�ַ��λ�͵�ַ��λ������0���Լ���127�У������ĺ�����
	Ȼ�����0ҳ��0��д��һ�ֽڣ�8λ�������ݣ�Ȼ��������һ�����0ҳ��1��д��һ�ֽڣ�8λ�������ݣ�ֱ��д�����
	ҳ����һ������д��ֱ��ҳ�������*/
void OLED_clear(void)
  {
    unsigned char page,column;
    for(page=0;page<OLED_PAGE_NUMBER;page++)             //page loop
      { 
          Page_set(page);
          Column_set(0);	  
          for(column=0;column<OLED_COLUMN_NUMBER;column++)	//column loop
            {
              OLED_send_data(0x00);
            }
      }
  }
void OLED_full(void)
  {
    unsigned char page,column;
    for(page=0;page<OLED_PAGE_NUMBER;page++)             //page loop
      { 
        Page_set(page);
        Column_set(0);	  
	for(column=0;column<OLED_COLUMN_NUMBER;column++)	//column loop
          {
            OLED_send_data(0xff);
          }
      }
  }
void OLED_init(void)
  {
    unsigned char i;
    for(i=0;i<25;i++)
      {
        OLED_send_cmd(OLED_init_cmd[i]);
      }
  }
//��ָ��λ����ʾһ�������ַ���x�����У�y�����С�xȡֵΪ1~4��yȡֵΪ1~8
//��һ��64�����أ���һ��128�����أ��ҹ涨��һ��ռ16�����أ�һ��ռ16�����أ���4��8��
void OLED_ShowCharChinese(uint8_t x,uint8_t y,const unsigned char *chr)
{      	

	
    unsigned char column;
		unsigned char page;
//		�Ե����ַ�����Ҫ ����ַ���ֱ��д���У�����������Ļ���϶�Ҫ��������е��ַ�

    for(page=(x-1)*2;page<x*2;page++)        //page loop д���ַ�
      {
				Page_set(page);				
				Column_set((y-1)*8);	  
				for(column=0;column<16;column++)	//column loop
          {
            OLED_send_data(*chr++);//F8X16��һ��16�������Եڶ����ǣ�����ô���׵�ַΪc*16+columnΪ16��
          }
      }
			
			
}
//��ָ��λ����ʾһ��Ӣ���ַ������֣�x�����У�y�����С�xȡֵΪ1~4��yȡֵΪ1~16
//��һ��64�����أ���һ��128�����أ��ҹ涨��һ��ռ16�����أ�һ��ռ8�����أ���4��16�У��˺������������ģ�
void OLED_ShowChar(uint8_t x,uint8_t y,const unsigned char *chr)
{      	

	
    unsigned char column;
		unsigned char page;
//		�Ե����ַ�����Ҫ ����ַ���ֱ��д���У�����������Ļ���϶�Ҫ��������е��ַ�

    for(page=(x-1)*2;page<x*2;page++)        //page loop д���ַ�
      {
				Page_set(page);				
				Column_set((y-1)*8);	  
				for(column=0;column<8;column++)	//column loop
          {
            OLED_send_data(*chr++);//F8X16��һ��16�������Եڶ����ǣ�����ô���׵�ַΪc*16+columnΪ16��
          }
      }
			
			
}

void OLED_ShowPage(uint8_t x,const unsigned char *chr)
{  //��һ�������������ǵڼ�ҳ���ڶ���������������ʾʲô����������   xȡֵΪ1~4 	
//û��Ҫ�������һ�У�д��ʱ����Ѿ������
	
    unsigned char column;
		unsigned char page;

    for(page=(x-1)*2;page<x*2;page++)        //page loop
      { 
				Page_set(page);
				Column_set(0);	  
				for(column=0;column<OLED_COLUMN_NUMBER;column++)	//column loop
          {
            OLED_send_data(*chr++);
          }
      }
			
}

void BPage_display(const unsigned char *ptr_pic0,const unsigned char *ptr_pic1,const unsigned char *ptr_pic2,const unsigned char *ptr_pic3)
//����ĺ���Picture_display��һ����д����Ļ���������أ�
//������һҳһҳ��д����һҳ����8�м�8�����أ������Լ�Ϊ�˷����ڴ˺����涨һҳΪ16�м�16�����أ���4ҳ����ʵҲ����4��.
//д��ʱ����д���һС��8�����أ���д��ڶ�С��8������
//��һ�������������ǵ�һҳ��ʾʲô���ڶ�������������ڶ�ҳ��ʾʲô����������.
  {
    unsigned char column;
		unsigned char Bpage=0;
    for(;Bpage<2;Bpage++)        //page loop
      { 
				Page_set(Bpage);
				Column_set(0);	  
				for(column=0;column<OLED_COLUMN_NUMBER;column++)	//column loop
          {
            OLED_send_data(*ptr_pic0++);
          }
      }
			
		for(;Bpage<4;Bpage++)        //page loop
      { 
				Page_set(Bpage);
				Column_set(0);	  
				for(column=0;column<OLED_COLUMN_NUMBER;column++)	//column loop
					{
						OLED_send_data(*ptr_pic1++);
					}
      }
    for(;Bpage<6;Bpage++)        //page loop
      { 
				Page_set(Bpage);
				Column_set(0);	  
				for(column=0;column<OLED_COLUMN_NUMBER;column++)	//column loop
					{
						OLED_send_data(*ptr_pic2++);
					}
      }			
    for(;Bpage<8;Bpage++)        //page loop
      { 
				Page_set(Bpage);
				Column_set(0);	  
				for(column=0;column<OLED_COLUMN_NUMBER;column++)	//column loop
					{
						OLED_send_data(*ptr_pic3++);
					}
      }			

			
  }
	
	
void Picture_display(const unsigned char *ptr_pic)
  {
    unsigned char page,column;
    for(page=0;page<(OLED_LINE_NUMBER/8);page++)        //page loop
      { 
	Page_set(page);
	Column_set(0);	  
	for(column=0;column<OLED_COLUMN_NUMBER;column++)	//column loop
          {
            OLED_send_data(*ptr_pic++);
          }
      }
  }
void Picture_ReverseDisplay(const unsigned char *ptr_pic)
{
    unsigned char page,column,data;
    for(page=0;page<(OLED_LINE_NUMBER/8);page++)        //page loop
      { 
	Page_set(page);
	Column_set(0);	  
	for(column=0;column<OLED_COLUMN_NUMBER;column++)	//column loop
          {
            data=*ptr_pic++;
            data=~data;
            OLED_send_data(data);
          }
      }
  }


