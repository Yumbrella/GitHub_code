#include "AT_MQTT.h"
#include "AT_command.h"
#include "string.h"


//AT+MQTTSUB=0,"订阅的主题名",0      //订阅对应的主题
int Subscribe(char *name,int timeout)
{
	int ret;
	char tem[50]="AT+MQTTSUB=0,\"";
	strcat(tem,name);
	strcat(tem,"\",0");
	AT_Send_Command(tem,NULL,timeout);
	
}

//AT+MQTTPUB=0,"对应主题","发布主题对应信息",0,0          //发布对应主题信息         

int PushTheme(char *name,char *text,int timeout)
{
	int ret;
	char tem[50]="AT+MQTTPUB=0,\"";
	strcat(tem,name);
	strcat(tem,"\",\"");
	strcat(tem,text);
	strcat(tem,"\",0,0");
	AT_Send_Command(tem,NULL,timeout);
}
