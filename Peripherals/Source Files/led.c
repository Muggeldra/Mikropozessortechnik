#include <LPC17xx.h>
#include "gpio.h"

void LED_Init(void){
	GPIOSetDir(0,0,1);
	GPIOSetDir(0,22,1);
	GPIOSetDir(2,7,1);
	GPIOSetDir(2,12,1);
	GPIOSetDir(0,2,1);
	GPIOSetDir(2,6,1);
	GPIOSetDir(2,8,1);
	GPIOSetDir(2,13,1);
	
	GPIOSetValue(0,0,0);
	GPIOSetValue(0,22,0);
	GPIOSetValue(2,7,0);
	GPIOSetValue(2,12,0);
	GPIOSetValue(0,2,0);
	GPIOSetValue(2,6,0);
	GPIOSetValue(2,8,0);
	GPIOSetValue(2,13,0);	
}

void LED_On(unsigned int num){
	switch(num){
		case 0:
			GPIOSetValue(0,0,1);
		break;
		case 1:
			GPIOSetValue(0,2,1);
		break;
		case 2:
			GPIOSetValue(0,22,1);
		break;
		case 3:
			GPIOSetValue(2,6,1);
		break;
		case 4:
			GPIOSetValue(2,7,1);
		break;
		case 5:
			GPIOSetValue(2,8,1);
		break;
		case 6:
			GPIOSetValue(2,12,1);
		break;
		case 7:
			GPIOSetValue(2,13,1);
		break;
		default:
		break;
	}
}

void LED_Off(unsigned int num){
	switch(num){
		case 0:
			GPIOSetValue(0,0,0);
		break;
		case 1:
			GPIOSetValue(0,2,0);
		break;
		case 2:
			GPIOSetValue(0,22,0);
		break;
		case 3:
			GPIOSetValue(2,6,0);
		break;
		case 4:
			GPIOSetValue(2,7,0);
		break;
		case 5:
			GPIOSetValue(2,8,0);
		break;
		case 6:
			GPIOSetValue(2,12,0);
		break;
		case 7:
			GPIOSetValue(2,13,0);
		break;
		default:
		break;
	}
}

void LED_Toggle(unsigned int num){
	switch(num){
		case 0:
			GPIOToggle(0,0);
		break;
		case 1:
			GPIOToggle(0,2);
		break;
		case 2:
			GPIOToggle(0,22);
		break;
		case 3:
			GPIOToggle(2,6);
		break;
		case 4:
			GPIOToggle(2,7);
		break;
		case 5:
			GPIOToggle(2,8);
		break;
		case 6:
			GPIOToggle(2,12);
		break;
		case 7:
			GPIOToggle(2,13);
		break;
		default:
		break;
	}
}

void LED_Out(unsigned char value){
	if(value >= 128){LED_On(7); value -= 128;}
	else{LED_Off(7);}
	if(value >= 64){LED_On(6); value -= 64;}
	else{LED_Off(6);}
	if(value >= 32){LED_On(5); value -= 32;}
	else{LED_Off(5);}
	if(value >= 16){LED_On(4); value -= 16;}
	else{LED_Off(4);}
	if(value >= 8){LED_On(3); value -= 8;}
	else{LED_Off(3);}
	if(value >= 4){LED_On(2); value -= 4;}
	else{LED_Off(2);}
	if(value >= 2){LED_On(1); value -= 2;}
	else{LED_Off(1);}
	if(value >= 1){LED_On(0); value -= 1;}
	else{LED_Off(0);}
}

void RGB_Init(void){
	GPIOSetDir(0,10,1);
	GPIOSetDir(0,11,1);
	GPIOSetDir(4,29,1);
	
	GPIOSetValue(0,10,0);
	GPIOSetValue(0,11,0);
	GPIOSetValue(4,29,0);
}

void RGB_On(unsigned int num){
	switch (num){
		case 0:
			GPIOSetValue(0,10,1);
		break;
		case 1:
			GPIOSetValue(0,11,1);
		break;
		case 2:
			GPIOSetValue(4,29,1);
		break;
		default:
		break;
	}
}

void RGB_Off(unsigned int num){
	switch (num){
		case 0:
			GPIOSetValue(0,10,0);
		break;
		case 1:
			GPIOSetValue(0,11,0);
		break;
		case 2:
			GPIOSetValue(4,29,0);
		break;
		default:
		break;
	}
}

void RGB_Toggle(unsigned int num){
	switch (num){
		case 0:
			GPIOToggle(0,10);
		break;
		case 1:
			GPIOToggle(0,11);
		break;
		case 2:
			GPIOToggle(4,29);
		break;
		default:
		break;
	}
}

void RGB_Out(unsigned char value){
	if(value >= 4){RGB_On(2); value -= 4;}
	else{RGB_Off(2);}
	if(value >= 2){RGB_On(1); value -= 2;}
	else{RGB_Off(1);}
	if(value >= 1){RGB_On(0); value -= 1;}
	else{RGB_Off(0);}
}

unsigned int RGB_FlipFlop(unsigned int led,unsigned int button, unsigned int buttonBefore){
	if(button == 1 && buttonBefore == 0){
			RGB_Toggle(led);
			return 1;
		}
		else if(button != 1 && buttonBefore == 1){
			return 0;
		}
		else{
			return buttonBefore;
		}
}

unsigned int LED_FlipFlop(unsigned int led,unsigned int button, unsigned int buttonBefore){
	if(button && buttonBefore == 0){
			LED_Toggle(led);
			return 1;
		}
		else if(!button && buttonBefore == 1){
			return 0;
		}
		else{
			return buttonBefore;
		}
}

void rolchar(uint8_t* value, uint8_t dir){
	if(dir == 0){
		if(*value & (1 << 7)){
			*value = ((*value << 1)+1);
		}
		else{
			*value = (*value << 1);
		}
	}
	else if(dir == 1){
		if(*value & 1){
			*value = ((*value >> 1)+128);
		}
		else{
			*value = (*value >> 1);
		}
	}
}
