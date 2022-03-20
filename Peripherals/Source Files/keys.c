#include <LPC17xx.h>
#include "gpio.h"
#include "prio.h"

//Switches
void Switch_Init(void){
	GPIOSetDir(1,18,0);
	GPIOSetDir(1,22,0);
	GPIOSetDir(1,20,0);
	GPIOSetDir(1,24,0);
	GPIOSetDir(1,19,0);
	GPIOSetDir(1,23,0);
	GPIOSetDir(1,21,0);
	GPIOSetDir(1,25,0);
	
	LPC_PINCON->PINMODE3&=~(0xFFFF<<4);
	LPC_PINCON->PINMODE3 |= (0xAAAA<<4);
	
}

unsigned char Get_SwitchPos(void){
	unsigned char value = 0;
	if(GPIOGetValue(1,25)){value += 128;}
	if(GPIOGetValue(1,24)){value += 64;}
	if(GPIOGetValue(1,23)){value += 32;}
	if(GPIOGetValue(1,22)){value += 16;}
	if(GPIOGetValue(1,21)){value += 8;}
	if(GPIOGetValue(1,20)){value += 4;}
	if(GPIOGetValue(1,19)){value += 2;}
	if(GPIOGetValue(1,18)){value += 1;}
	return value;
}

//Buttons
void button_Init(void){
	GPIOSetDir(1,26,0);
	GPIOSetDir(1,27,0);
	GPIOSetDir(2,11,0);
	
	LPC_PINCON->PINMODE3 &= ~(3 << 20);LPC_PINCON->PINMODE3 |= (2 << 20);//P1.26  
	LPC_PINCON->PINMODE3 &= ~(3 << 22);LPC_PINCON->PINMODE3 |= (2 << 22);//P1.27  
	LPC_PINCON->PINMODE4 &= ~(3 << 22);LPC_PINCON->PINMODE4 |= (2 << 22);//P2.11 
}

unsigned int Get_TA10Stat(void){
	if(GPIOGetValue(1,26)) {return 1;}
	else{return 0;}
}

unsigned int Get_TA11Stat(void){
	if(GPIOGetValue(1,27)) {return 1;}
	else{return 0;}
}

unsigned int Get_TA12Stat(void){
	if(GPIOGetValue(2,11)) {return 1;}
	else{return 0;}
}

//Joystick
void Joystick_Init(void){
	GPIOSetDir(0,27,0);
	GPIOSetDir(0,28,0);
	GPIOSetDir(0,3,0);
	GPIOSetDir(0,21,0);
	GPIOSetDir(0,25,0);
	
	LPC_PINCON->PINMODE0 &= ~(3 <<  6);LPC_PINCON->PINMODE0 |= (2 <<  6);//P0.03  
	LPC_PINCON->PINMODE1 &= ~(3 << 10);LPC_PINCON->PINMODE1 |= (2 << 10);//P0.21 
	LPC_PINCON->PINMODE1 &= ~(3 << 18);LPC_PINCON->PINMODE1 |= (2 << 18);//P0.25  
	LPC_PINCON->PINMODE1 &= ~(3 << 22);LPC_PINCON->PINMODE1 |= (2 << 22);//P0.27 
	LPC_PINCON->PINMODE1 &= ~(3 << 24);LPC_PINCON->PINMODE1 |= (2 << 24);//P0.28
}

unsigned int Get_LeftStat(void){
	if(GPIOGetValue(0,25)) {return 1;}
	else{return 0;}
}
unsigned int Get_RightStat(void){
	if(GPIOGetValue(0,28)) {return 1;}
	else{return 0;}
}
unsigned int Get_UpStat(void){
	if(GPIOGetValue(0,21)) {return 1;}
	else{return 0;}
}
unsigned int Get_DownStat(void){
	if(GPIOGetValue(0,27)) {return 1;}
	else{return 0;}
}
unsigned int Get_CenterStat(void){
	if(GPIOGetValue(0,3)) {return 1;}
	else{return 0;}
}

//Joystick Interrupt
void JoyStick_IRQ_Init(void){
	
}

//Matrix
void Matrix_Init(void){
	// rows as output
	GPIOSetDir(2, 3, 1);
	GPIOSetDir(2, 4, 1);
	GPIOSetDir(2, 5, 1);
	
	// colums as input
	GPIOSetDir(0, 4, 0);
	GPIOSetDir(0, 5, 0);
	GPIOSetDir(3,26, 0);
	
	// set pinmode for inputs
	LPC_PINCON->PINMODE0 &= ~(3 <<  8);LPC_PINCON->PINMODE0 |= (2 <<  8);//P0.04 
	LPC_PINCON->PINMODE0 &= ~(3 << 10);LPC_PINCON->PINMODE0 |= (2 << 10);//P0.05 
	LPC_PINCON->PINMODE7 &= ~(3 << 20);LPC_PINCON->PINMODE7 |= (2 << 20);//P3.26 
}

unsigned char Get_Mkey(void){
	unsigned char taste = 0x20;
	GPIOSetValue(2, 3, PORT_PIN_HIGH);
	GPIOSetValue(2, 4, PORT_PIN_LOW);
	GPIOSetValue(2, 5, PORT_PIN_LOW);
	if(GPIOGetValue(0, 4)){ taste = '1'; }
	else if(GPIOGetValue(0, 5)){ taste = '2'; }
	else if(GPIOGetValue(3, 26)) { taste = '3'; }
	else {
		GPIOSetValue(2, 3, PORT_PIN_LOW);
		GPIOSetValue(2, 4, PORT_PIN_HIGH);
		GPIOSetValue(2, 5, PORT_PIN_LOW);
		if(GPIOGetValue(0, 4)){ taste = '4'; }
		else if(GPIOGetValue(0, 5)){ taste = '5'; }
		else if(GPIOGetValue(3, 26)) { taste = '6'; }
		else {
			GPIOSetValue(2, 3, PORT_PIN_LOW);
			GPIOSetValue(2, 4, PORT_PIN_LOW);
			GPIOSetValue(2, 5, PORT_PIN_HIGH);
			if(GPIOGetValue(0, 4)){ taste = '7'; }
			else if(GPIOGetValue(0, 5)){ taste = '8'; }
			else if(GPIOGetValue(3, 26)) { taste = '9'; }
		}
	}
	GPIOSetValue(2, 3, PORT_PIN_LOW);
	GPIOSetValue(2, 4, PORT_PIN_LOW);
	GPIOSetValue(2, 5, PORT_PIN_LOW);
	return taste;
}
