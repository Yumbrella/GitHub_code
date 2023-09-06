#ifndef __DHT11_H
#define __DHT11_H

#define GPIO_DHT11 GPIOB
#define GPIO_DHT11_Pin GPIO_Pin_12


#define dht11_high GPIO_SetBits(GPIO_DHT11, GPIO_DHT11_Pin)
#define dht11_low GPIO_ResetBits(GPIO_DHT11, GPIO_DHT11_Pin)
#define Read_Data GPIO_ReadInputDataBit(GPIO_DHT11, GPIO_DHT11_Pin)

void DHT11_GPIO_Init_OUT(void);
void DHT11_GPIO_Init_IN(void);
void DHT11_Start(void);
unsigned char DHT11_REC_Byte(void);
void DHT11_REC_Data(void);



#endif
