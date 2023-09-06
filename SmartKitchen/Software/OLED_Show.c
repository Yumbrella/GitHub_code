#include "OLED.h"
#include "OLEDShow.h"

char MyTime[4];

void OLED_ShowDecName()
{
	OLED_ShowCN(0,2,0);
	OLED_ShowCN(16,2,1);
	OLED_ShowCN(32,2,2);
	OLED_ShowCN(48,2,3);
	OLED_ShowCN(64,2,4);
	OLED_ShowCN(80,2,5);
	OLED_ShowCN(96,2,6);
	OLED_ShowCN(112,2,7);
}


void OLED_ShowDeveloperName()
{
	OLED_ShowCN(16,5,8);
	OLED_ShowCN(32,5,9);
	OLED_ShowCN(48,5,10);
	OLED_ShowCN(64,5,11);
	OLED_ShowCN(80,5,12);
}

void OLED_ShowInterConnecting()
{
	OLED_ShowCN(16,5,13);
	OLED_ShowCN(32,5,14);
	OLED_ShowCN(48,5,15);
	OLED_ShowCN(64,5,16);
	OLED_ShowCN(80,5,17);
}

void OLED_ShowConnectOK()
{
	OLED_ShowCN(32,5,15);
	OLED_ShowCN(48,5,16);
	OLED_ShowCN(64,5,18);
	OLED_ShowCN(80,5,19);
}


void Show_MyTime(uint8_t a)
{
	OLED_ShowChar(1,9,MyTime[0]);
	OLED_ShowChar(1,10,MyTime[1]);
	OLED_ShowChar(1,11,a);
	OLED_ShowChar(1,12,MyTime[2]);
	OLED_ShowChar(1,13,MyTime[3]);
}



void Show_Bar()
{
	OLED_ShowCN(0,0,20);
	OLED_ShowCN(110,0,21);
	OLED_ShowCN(18,0,26);
	
	Show_MyTime(':');
}

void System_Homepage(void)
{
	
	OLED_Clear();
	Show_Bar();
	OLED_ShowCN(0,2,0);
	OLED_ShowCN(15,2,1);
	OLED_ShowCN(30,2,2);
	OLED_ShowCN(45,2,3);
	OLED_ShowCN(60,2,4);
	OLED_ShowCN(75,2,5);
	OLED_ShowCN(90,2,6);
	OLED_ShowCN(105,2,7);
	
	OLED_ShowCN(0,6,22);
	OLED_ShowCN(15,6,23);
	
	OLED_ShowCN(95,6,24);
	OLED_ShowCN(110,6,25);
}

void System_HelloHomepage(void)
{
	
	OLED_Clear();
	Show_Bar();
	
	OLED_ShowCN(0,2,0);
	OLED_ShowCN(15,2,1);
	OLED_ShowCN(30,2,2);
	OLED_ShowCN(45,2,3);
	OLED_ShowCN(60,2,4);
	OLED_ShowCN(75,2,5);
	OLED_ShowCN(90,2,6);
	OLED_ShowCN(105,2,7);
}

void System_Page1(void)
{
	OLED_Clear();
	Show_Bar();
	
	OLED_ShowCN(0,2,30);
	OLED_ShowCN(15,2,31);
	OLED_ShowString(2,5,":");
	
	OLED_ShowCN(0,4,32);
	OLED_ShowCN(15,4,33);
	OLED_ShowString(3,5,":");
	
	OLED_ShowCN(79,6,27);
	OLED_ShowCN(95,6,28);
	OLED_ShowCN(110,6,29);
}

void System_Page2(void)
{
	OLED_Clear();
	Show_Bar();
	
	OLED_ShowCN(0,2,34);
	OLED_ShowCN(17,2,35);
	OLED_ShowString(2,5,":");
	
	OLED_ShowCN(0,4,36);
	OLED_ShowCN(17,4,37);
	OLED_ShowString(3,5,":");
	
	OLED_ShowCN(79,6,27);
	OLED_ShowCN(95,6,28);
	OLED_ShowCN(110,6,29);
}


void Show_WarningFire()
{
	OLED_Clear();
	OLED_ShowCN(32,2,40);
	OLED_ShowCN(48,2,41);
	OLED_ShowCN(64,2,42);
	OLED_ShowCN(80,2,43);
	OLED_ShowCN(96,2,44);
}

