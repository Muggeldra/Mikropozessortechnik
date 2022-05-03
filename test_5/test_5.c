/*******************************************************************************

test5.c


	Autor: 
	Datum: 

********************************************************************************/

//================================================================================
//include Header Files:
//================================================================================
#include <LPC17xx.h>
#include <stdio.h>
#include "core_cm3.h"
#include "tests.h"
#include "GLCD.h"
#include "gpio.h"
#include "delay.h"
#include "led.h"
#include "keys.h"
#include "prio.h"
#include "lcd.h"
#include "Timer.h"

//================================================================================
//Definition 
//================================================================================

#define FONT_6x8   0     //Font-Index für ASCII Font 6x8
#define FONT_16x24 1     //Font-Index für ASCII Font 16x24


//================================================================================
//  test T51
//================================================================================
#if (T5_1==1)



int main(void)
{	
	//counter_Init(0,1,1);
	uint32_t tcvalue = 0;
	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Red);
	GLCD_SetTextColor(Yellow);
	GLCD_DisplayString(0,3,FONT_16x24,(unsigned char*)"Lab microproc.");
	GLCD_DisplayString(1,1,FONT_16x24,(unsigned char*)"test5.1 Counter");
	
	
	counter_Init(0,1,1);

	while(1)
	{
		tcvalue = LPC_TIM0->TC;
		GLCD_DisplayString(4,7,FONT_16x24,(unsigned char*)lcd_dez(tcvalue));
		
	} // end while(1)
}	// end main()

#endif



#if (T5_2==1)
//
//================================================================================
//  test T52
//================================================================================
uint32_t tcvalue=0; 
uint32_t tcvalueBefore=0;

void TIMER0_IRQHandler(void){
	
	if(LPC_TIM0->IR & (1<<0)){
		LPC_TIM0->IR |= (1<<0);
		GPIOToggle(2,5);
	}
	
}


int main (){ 
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Red);
	GLCD_SetTextColor(Yellow);
	GLCD_DisplayString(0,3,FONT_16x24,(unsigned char*)"Lab microproc.");
	GLCD_DisplayString(1,1,FONT_16x24,(unsigned char*)"test5.2 Timer");
	
	
	Timer_Init (0,1000,1000000,1,0); 
	//timer0, counts: 0..999, divider=1, pclk=cclk, reset with MR0 
	LPC_TIM0->TCR=(1<<0);//start timer 0 
	
	GPIOSetDir(2, 0, 1);
	GPIOSetDir(2, 5, 1);
	
	while(1){
		//GLCD_Simulation();
		tcvalue=LPC_TIM0->TC;
		if(tcvalue != tcvalueBefore){
			GPIOToggle(2,1);
			tcvalueBefore=tcvalue;
		}
		
		GLCD_DisplayString(4,7,FONT_16x24,(unsigned char*)lcd_dez(tcvalue));
	} 
}

#endif

#if (T5_3==1)
void TIMER0_IRQHandler(void){
	if(LPC_TIM0->IR & (1<<4)){
		//CAP 0.0
		LPC_TIM0->IR |= (1<<4);
		LPC_GPIO2->FIOPIN ^= (1<<10); 
	}
	else if(LPC_TIM0->IR & (1<<5)){
		//CAP 0.1
		LPC_TIM0->IR |= (1<<5);
		LPC_GPIO2->FIOPIN ^= (1<<10); 
	}
}

int main(void)
{	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Red);
	GLCD_SetTextColor(Yellow);
	GLCD_DisplayString(0,3,FONT_16x24,(unsigned char*)"Lab microproc.");
	GLCD_DisplayString(1,1,FONT_16x24,(unsigned char*)"test5.3 PWM");
	
	Timer_Init (0,100,100000000,1,0); 
	//capture Interrupt 0.0
	LPC_PINCON->PINSEL3 |= (3<<20);
	LPC_PINCON->PINMODE3 &=~ (3<<20);
	LPC_PINCON->PINMODE3 |= (2<<20);
	LPC_TIM0->CCR |= (1<<0);
	LPC_TIM0->CCR |= (1<<2);

	//capture Interrupt 0.1
	LPC_PINCON->PINSEL3 |= (3<<22);
	LPC_PINCON->PINMODE3 &=~ (3<<22);
	LPC_PINCON->PINMODE3 |= (2<<22);
	LPC_TIM0->CCR |= (1<<4);
	LPC_TIM0->CCR |= (1<<5);
	
	NVIC_SetPriority(TIMER0_IRQn, prioCaptureInterrupt);
	LPC_TIM0->IR |= (1<<4);
	NVIC_ClearPendingIRQ(TIMER0_IRQn);
	NVIC_EnableIRQ(TIMER0_IRQn);
	GPIOSetDir(2,5,1);
	

	while(1)
	{
		
	} // end while(1)
}	// end main()



