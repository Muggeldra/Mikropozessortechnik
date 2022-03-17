#include <LPC17xx.h>
#include "gpio.h"

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
	if(GPIOGetValue(1,21)){value += 64;}
	if(GPIOGetValue(1,23)){value += 32;}
	if(GPIOGetValue(1,19)){value += 16;}
	if(GPIOGetValue(1,24)){value += 8;}
	if(GPIOGetValue(1,20)){value += 4;}
	if(GPIOGetValue(1,22)){value += 2;}
	if(GPIOGetValue(1,18)){value += 1;}
	return value;
}

//Buttons
void button_Init(void){
	GPIOSetDir(1,26,0);
	GPIOSetDir(1,27,0);
	GPIOSetDir(2,11,0);
	
	//pincon
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
	
	//pincon
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
