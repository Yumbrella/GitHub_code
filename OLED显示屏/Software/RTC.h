#ifndef __RTC_H
#define __RTC_H

extern uint16_t MyRTC_DataTime[];
void RTC_Init(void);
void RTC_SetTime(void);
void RTC_ReadTime(void);

#endif