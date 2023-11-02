#ifndef __MENU_H
#define __MENU_H

typedef struct
{
	u8 current;
	u8 next;
	u8 enter;
	u8 back;
	void (*current_operation)(void);
}Menu_table;



void home();
void Temperature();
void Palygame();
void Setting();
void Info();


void  Menu_key_set(void);
u8 KEY_Scan(u8 mode);

void TestTemperature();
void ControlGame(void);
void Set();
void Information();

void LED();
void RTC_display();

#endif