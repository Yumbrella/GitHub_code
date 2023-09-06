#ifndef __BUFFER_H
#define __BUFFER_H

#define bufMax 512

typedef struct _serial_buffer
{
    char buffer[bufMax];
    int rd;
	int wr;

}sbuffer;

extern sbuffer ATbuf;
extern sbuffer DATAbuf;

void Buffer_Init();
void Buffer_Write(char w,sbuffer *buf);
int Buffer_Read(char *r,sbuffer *buf);



#endif