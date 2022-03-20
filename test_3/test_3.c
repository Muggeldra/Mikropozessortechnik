/******************************************************************************

test_3.c

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


//================================================================================
//Definition v. Konstanten:
//================================================================================

#define FONT_6x8   0     //Font-Index für ASCII Font 6x8
#define FONT_16x24 1     //Font-Index für ASCII Font 16x24

//================================================================================
//  Test T3_1
//================================================================================
#if (T3_2 == 1)
static unsigned int ticks = 0;
void SysTick_Handler(void){
		ticks++;
	}
int main(void)
{	
	void SysTick_Handler(void);
	// Initialize LCD-Display, write headlines
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Green);
	GLCD_SetTextColor(Yellow);
	GLCD_DisplayString(0,3,FONT_16x24,(unsigned char*)"Lab microproc.");
	GLCD_DisplayString(1,1,FONT_16x24,(unsigned char*)"test3.1 SystemTick");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)""); 
	GLCD_DisplayString(3,0,FONT_16x24,(unsigned char*)"LED0 Flashes"); 
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"50ms on, 150ms off,"); 
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"50ms on, 750ms off,"); 
	LED_Init();
	LED_On(0);
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/100);
	SysTick_Handler();
	
	

	while(1)
	{
		GLCD_Simulation();
				
		if(ticks > 100){
			LED_On(0);
			ticks = 0;
		}
		else if(ticks > 25){
			LED_Off(0);
		}
		else if(ticks > 20){
			LED_On(0);
		}
		else if(ticks > 5){
			LED_Off(0);
		}
		
	} // end while(1)
}	// end main()

#endif


//
//================================================================================
//  Main-Funktion Versuchsteil T3_2
//================================================================================
#if (T3_3 == 1)
int count_TA12_int = 0;

void EINT1_IRQ_Init(void){
	LPC_SC->PCONP |= (1<<15);
	LPC_PINCON->PINSEL4 &=~ (3<<22);
	LPC_PINCON->PINSEL4 |= (1<<22);
	LPC_PINCON->PINMODE4 &=~ (3<<22);
	LPC_PINCON->PINMODE4 |= (2<<22);
	LPC_SC->EXTMODE |= (1<<1);
	LPC_SC->EXTPOLAR |= (1<<1);
	LPC_SC->EXTINT |= (1<<1);
	NVIC_ClearPendingIRQ(EINT1_IRQn);
	NVIC_SetPriority(EINT1_IRQn, prioTA12);
	NVIC_EnableIRQ(EINT1_IRQn);
}

void EINT1_IRQHandler(void){
	LPC_SC->EXTINT |= (1<<1);
	count_TA12_int++;
}

int main(void)
{	
	EINT1_IRQ_Init();
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Green);
	GLCD_SetTextColor(Yellow);
	GLCD_DisplayString(1,1,FONT_16x24,(unsigned char*)"LAB 3.2"); 

	while(1)
	{
		GLCD_Simulation();
		GLCD_DisplayString(2,1,FONT_16x24,(unsigned char*)lcd_dez(count_TA12_int)); 
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  Main-Funktion Versuchsteil T3_3
//================================================================================
#if (T3_1 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif



//
//================================================================================
//  Main-Funktion Versuchsteil T3_4
//================================================================================
#if (T3_4 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif


//
//================================================================================
//  Test T3_5
//================================================================================
#if (T3_5 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif



//
//================================================================================
//  Test T3_6
//================================================================================
#if (T3_6 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  Test T3_7
//================================================================================

#if (T3_7 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

