#include "test.h"
#include "bsp_esp8266.h"
#include "bsp_SysTick.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "bsp_moter.h"
#include "OLED4Piic.h"
#include "front.h"
#include "bsp_GeneralTim3.h"
#include "bsp_GeneralTim2.h"
#include "bsp_GeneralTim4.h"
uint32_t time2, time4;
// TIM ������������ʱ��
uint32_t TIM2_PscCLK = 72000000 / (GENERAL_TIM2_PSC + 1), TIM4_PscCLK = 72000000 / (GENERAL_TIM4_PSC + 1);

void showfg(uint16_t i, uint32_t time)
{
	//			//���1 0.123456 s
	if (time <= 9999999)
	{
		OLED_ShowChar(i, 8, &Fxiaodian[0]); // TIM_PscCLKΪ100 0000

		OLED_ShowChar(i, 7, &FNum[(int)(time / 1000000) * 16]); // TIM_PscCLKΪ100 0000,һ��Ҫע�����16��16λ�������е�һ�У���ʾһ������
		OLED_ShowChar(i, 9, &FNum[(int)(time % 1000000 / 100000) * 16]);
		OLED_ShowChar(i, 10, &FNum[(int)(time % 1000000 % 100000 / 10000) * 16]);
		OLED_ShowChar(i, 11, &FNum[(int)(time % 1000000 % 100000 % 10000 / 1000) * 16]);
		OLED_ShowChar(i, 12, &FNum[(int)(time % 1000000 % 100000 % 10000 % 1000 / 100) * 16]);
		OLED_ShowChar(i, 13, &FNum[(int)(time % 1000000 % 100000 % 10000 % 1000 % 100 / 10) * 16]);
		OLED_ShowChar(i, 14, &FNum[(int)(time % 1000000 % 100000 % 10000 % 1000 % 100 % 10 / 1) * 16]);
		// 15Ϊ�ո�
		OLED_ShowChar(i, 16, &Fs[0]);
	}
	else
	{
		OLED_ShowChar(i, 8, &Fxiaodian[0]); // TIM_PscCLKΪ100 0000

		OLED_ShowChar(i, 7, &FNum[9 * 16]);
		OLED_ShowChar(i, 9, &FNum[9 * 16]);
		OLED_ShowChar(i, 10, &FNum[9 * 16]);
		OLED_ShowChar(i, 11, &FNum[9 * 16]);
		OLED_ShowChar(i, 12, &FNum[9 * 16]);
		OLED_ShowChar(i, 13, &FNum[9 * 16]);
		OLED_ShowChar(i, 14, &FNum[9 * 16]);
		// 15Ϊ�ո�
		OLED_ShowChar(i, 16, &Fs[0]);
	}
}
/**
 * @brief  ESP8266 ��Sta Tcp Client��͸��
 * @param  ��
 * @retval ��
 */
