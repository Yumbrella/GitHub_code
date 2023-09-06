#include "buffer.h"

sbuffer ATbuf; //用于存AT命令后返回的数据 以及接受的数据
sbuffer DATAbuf;//用于把接收的数据转化成可以用的数据

void Buffer_Init()
{
	ATbuf.rd=0;
	ATbuf.wr=0;
	
	DATAbuf.rd=0;
	DATAbuf.wr=0;
}

int Buffer_Read(char *r,sbuffer *buf)
{
	if(buf->rd==buf->wr)
		return 0;
	else
	{
		*r=buf->buffer[buf->rd];
		buf->rd=(buf->rd+1)%bufMax;
		return 1;
	}
}

void Buffer_Write(char w,sbuffer *buf)
{
	int i=(buf->wr+1)%bufMax;
	if(i!=buf->rd)	//为什么要留一个空位 因为如果不留 会造成读数据没有的情况 一直得不到读
	{
		buf->buffer[buf->wr]=w;
		buf->wr=i;
	}	
}

