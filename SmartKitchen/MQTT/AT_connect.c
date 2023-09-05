#include "AT_connect.h"
#include "AT_command.h"
#include "string.h"


//成功1 失败0
int AT_WIFIconnect(char *WIFIID,char *WIFIPWD,int timeout)
{
	int ret;
	char tem[50]="AT+CWJAP=\"";
	//AT+CWJAP="SSID","password"	
	strcat(tem,WIFIID);
	strcat(tem,"\",\"");
	strcat(tem,WIFIPWD);
	strcat(tem,"\"");
	ret=AT_Send_Command("AT+CWMODE=3",NULL,timeout);
	if(ret!=1)return 0;
	ret=AT_Send_Command(tem,NULL,timeout);
	if(ret!=1)return 0;
	return 1;
		
}

/*
*	AT+MQTTUSERCFG=0,1,"myuser","yry000","123456",0,0,""
*	AT+MQTTCONN=0,"p8709629.ala.cn-hangzhou.emqxsl.cn",1883,0
*	AT+MQTTPUB=0,"对应主题","发布主题对应信息",0,0          //发布对应主题信息                                            
*	AT+MQTTSUB=0,"订阅的主题名",0      //订阅对应的主题
*/

int AT_Interconnect(char *user,char *id,char *pwd,char *url,char *port,int timeout)
{
	int ret;
	char tem[100]="AT+MQTTUSERCFG=0,1,\"";
	strcat(tem,user);
	strcat(tem,"\",\"");
	strcat(tem,id);
	strcat(tem,"\",\"");
	strcat(tem,pwd);
	strcat(tem,"\",0,0,\"\"");
	ret=AT_Send_Command(tem,NULL,timeout);
	if(ret!=1)return 0;
	
	strcpy(tem,"AT+MQTTCONN=0,\"");
	strcat(tem,url);
	strcat(tem,"\",");
	strcat(tem,port);
	strcat(tem,",0");
	ret=AT_Send_Command(tem,NULL,timeout);
	if(ret!=1)return 0;
	return 1;
}