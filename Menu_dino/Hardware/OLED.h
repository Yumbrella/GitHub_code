#ifndef __OLED_H
#define __OLED_H

#define OLED0561_ADD	0x78  // OLED I2C??
#define COM				0x00  // OLED 
#define DAT 			0x40  // OLED 

#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF
#define X_WIDTH 	128
#define Y_WIDTH 	64


void OLED_DrawGIF(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1, unsigned char k, int m, unsigned char GIF[][m]);
void OLED_I2C_Init(void);
void OLED_I2C_Start(void);
void OLED_I2C_Stop(void);
void OLED_I2C_WaitAck(void);
void OLED_I2C_SendByte(uint8_t Byte);
void OLED_WriteCommand(uint8_t Command);
void OLED_WriteData(uint8_t Data);
void OLED_SetCursor(unsigned char x, unsigned char y);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
uint32_t OLED_Pow(uint32_t X, uint32_t Y);
void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num,uint8_t len, uint8_t size2);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawBMP2(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[]);

#endif
