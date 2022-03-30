#include <LPC17xx.h>
#include "gpio.h"
#include "prio.h"

//Switches
void Switch_Init(void){
	LPC_GPIO1->FIODIR &=~ (0xFF << 18);
	LPC_PINCON->PINMODE3&=~(0xFFFF<<4);
	LPC_PINCON->PINMODE3 |= (0xAAAA<<4);
}

unsigned char Get_SwitchPos(void){
	return ((LPC_GPIO1->FIOPIN>>18) & 0xFF);	
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
	
	//checken
	//LPC_GPIO0->FIODIR &=~ (0x3440001 << 3);
	
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

//Joystick as interrupt
void JoyStick_IRQ_Init(void){
	LPC_PINCON->PINSEL0 &=~ (3<<6);
	LPC_PINCON->PINSEL1 &=~ (3<<10);
	LPC_PINCON->PINSEL1 &=~ (3<<18);
	LPC_PINCON->PINSEL1 &=~ (3<<22);
	LPC_PINCON->PINSEL1 &=~ (3<<24);
	
	LPC_PINCON->PINMODE0 &= ~(3 <<  6);LPC_PINCON->PINMODE0 |= (2 <<  6);//P0.03  
	LPC_PINCON->PINMODE1 &= ~(3 << 10);LPC_PINCON->PINMODE1 |= (2 << 10);//P0.21 
	LPC_PINCON->PINMODE1 &= ~(3 << 18);LPC_PINCON->PINMODE1 |= (2 << 18);//P0.25  
	LPC_PINCON->PINMODE1 &= ~(3 << 22);LPC_PINCON->PINMODE1 |= (2 << 22);//P0.27 
	LPC_PINCON->PINMODE1 &= ~(3 << 24);LPC_PINCON->PINMODE1 |= (2 << 24);//P0.28
	
	GPIOSetDir(0,27,0);
	GPIOSetDir(0,28,0);
	GPIOSetDir(0,3,0);
	GPIOSetDir(0,21,0);
	GPIOSetDir(0,25,0);
	
	LPC_GPIOINT->IO0IntEnR |= (1<<3);
	LPC_GPIOINT->IO0IntEnR |= (1<<21);
	LPC_GPIOINT->IO0IntEnR |= (1<<25);
	LPC_GPIOINT->IO0IntEnR |= (1<<27);
	LPC_GPIOINT->IO0IntEnR |= (1<<28);
	
	//LPC_GPIOINT->IO0IntStatR = 0;
	NVIC_ClearPendingIRQ(EINT3_IRQn);
	NVIC_SetPriority(EINT3_IRQn, prioJoystick);
	NVIC_EnableIRQ(EINT3_IRQn);
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

//Encoder
void Encoder_Init(void){
	LPC_SC->PCONP |= (1<<15);
	
	//center interupt
	LPC_PINCON->PINSEL4 &=~ (3<<20);
	LPC_PINCON->PINSEL4 |= (1<<20);
	LPC_PINCON->PINMODE4 &=~ (3<<20);
	LPC_PINCON->PINMODE4 |= (2<<20);
	LPC_SC->EXTMODE |= (1<<0);
	LPC_SC->EXTPOLAR |= (1<<0);
	LPC_SC->EXTINT |= (1<<0);
	NVIC_ClearPendingIRQ(EINT0_IRQn);
	NVIC_SetPriority(EINT0_IRQn, prioEncoderCenter);
	NVIC_EnableIRQ(EINT0_IRQn);
	
	//A interrupt
	LPC_PINCON->PINSEL1 &=~ (3<<14);
	LPC_PINCON->PINMODE1 &= ~(3 <<  14);LPC_PINCON->PINMODE1 |= (2 <<  14);
	LPC_GPIO0->FIODIR &=~ (1<<14);
	LPC_GPIOINT->IO0IntEnR |= (1<<23);
	//LPC_GPIOINT->IO0IntStatR = 0;
	NVIC_ClearPendingIRQ(EINT3_IRQn);
	NVIC_SetPriority(EINT3_IRQn, prioEncoderA);
	NVIC_EnableIRQ(EINT3_IRQn);
		
	
	//B GPIO
	LPC_PINCON->PINSEL1 &=~ (3<<16);
	LPC_PINCON->PINMODE1 &= ~(3 <<  16);LPC_PINCON->PINMODE1 |= (2 <<  16);
	GPIOSetDir(0,24,0);
	
	
}

