#ifndef __SERIAL_H
#define __SERIAL_H

void Serial_Init();
void Serial_Write(char *buf,int len);
void Serial_Putc(uint8_t ch);

#endif
