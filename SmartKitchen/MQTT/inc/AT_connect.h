#ifndef __AT_connect_H
#define __AT_connect_H

int AT_WIFIconnect(char *WIFIID,char *WIFIPWD,int timeout);
int AT_Interconnect(char *user,char *id,char *pwd,char *url,char *port,int timeout);

#endif