#endif

//
//================================================================================
//  test T54
//================================================================================
#if (T5_4==1)
/*
uint32_t dutyCycleR = 20;
uint32_t counterR = 0;

void TIMER2_IRQHandler(void){
	
	if(LPC_TIM2->IR & (1<<0)){
		LPC_TIM2->IR |= (1<<0);
	}
}

void TIMER3_IRQHandler(void){
	
	if(LPC_TIM3->IR & (1<<0)){
		counterR++;
		if(counterR > dutyCycleR){
			LPC_TIM3->IR |= (1<<0);
		}
		else if(counterR >= 100){
			//LPC_TIM3->IR |= (1<<0);
			counterR = 0;
		}
		
	}
	/*
	if(LPC_TIM3->IR & (1<<1)){
		LPC_TIM3->IR |= (1<<1);
	}*//*
}

int main(void)
{	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Red);
	GLCD_SetTextColor(Yellow);
	GLCD_DisplayString(0,3,FONT_16x24,(unsigned char*)"Lab microproc.");
	GLCD_DisplayString(1,1,FONT_16x24,(unsigned char*)"test5.4 RGB PWM");
	
	LPC_SC->PCONP |= (1<<15);
	
	Timer_Init (2,100,100000000,1,0); 
	LPC_PINCON->PINSEL9 &=~ (3<<26);	//MAT 2.1
	LPC_PINCON->PINSEL9 |= (2<<26);
	LPC_GPIO4->FIODIR |= (1<<29);
	LPC_TIM2->EMR |= (11<<6);
	
	Timer_Init (3,100,100000000,1,0);
	LPC_PINCON->PINSEL0 |= (3<<20);		//MAT 3.0
	LPC_GPIO0->FIODIR |= (1<<10);
	LPC_TIM3->EMR |= (11<<4);
	
	Timer_Init (3,100,100000000,1,1);
	LPC_PINCON->PINSEL0 |= (3<<22);		//MAT 3.1
	LPC_GPIO0->FIODIR |= (1<<11);
	LPC_TIM3->EMR |= (11<<6);

	while(1)
	{
		
	} // end while(1)
}	// end main()
*/

extern uint8_t var1;
void Timer3_IRQHandler(void) {
 if(LPC_TIM3->IR & (1UL<<2)) {
 LPC_TIM3->IR = (1UL<<2); // %value% = 0:MR0, 1:MR1, 2:MR2, 3:MR3
 //…
 }
}

int main(void)
{
	//Setup Timer 3
	LPC_SC->PCONP |= (1UL<<23);
	LPC_PINCON->PINSEL0 |= (3UL<<22);
	LPC_SC->PCLKSEL1 |= (1UL<<14);
	SystemCoreClockUpdate();
	LPC_TIM3->PR = SystemCoreClock/(1000000)-1;
	LPC_TIM3->MR1 = 1000;
	LPC_TIM3->MCR |= (1UL<<4);
	LPC_TIM3->EMR &= ~(1UL<<1);
	LPC_TIM3->EMR |= (3UL<<6);
	NVIC_SetPriority(TIMER3_IRQn, 12);
	NVIC_ClearPendingIRQ(TIMER3_IRQn);
	NVIC_EnableIRQ(TIMER3_IRQn);
	LPC_TIM3->IR = 0x0F;
	LPC_TIM3->CTCR &= ~(3UL<<0);
	LPC_TIM3->TCR = (1UL<<1);
	LPC_TIM3->TCR = (1UL<<0);
	
	LPC_TIM3->MR0 = 100;	//PWM
	LPC_TIM3->MCR |= (1UL<<3);
	
	
	
	while(1)
	{
		
	}
}


#endif
//
//================================================================================
//  test T5_55
//================================================================================
#if (T5_5==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif


#if (T5_6==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//================================================================================
//  test T5_7
//================================================================================
#if (T5_7==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif


