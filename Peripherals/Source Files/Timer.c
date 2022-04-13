#include <LPC17xx.h>
#include "gpio.h"
#include "prio.h"

void counter_Init (uint8_t TimerNum, uint8_t CapIn, uint8_t edge){
	switch(TimerNum){
		case 0: 
			TimerNum = 1;
			LPC_SC->PCONP |= (1<<TimerNum);
			if(CapIn == 0){
				CapIn = 20;
			}
			else{
				CapIn = 22;
			}
			LPC_PINCON->PINSEL3 |= (3<<CapIn);
			LPC_PINCON->PINMODE3 &=~ (3<<CapIn);
			LPC_PINCON->PINMODE3 |= (2<<CapIn);
			LPC_TIM0->CTCR &=~(3<<2);
			if(CapIn == 22){LPC_TIM0->CTCR |=(1<<2);}
			LPC_TIM0->CTCR |= (edge);
			LPC_TIM0->TCR &=~ (1<<1);
			LPC_TIM0->TCR |= (1<<0);
		break;
		case 1: 
			TimerNum = 2;
			LPC_SC->PCONP |= (1<<TimerNum);
			LPC_TIM1->CTCR &=~(3<<2);
			if(CapIn == 0){
				CapIn = 4;
			}
			else{
				CapIn = 6;
				LPC_TIM1->CTCR |=(1<<2);
			}
			LPC_PINCON->PINSEL3 |= (3<<CapIn);
			LPC_PINCON->PINMODE3 &=~ (3<<CapIn);
			LPC_PINCON->PINMODE3 |= (2<<CapIn);
			LPC_TIM1->CTCR |= (edge);
			LPC_TIM1->TCR &=~ (1<<1);
			LPC_TIM1->TCR &=~ (1<<1);
		break;
		case 2: 
			TimerNum = 22;
			LPC_SC->PCONP |= (1<<TimerNum);
			LPC_TIM2->CTCR &=~(3<<2);
			if(CapIn == 0){
				CapIn = 8;
			}
			else{
				CapIn = 10;
				LPC_TIM2->CTCR |=(1<<2);
			}
			LPC_PINCON->PINSEL0 |= (3<<CapIn);
			LPC_PINCON->PINMODE0 &=~ (3<<CapIn);
			LPC_PINCON->PINMODE0|= (2<<CapIn);
			LPC_TIM2->CTCR |= (edge);
			LPC_TIM2->TCR &=~ (1<<1);
			LPC_TIM2->TCR &=~ (1<<1);
		break;
		case 3: 
			TimerNum = 23;
			LPC_SC->PCONP |= (1<<TimerNum);
			LPC_TIM3->CTCR &=~(3<<2);
			if(CapIn == 0){
				CapIn = 14;
			}
			else{
				CapIn = 16;
				LPC_TIM3->CTCR |=(1<<2);
			}
			LPC_PINCON->PINSEL1 |= (3<<CapIn);
			LPC_PINCON->PINMODE1 &=~ (3<<CapIn);
			LPC_PINCON->PINMODE1 |= (2<<CapIn);
			LPC_TIM3->CTCR |= (edge);
			LPC_TIM3->TCR &=~ (1<<1);
			LPC_TIM3->TCR &=~ (1<<1);
		break;
		default: break;
	}
}

void Timer_Init (uint8_t TimerNum, uint32_t cycle, uint32_t TimerDivid, uint8_t pclk , uint8_t ResetMR){
	SystemCoreClockUpdate();
	switch(TimerNum){
		case 0:
		LPC_SC->PCONP |= (1<<1);
		LPC_TIM0->CTCR = 0;
		LPC_TIM0->TCR |= (1<<1);
		
		LPC_SC->PCLKSEL0 |= (pclk<<2);
		LPC_TIM0->PR = SystemCoreClock/TimerDivid-1;
		LPC_TIM0->TCR = (1<<0);
		
		LPC_TIM0->MR0 = cycle -1;
		
		LPC_TIM0->MCR |= (3 <<0);
		//LPC_TIM0->EMR = (3UL<<4);
		LPC_TIM0->IR |= (1<<0);
		
		NVIC_SetPriority(TIMER0_IRQn, prioTimer);
		NVIC_ClearPendingIRQ(TIMER0_IRQn);
		NVIC_EnableIRQ(TIMER0_IRQn);
		
		break;
	}
}
