#ifndef __MAX7219_H
#define __MAX7219_H

void Max7219_Init(void);
void SPI_Start(void);
void SPI_Stop(void);
void Write_data(uint8_t TXdata);
void MAX7219_W(uint8_t addr, uint8_t data);



#endif