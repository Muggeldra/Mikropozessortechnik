
#include <LPC17xx.h>

void DAC_Init(void){
	// set dac clock
	LPC_SC->PCLKSEL0 &=~ (3 << 22);
	LPC_SC->PCLKSEL0 |=  (1 << 22);
	
	// configure P0.26 as dac
	LPC_PINCON->PINSEL1 &=~ (3 << 20);
	LPC_PINCON->PINSEL1 |=  (2 << 20);
}

void DAC_Out(unsigned int wert){
	LPC_DAC->DACR = ((wert & 0x3FF) << 6);
}
