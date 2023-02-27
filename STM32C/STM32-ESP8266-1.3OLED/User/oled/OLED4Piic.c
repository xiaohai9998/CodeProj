
/********************金逸晨**************************本公司模块SDA,SCK已内置上拉电阻，
*****************1.3  4PIN IIC OLED FOR STM32F103*************
*****STM32F103驱动**************************
***** PB5----3  SCK   ,  PB6----4  SDA   ,    
***** BY:GU 
********************************************************/
#include "OLED4Piic.h"
const unsigned char  OLED_init_cmd[25]=			//SH1106
{
  
  /*0xae,0X00,0X10,0x40,0X81,0XCF,0xff,0xa1,0xa4,
  0xA6,0xc8,0xa8,0x3F,0xd5,0x80,0xd3,0x00,0XDA,0X12,
  0x8d,0x14,0xdb,0x40,0X20,0X02,0xd9,0xf1,0xAF*/
       0xAE,//关闭显示
	
       0xD5,//设置时钟分频因子,震荡频率
       0x80,  //[3:0],分频因子;[7:4],震荡频率

       0xA8,//设置驱动路数
       0X3F,//默认(1/64)
	
       0xD3,//设置显示偏移
       0X00,//默认为0
	
       0x40,//设置显示开始行 [5:0],行数.
	
       0x8D,//电荷泵设置
       0x14,//bit2，开启/关闭
       0x20,//设置内存地址模式
       0x02,//[1:0],00，列地址模式;01，行地址模式;10,页地址模式;默认10;
       0xA1,//段重定义设置,bit0:0,0->0;1,0->127;  A1
	
       0xC8,//设置COM扫描方向;bit3:0,普通模式;1,重定义模式 COM[N-1]->COM0;N:驱动路数 (C0 翻转显示) C8
	   
       0xDA,//设置COM硬件引脚配置
       0x12,//[5:4]配置  
	   
       0x81,//对比度设置
       0x66,//1~255;默认0X7F (亮度设置,越大越亮)
	   
       0xD9,//设置预充电周期
       0xf1,//[3:0],PHASE 1;[7:4],PHASE 2;
	   
       0xDB,//设置VCOMH 电压倍率
       0x30,//[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;
	   
       0xA4,//全局显示开启;bit0:1,开启;0,关闭;(白屏/黑屏)
	   
       0xA6,//设置显示方式;bit0:1,反相显示;0,正常显示 
       
       0xAF,//开启显示     
};


unsigned char ACK=0;
/*******时钟初始化******************/
void SYS_init(unsigned char PLL)
{
	
		 
	RCC->APB1RSTR = 0x00000000;//复位结束			 
	RCC->APB2RSTR = 0x00000000; 	  
  	RCC->AHBENR = 0x00000014;  //睡眠模式闪存和SRAM时钟使能.其他关闭.	  
  	RCC->APB2ENR = 0x00000000; //外设时钟关闭.			   
  	RCC->APB1ENR = 0x00000000;   
	RCC->CR |= 0x00000001;     //使能内部高速时钟HSION
	
	RCC->CFGR &= 0xF8FF0000;   //复位SW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]					 
	RCC->CR &= 0xFEF6FFFF;     //复位HSEON,CSSON,PLLON
	RCC->CR &= 0xFFFBFFFF;     //复位HSEBYP	   	  
	RCC->CFGR &= 0xFF80FFFF;   //复位PLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE
	while(((RCC->CFGR>>2)& 0x03 )!=0x00); 	
	RCC->CIR = 0x00000000;     //关闭所有中断		 
	//配置向量表				  
  
//	SCB->VTOR = 0x08000000|(0x0 & (u32)0x1FFFFF80);//设置NVIC的向量表偏移寄存器
	
 	RCC->CR|=0x00010000;  //外部高速时钟使能HSEON
	while(((RCC->CR>>17)&0x00000001)==0);//等待外部时钟就绪
	RCC->CFGR=0X00000400; //APB1=DIV2;APB2=DIV1;AHB=DIV1;
	PLL-=2;//抵消2个单位
	RCC->CFGR|=PLL<<18;   //设置PLL值 2~16
	RCC->CFGR|=1<<16;	  //PLLSRC ON 
	

	RCC->CR|=0x01000000;  //PLLON
	while(!(RCC->CR>>25));//等待PLL锁定
	RCC->CFGR|=0x00000002;//PLL作为系统时钟	 
	while(((RCC->CFGR>>2)&0x03)!=0x02);   //等待PLL作为系统时钟设置成功
	
	
}

