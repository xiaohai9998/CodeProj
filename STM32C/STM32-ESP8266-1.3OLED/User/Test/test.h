#ifndef  __TEST_H
#define	 __TEST_H



#include "stm32f10x.h"
#include "bsp_esp8266.h"


/********************************** �û���Ҫ���õĲ���**********************************/
#define   macUser_ESP8266_BulitApSsid         "iLink"      //Ҫ�������ȵ������
#define   macUser_ESP8266_BulitApEcn           OPEN               //Ҫ�������ȵ�ļ��ܷ�ʽ
#define   macUser_ESP8266_BulitApPwd           "HI1910300105"         //Ҫ�������ȵ����Կ

#define   macUser_ESP8266_TcpServer_IP         "192.168.123.169"      //������������IP��ַ
#define   macUser_ESP8266_TcpServer_Port       "8080"             //�����������Ķ˿�   

#define   macUser_ESP8266_TcpServer_OverTime   "1800"             //��������ʱʱ�䣨��λ���룩

#define mo0  0//������Ƶ��1
#define mo1  1//������Ƶ��2
#define mo2	 2//������Ƶ��1��2

#define   mospeedg      90 //����ռ�ձ�Ϊ9��
#define   mospeedz 	    60 //����ռ�ձ�Ϊ6��
#define   mospeedd      30 //����ռ�ձ�Ϊ3��

/********************************** ���Ժ������� ***************************************/
void                     ESP8266_StaTcpClient_UnvarnishTest  ( void );
void showfg(uint16_t i ,uint32_t time);


#endif

