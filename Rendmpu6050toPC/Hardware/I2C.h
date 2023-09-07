#ifndef __I@C_H
#define __I@C_H

void MPU_WriteReg(uint8_t Address, uint8_t Data);
uint8_t MPU_ReadReg(uint8_t Address);
void MPUI2C_Init(void);
uint8_t MPU6050_GetID(void);
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
						int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ);


#endif