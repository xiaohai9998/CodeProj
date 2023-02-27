#ifndef  __TEST_H
#define	 __TEST_H



#include "stm32f10x.h"
#include "bsp_esp8266.h"


/********************************** 用户需要设置的参数**********************************/
#define   macUser_ESP8266_BulitApSsid         "iLink"      //要建立的热点的名称
#define   macUser_ESP8266_BulitApEcn           OPEN               //要建立的热点的加密方式
#define   macUser_ESP8266_BulitApPwd           "HI1910300105"         //要建立的热点的密钥

#define   macUser_ESP8266_TcpServer_IP         "192.168.123.169"      //服务器开启的IP地址
#define   macUser_ESP8266_TcpServer_Port       "8080"             //服务器开启的端口   

#define   macUser_ESP8266_TcpServer_OverTime   "1800"             //服务器超时时间（单位：秒）

#define mo0  0//代表控制电机1
#define mo1  1//代表控制电机2
#define mo2	 2//代表控制电机1和2

#define   mospeedg      90 //高速占空比为9成
#define   mospeedz 	    60 //中速占空比为6成
#define   mospeedd      30 //低速占空比为3成

/********************************** 测试函数声明 ***************************************/
void                     ESP8266_StaTcpClient_UnvarnishTest  ( void );
void showfg(uint16_t i ,uint32_t time);


#endif

