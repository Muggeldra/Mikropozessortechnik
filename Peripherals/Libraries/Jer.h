#ifndef Jer
#define Jer
void LED_Init(void);
void LED_On(unsigned int num);
void LED_Off(unsigned int num);
void LED_TOGGLE(unsigned int num);
void LED_Out(unsigned char value);
void Switch_Init(void);
unsigned char Get_SwitchPos(void);

#endif
