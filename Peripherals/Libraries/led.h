#ifndef led
#define led

void LED_Init(void);
void LED_On(unsigned int num);
void LED_Off(unsigned int num);
void LED_Toggle(unsigned int num);
void LED_Out(unsigned char value);
void RGB_Init(void);
void RGB_On(unsigned int num);
void RGB_Off(unsigned int num);
void RGB_Out(unsigned char num);
void RGB_Toggle(unsigned int num);
void LED_FlipFlop(unsigned int led,unsigned int button, unsigned int buttonBefore);
void RGB_FlipFlop(unsigned int led,unsigned int button, unsigned int buttonBefore);

#endif
