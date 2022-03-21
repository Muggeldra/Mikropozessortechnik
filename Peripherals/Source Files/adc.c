
#include <LPC17xx.h>
#include "prio.h"

void ADC_Init(uint8_t chsel, uint8_t intEn){
	/*	initialize analog channels depending on chsel byte: bit0 -> a0.0, bit1 -> a0.1, ...
			intEn: 0 -> no burst, 1 -> burst
				AD0.0  <-->  P0.23
				AD0.1  <-->  P0.24
				AD0.2  <-->  P0.25
				AD0.3  <-->  P0.26			AOUT
				AD0.4  <-->  P1.30			Pot1
				AD0.5  <-->  P1.31			Pot2
				AD0.6  <-->  P0.03
				AD0.7  <-->  P0.02
	*/
	
	//enable power
	LPC_SC->PCONP |= (1 << 12);
	LPC_SC->PCONP |= (1 << 15);
	
	// set adc clock
	LPC_SC->PCLKSEL0 &=~ (3 << 24);
	
	// default values
	LPC_ADC->ADCR &=~ (0xFF << 8);
	LPC_ADC->ADCR |=  (0x01 << 8);
	
	// test 4.1.2
	//LPC_ADC->ADCR |=  (23 << 8);
	//LPC_ADC->ADCR |=  ( 9 << 8);
	//LPC_ADC->ADCR |=  ( 4 << 8);
	//LPC_ADC->ADCR |=  ( 3 << 8);
	//LPC_ADC->ADCR |=  ( 2 << 8);
	
	//LPC_SC->PCLKSEL0 &=~ (3 << 24);
	//LPC_SC->PCLKSEL0 |=  (1 << 24);
	//LPC_ADC->ADCR    |=  (7 <<  8);
	// end test 4.1.2
	
	// set burst mode
	LPC_ADC->ADCR |= (intEn << 16);
	// set converter operational
	LPC_ADC->ADCR |= (1 << 21);
	// set no start
	LPC_ADC->ADCR &=~(7 << 24);
	
	if((chsel>>3)&1){
		/*initialize channel 3*/
		LPC_PINCON->PINSEL1  &=~(3 << 20);
		LPC_PINCON->PINSEL1  |= (1 << 20);
		LPC_PINCON->PINMODE1 &=~(3 << 20);
		LPC_PINCON->PINMODE1 |= (2 << 20);
	}
	if((chsel>>4)&1){
		/*initialize channel 4*/
		LPC_PINCON->PINSEL3  |= (3 << 28);
		LPC_PINCON->PINMODE3 &=~(3 << 28);
		LPC_PINCON->PINMODE3 |= (2 << 28);
	}
	if((chsel>>5)&1){
		/*initialize channel 5*/
		LPC_PINCON->PINSEL3  |= (3 << 30);
		LPC_PINCON->PINMODE3 &=~(3 << 30);
		LPC_PINCON->PINMODE3 |= (2 << 30);
	}
	if(intEn){
		LPC_ADC->ADINTEN |= (0xFF);
		LPC_ADC->ADINTEN &=~(1<<8);
		NVIC_ClearPendingIRQ(ADC_IRQn);
		NVIC_SetPriority(ADC_IRQn, PRIO_ADC_IRQN);
		NVIC_EnableIRQ(ADC_IRQn);
	}
}

void ADC_StartCnv(uint8_t chsel, uint8_t burst){
	LPC_ADC->ADCR &=~ (0xFF);
	LPC_ADC->ADCR |= chsel;
	if(!burst){
		LPC_ADC->ADCR &=~ (7 << 24);
		LPC_ADC->ADCR |=  (1 << 24);
	}
}

void ADC_StopCnv(void){
	LPC_ADC->ADCR &=~ 0xFF;
}	

uint32_t ADC_Stat(void){
		return LPC_ADC->ADSTAT;
}

uint16_t ADC_GetValue(unsigned int channel){
	switch(channel){
		case 0: return ((LPC_ADC->ADDR0 >> 4)&(0xFFF));
		case 1: return ((LPC_ADC->ADDR1 >> 4)&(0xFFF));
		case 2: return ((LPC_ADC->ADDR2 >> 4)&(0xFFF));
		case 3: return ((LPC_ADC->ADDR3 >> 4)&(0xFFF));
		case 4: return ((LPC_ADC->ADDR4 >> 4)&(0xFFF));
		case 5: return ((LPC_ADC->ADDR5 >> 4)&(0xFFF));
		case 6: return ((LPC_ADC->ADDR6 >> 4)&(0xFFF));
		case 7: return ((LPC_ADC->ADDR7 >> 4)&(0xFFF));
		default: return 0;
	}
}
