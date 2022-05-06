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
		
		switch(ResetMR){
			case 0: 
				LPC_TIM0->MR0 = cycle -1;
				LPC_TIM0->MCR |= (3 <<0);
				LPC_TIM0->EMR = (3UL<<4);
				LPC_TIM0->IR |= (1<<0);
			break;
			case 1: 
				LPC_TIM0->MR1 = cycle -1;
				LPC_TIM0->MCR |= (3 <<3);
				LPC_TIM0->EMR = (3UL<<6);
				LPC_TIM0->IR |= (1<<1);
			break;
			case 2: 
				LPC_TIM0->MR2 = cycle -1;
				LPC_TIM0->MCR |= (3 <<6);
				LPC_TIM0->EMR = (3UL<<8);
				LPC_TIM0->IR |= (1<<2);
			break;
			case 3: 
				LPC_TIM0->MR3 = cycle -1;
				LPC_TIM0->MCR |= (3 <<9);
				LPC_TIM0->EMR = (3UL<<10);
				LPC_TIM0->IR |= (1<<3);
			break;
			default:
				break;
		}
		
		NVIC_SetPriority(TIMER0_IRQn, prioTimer0);
		NVIC_ClearPendingIRQ(TIMER0_IRQn);
		NVIC_EnableIRQ(TIMER0_IRQn);
		break;
		case 1:
		LPC_SC->PCONP |= (1<<2);
		LPC_TIM1->CTCR = 0;
		LPC_TIM1->TCR |= (1<<1);
		
		LPC_SC->PCLKSEL0 |= (pclk<<4);
		LPC_TIM1->PR = SystemCoreClock/TimerDivid-1;
		LPC_TIM1->TCR = (1<<0);
		
		switch(ResetMR){
			case 0: 
				LPC_TIM1->MR0 = cycle -1;
				LPC_TIM1->MCR |= (3 <<0);
				LPC_TIM1->EMR = (3UL<<4);
				LPC_TIM1->IR |= (1<<0);
			break;
			case 1: 
				LPC_TIM1->MR1 = cycle -1;
				LPC_TIM1->MCR |= (3 <<3);
				LPC_TIM1->EMR = (3UL<<6);
				LPC_TIM1->IR |= (1<<1);
			break;
			case 2: 
				LPC_TIM1->MR2 = cycle -1;
				LPC_TIM1->MCR |= (3 <<6);
				LPC_TIM1->EMR = (3UL<<8);
				LPC_TIM1->IR |= (1<<2);
			break;
			case 3: 
				LPC_TIM1->MR3 = cycle -1;
				LPC_TIM1->MCR |= (3 <<9);
				LPC_TIM1->EMR = (3UL<<10);
				LPC_TIM1->IR |= (1<<3);
			break;
			default:
				break;
		}
		
		NVIC_SetPriority(TIMER1_IRQn, prioTimer1);
		NVIC_ClearPendingIRQ(TIMER1_IRQn);
		NVIC_EnableIRQ(TIMER1_IRQn);
		break;
		case 2:
		LPC_SC->PCONP |= (1<<22);
		LPC_TIM2->CTCR = 0;
		LPC_TIM2->TCR |= (1<<1);
		
		LPC_SC->PCLKSEL1 |= (pclk<<12);
		LPC_TIM2->PR = SystemCoreClock/TimerDivid-1;
		LPC_TIM2->TCR = (1<<0);
		
		switch(ResetMR){
			case 0: 
				LPC_TIM2->MR0 = cycle -1;
				LPC_TIM2->MCR |= (3 <<0);
				LPC_TIM2->EMR = (3UL<<4);
				LPC_TIM2->IR |= (1<<0);
			break;
			case 1: 
				LPC_TIM2->MR1 = cycle -1;
				LPC_TIM2->MCR |= (3 <<3);
				LPC_TIM2->EMR = (3UL<<6);
				LPC_TIM2->IR |= (1<<1);
			break;
			case 2: 
				LPC_TIM2->MR2 = cycle -1;
				LPC_TIM2->MCR |= (3 <<6);
				LPC_TIM2->EMR = (3UL<<8);
				LPC_TIM2->IR |= (1<<2);
			break;
			case 3: 
				LPC_TIM2->MR3 = cycle -1;
				LPC_TIM2->MCR |= (3 <<9);
				LPC_TIM2->EMR = (3UL<<10);
				LPC_TIM2->IR |= (1<<3);
			break;
			default:
				break;
		}
		
		NVIC_SetPriority(TIMER2_IRQn, prioTimer2);
		NVIC_ClearPendingIRQ(TIMER2_IRQn);
		NVIC_EnableIRQ(TIMER2_IRQn);
		break;
		case 3:
		LPC_SC->PCONP |= (1<<23);
		LPC_TIM3->CTCR = 0;
		LPC_TIM3->TCR |= (1<<1);
		
		LPC_SC->PCLKSEL1 |= (pclk<<14);
		LPC_TIM3->PR = SystemCoreClock/TimerDivid-1;
		LPC_TIM3->TCR = (1<<0);
		
		switch(ResetMR){
			case 0: 
				LPC_TIM3->MR0 = cycle -1;
				LPC_TIM3->MCR |= (3 <<0);
				LPC_TIM3->EMR = (3UL<<4);
				LPC_TIM3->IR |= (1<<0);
			break;
			case 1: 
				LPC_TIM3->MR1 = cycle -1;
				LPC_TIM3->MCR |= (3 <<3);
				LPC_TIM3->EMR = (3UL<<6);
				LPC_TIM3->IR |= (1<<1);
			break;
			case 2: 
				LPC_TIM3->MR2 = cycle -1;
				LPC_TIM3->MCR |= (3 <<6);
				LPC_TIM3->EMR = (3UL<<8);
				LPC_TIM3->IR |= (1<<2);
			break;
			case 3: 
				LPC_TIM3->MR3 = cycle -1;
				LPC_TIM3->MCR |= (3 <<9);
				LPC_TIM3->EMR = (3UL<<10);
				LPC_TIM3->IR |= (1<<3);
			break;
			default:
				break;
		}
		
		NVIC_SetPriority(TIMER3_IRQn, prioTimer3);
		NVIC_ClearPendingIRQ(TIMER3_IRQn);
		NVIC_EnableIRQ(TIMER3_IRQn);
		break;
	}
}