void ESP8266_StaTcpClient_UnvarnishTest(void)
{
	printf("\r\nTIM4��øߵ�ƽ����ʱ�� s\r\n");
	OLED_clear();
	char cStr[100] = {0}, cCh1, cCh2, cCh3;

	char *pCh;

	macESP8266_CH_ENABLE();

	ESP8266_AT_Test();

	ESP8266_Net_Mode_Choose(AP);

	while (!ESP8266_CIPAP(macUser_ESP8266_TcpServer_IP))
		;

	while (!ESP8266_BuildAP(macUser_ESP8266_BulitApSsid, macUser_ESP8266_BulitApPwd, macUser_ESP8266_BulitApEcn))
		;

	ESP8266_Enable_MultipleId(ENABLE);

	while (!ESP8266_StartOrShutServer(ENABLE, macUser_ESP8266_TcpServer_Port, macUser_ESP8266_TcpServer_OverTime))
		;

	ESP8266_Inquire_ApIp(cStr, 20);

	//	printf ( "\r\n��ģ��WIFIΪ%s������Ϊ��%s,\r\nAP IP Ϊ��%s�������Ķ˿�Ϊ��%s\r\n�ֻ������������Ӹ� IP �Ͷ˿ڣ���������5���ͻ���\r\n",
	//           macUser_ESP8266_BulitApSsid, macUser_ESP8266_BulitApPwd ,cStr, macUser_ESP8266_TcpServer_Port );

	strEsp8266_Fram_Record.InfBit.FramLength = 0;
	strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;

	Moter1_Power_ON();
	Moter2_Power_ON(); // ����
	// Moter1_BR_ON();
	// Moter2_BR_ON();//ʹ��ɲ�����õ��ֹͣ
	Moter1_CW_ON(); // ��ת
	Moter2_CW_ON(); // ��ת

	OLED_clear();
	BpagePoint0 = &mo_1[0];
	BpagePoint1 = &mo_stop[0];
	BpagePoint2 = &mo_2[0];
	BpagePoint3 = &mo_stop[0];
	BPage_display(BpagePoint0, BpagePoint1, BpagePoint2, BpagePoint3); // ��ʼ������������Ļ��
	showfg(1, 0);
	showfg(3, 0);
	while (1)
	{
		if (strEsp8266_Fram_Record.InfBit.FramFinishFlag)
		{
			USART_ITConfig(macESP8266_USARTx, USART_IT_RXNE, DISABLE); // ���ô��ڽ����ж�
			strEsp8266_Fram_Record.Data_RX_BUF[strEsp8266_Fram_Record.InfBit.FramLength] = '\0';

			if ((pCh = strstr(strEsp8266_Fram_Record.Data_RX_BUF, "CMD_")) != 0)
			{
				cCh1 = *(pCh + 4);
				cCh2 = *(pCh + 5);
				cCh3 = *(pCh + 6);
				switch (cCh1)
				{
				case '0': // motor1
					Moter1_BR_OFF();
					switch (cCh3)
					{
					case '0':
						Moter1_BR_ON();
						BpagePoint1 = &mo_stop[0];
						break;
					case '1':
						switch (cCh2)
						{
						case '0':
							Moter1_CW_OFF();
							BpagePoint1 = &mo_fandi[0];
							break;
						case '1':
							Moter1_CW_ON();
							BpagePoint1 = &mo_zhengdi[0];
							break;
						}
						GENERAL_TIM3_Mode_Config(mo0, mospeedd);
						break;
					case '2':
						switch (cCh2)
						{
						case '0':
							Moter1_CW_OFF();
							BpagePoint1 = &mo_fanzhong[0];
							break;
						case '1':
							Moter1_CW_ON();
							BpagePoint1 = &mo_zhengzhong[0];
							break;
						}
						GENERAL_TIM3_Mode_Config(mo0, mospeedz);
						break;
					case '3':
						switch (cCh2)
						{
						case '0':
							Moter1_CW_OFF();
							BpagePoint1 = &mo_zhengzhong[0];
							BpagePoint1 = &mo_fangao[0];
							break;
						case '1':
							Moter1_CW_ON();
							BpagePoint1 = &mo_zhengzhong[0];
							BpagePoint1 = &mo_zhenggao[0];
							break;
						}
						GENERAL_TIM3_Mode_Config(mo0, mospeedg);
						break;
					default:
						break;
					}
					break;
				case '1':
					Moter2_BR_OFF();
					switch (cCh3)
					{
					case '0':
						Moter2_BR_ON();
						BpagePoint3 = &mo_stop[0];
						break;
					case '1':
						switch (cCh2)
						{
						case '0':
							Moter2_CW_OFF();
							BpagePoint3 = &mo_fandi[0];
							break;
						case '1':
							Moter2_CW_ON();
							BpagePoint3 = &mo_zhengdi[0];
							break;
						}
						GENERAL_TIM3_Mode_Config(mo1, mospeedd);
						break;
					case '2':
						switch (cCh2)
						{
						case '0':
							Moter2_CW_OFF();
							BpagePoint3 = &mo_fanzhong[0];
							break;
						case '1':
							Moter2_CW_ON();
							BpagePoint3 = &mo_zhengzhong[0];
							break;
						}
						GENERAL_TIM3_Mode_Config(mo1, mospeedz);
						break;
					case '3':
						switch (cCh2)
						{
						case '0':
							Moter2_CW_OFF();
							BpagePoint3 = &mo_fangao[0];
							break;
						case '1':
							Moter2_CW_ON();
							BpagePoint3 = &mo_zhenggao[0];
							break;
						}
						GENERAL_TIM3_Mode_Config(mo1, mospeedg);
						break;
					default:
						break;
					}
					break;
				case '2':
					Moter1_BR_OFF();
					Moter2_BR_OFF();
					switch (cCh3)
					{
					case '0':
						Moter1_BR_ON();
						Moter2_BR_ON();
						BpagePoint1 = &mo_stop[0];
						BpagePoint3 = &mo_stop[0];
						break;

					case '1':
						switch (cCh2)
						{
						case '0':
							Moter1_CW_OFF();
							Moter2_CW_OFF();
							BpagePoint1 = &mo_fandi[0];
							BpagePoint3 = &mo_fandi[0];
							break;
						case '1':
							Moter1_CW_ON();
							Moter2_CW_ON();
							BpagePoint1 = &mo_zhengdi[0];
							BpagePoint3 = &mo_zhengdi[0];
							break;
						}
						GENERAL_TIM3_Mode_Config(mo2, mospeedd);
						break;
					case '2':
						switch (cCh2)
						{
						case '0':
							Moter1_CW_OFF();
							Moter2_CW_OFF();
							BpagePoint1 = &mo_fanzhong[0];
							BpagePoint3 = &mo_fanzhong[0];
							break;
						case '1':
							Moter1_CW_ON();
							Moter2_CW_ON();
							BpagePoint1 = &mo_zhengzhong[0];
							BpagePoint3 = &mo_zhengzhong[0];
							break;
						}
						GENERAL_TIM3_Mode_Config(mo2, mospeedz);
						break;
					case '3':
						switch (cCh2)
						{
						case '0':
							Moter1_CW_OFF();
							Moter2_CW_OFF();
							BpagePoint1 = &mo_fangao[0];
							BpagePoint3 = &mo_fangao[0];
							break;
						case '1':
							Moter1_CW_ON();
							Moter2_CW_ON();
							BpagePoint1 = &mo_zhenggao[0];
							BpagePoint3 = &mo_zhenggao[0];
							break;
						}
						GENERAL_TIM3_Mode_Config(mo2, mospeedg);
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
				OLED_ShowPage(2, &clearpage[0]);
				OLED_ShowPage(2, BpagePoint1); // ��Ȼû��Ҫ�������һ�У�д��ʱ����Ѿ�����ˣ����ǻ�������հɣ����ٿ��Կ�����ֵ�Ǹ��˵�
				OLED_ShowPage(4, &clearpage[0]);
				OLED_ShowPage(4, BpagePoint3);
			}
			strEsp8266_Fram_Record.InfBit.FramLength = 0;
			strEsp8266_Fram_Record.InfBit.FramFinishFlag = 0;

			USART_ITConfig(macESP8266_USARTx, USART_IT_RXNE, ENABLE); // ʹ�ܴ��ڽ����ж�
		}

		if (TIM4_ICUserValueStructure.Capture_FinishFlag == 1)
		{
			// ����ߵ�ƽʱ��ļ�������ֵ
			time4 = TIM4_ICUserValueStructure.Capture_Period * (GENERAL_TIM4_PERIOD + 1) +
					(TIM4_ICUserValueStructure.Capture_CcrValue + 1);
			printf("\r\nTIM4��%d \r\n", time4);

			// ��ӡ�ߵ�ƽ����ʱ��
			printf("\r\nTIM4��øߵ�ƽ����ʱ��4��%d.%d s\r\n", time4 / TIM4_PscCLK, time4 % TIM4_PscCLK);
			showfg(1, time4);
			TIM4_ICUserValueStructure.Capture_FinishFlag = 0;
		}

		if (TIM2_ICUserValueStructure.Capture_FinishFlag == 1)
		{
			// ����ߵ�ƽʱ��ļ�������ֵ
			time2 = TIM2_ICUserValueStructure.Capture_Period * (GENERAL_TIM2_PERIOD + 1) +
					(TIM2_ICUserValueStructure.Capture_CcrValue + 1);

			// ��ӡ�ߵ�ƽ����ʱ��
			printf("\r\nTIM2��%d \r\n", time2);
			printf("\r\nTIM2��øߵ�ƽ����ʱ��2��%d.%d s\r\n", time2 / TIM2_PscCLK, time2 % TIM2_PscCLK);
			showfg(3, time2);
			TIM2_ICUserValueStructure.Capture_FinishFlag = 0;
		}
	}
}
