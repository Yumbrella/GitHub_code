#include "stm32f10x.h"                  // Device header
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "Usart.h"
#include "OLED.h"
#include "I2C.h"



uint8_t ReceiverData;
uint8_t ID;
int16_t AX, AY, AZ, GX, GY, GZ;

void Task1(void* pvParameters)
{

	OLED_ShowString(1, 1, "Rx_Data:  ");
	OLED_ShowString(2, 1, "Tx_Data:  ");
	OLED_ShowString(3, 1, "ID: ");
	ID = MPU6050_GetID();
	OLED_ShowHexNum(3, 4, ID, 2);
	  while(1)
	{
		MPU6050_GetData(&AX, &AY, &AZ,&GX, &GY, &GZ);
		Send_Tx_data( (uint8_t)(AZ));
		OLED_ShowSignedNum(4, 1, AZ, 5);
		if(Get_Flag() == 1)
		{
			ReceiverData = Get_Rx_Data();
			
			OLED_ShowHexNum(1, 8, ReceiverData, 2);		
		}

	}

}


void Task2(void* pvParameters)
{
	
		while (1)
   {		 
     
   }
}




int main()
{
   OLED_Init();
	 Usart_Init();
	 MPUI2C_Init();
   
	
	xTaskCreate(Task1, "task1", 100, NULL , 0, NULL);
	xTaskCreate(Task2, "task2", 100, NULL , 0, NULL);	
//  xTaskCreate(Task3, "task3", 100, NULL, 1, NULL);


  vTaskStartScheduler();

	return 0;
}





