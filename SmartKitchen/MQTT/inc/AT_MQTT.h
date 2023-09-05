#ifndef __AT_MQTT_H
#define __AT_MQTT_H

int Subscribe(char *name,int timeout);
int PushTheme(char *name,char *text,int timeout);

#endif