void IO_init(void)
{
	RCC->APB2ENR|=1<<3;    //使能PORTB时钟 
	GPIOB->CRL&=0X00FFFFFF;				//将B56口配置为通用开漏输出,最大50MH
	GPIOB->CRL|=0X07700000;				//B7配置为通用推挽输出,最大50MH
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

/**************************IIC模块发送函数************************************************

 *************************************************************************/
//写入  最后将SDA拉高，以等待从设备产生应答
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
//								不需要应答
//	if (READ_SDA==0)
//		ACK = 1;
//	else ACK =0;
	delay_us(1);
	IIC_SCK_0;
	delay_us(1);
	

}
//启动信号
//SCL在高电平期间，SDA由高电平向低电平的变化定义为启动信号
void IIC_start()
{
	IIC_SDA_1;
	delay_us(1);
	IIC_SCK_1;
	delay_us(1);				   //所有操作结束释放SCL	
	IIC_SDA_0;
	delay_us(3);
	IIC_SCK_0;
	
        IIC_write(0x78);
        
}

//停止信号
//SCL在高电平期间，SDA由低电平向高电平的变化定义为停止信号
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
    OLED_send_cmd(0x10|(column>>4));    //设置列地址高位
    OLED_send_cmd(0x00|(column&0x0f));   //设置列地址低位  
    	 
  }
void Page_set(unsigned char page)
  {
    OLED_send_cmd(0xb0+page);
  }
	
/*一页代表8个像素，先选择第一页，然后设置列的地址地位和地址高位，即第0列以及第127列，见上文函数，
	然后向第0页第0列写入一字节（8位）的数据，然后列数加一，向第0页第1列写入一字节（8位）的数据，直到写到最后
	页数加一，继续写。直到页数到最后*/
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
//在指定位置显示一个中文字符，x代表行，y代表列。x取值为1~4，y取值为1~8
//高一共64个像素，列一共128个像素，我规定，一行占16个像素，一列占16个像素，共4行8列
void OLED_ShowCharChinese(uint8_t x,uint8_t y,const unsigned char *chr)
{      	

	
    unsigned char column;
		unsigned char page;
//		对单个字符不需要 清除字符，直接写就行，而对整个屏幕，肯定要先清空所有的字符

    for(page=(x-1)*2;page<x*2;page++)        //page loop 写入字符
      {
				Page_set(page);				
				Column_set((y-1)*8);	  
				for(column=0;column<16;column++)	//column loop
          {
            OLED_send_data(*chr++);//F8X16中一行16个，所以第二行是！，那么，首地址为c*16+column为16，
          }
      }
			
			
}
//在指定位置显示一个英文字符或数字，x代表行，y代表列。x取值为1~4，y取值为1~16
//高一共64个像素，列一共128个像素，我规定，一行占16个像素，一列占8个像素，共4行16列（此函数不适用中文）
void OLED_ShowChar(uint8_t x,uint8_t y,const unsigned char *chr)
{      	

	
    unsigned char column;
		unsigned char page;
//		对单个字符不需要 清除字符，直接写就行，而对整个屏幕，肯定要先清空所有的字符

    for(page=(x-1)*2;page<x*2;page++)        //page loop 写入字符
      {
				Page_set(page);				
				Column_set((y-1)*8);	  
				for(column=0;column<8;column++)	//column loop
          {
            OLED_send_data(*chr++);//F8X16中一行16个，所以第二行是！，那么，首地址为c*16+column为16，
          }
      }
			
			
}

void OLED_ShowPage(uint8_t x,const unsigned char *chr)
{  //第一个参数，代表是第几页，第二个参数，代表显示什么。。。。。   x取值为1~4 	
//没必要先清楚这一行，写的时候就已经清除了
	
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
//下面的函数Picture_display是一次性写完屏幕上所有像素，
//而我是一页一页的写下面一页代表8行即8各像素，而我自己为了方便在此函数规定一页为16行即16各像素，共4页，其实也就是4行.
//写入时，先写入第一小行8个像素，再写入第二小行8个像素
//第一个参数，代表是第一页显示什么，第二个参数，代表第二页显示什么。。。。。.
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


