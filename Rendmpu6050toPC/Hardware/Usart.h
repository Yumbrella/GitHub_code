#ifndef __USART_H
#define __USART_H

void Usart_Init(void);
uint8_t Get_Flag();
uint8_t Get_Rx_Data(void);
void Send_Tx_data(uint8_t byte);


#endif