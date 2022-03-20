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
	GLCD_DisplayString(0,3,FONT_16x24,(unsigned char*)"Lab microproc.");
	GLCD_DisplayString(1,2,FONT_16x24,(unsigned char*)"test3.2 TA12-Int.");
	GLCD_DisplayString(2,5,FONT_16x24,(unsigned char*)"Group A.10"); //TO-DO: Set correct group

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
#if (T3_4 == 1)

	int counterUp = 0;
	int counterDown = 0;
	int counterLeft = 0;
	int counterRight = 0;
	
	void EINT3_IRQHandler(void){
		if(LPC_GPIOINT->IO0IntStatR & (1<<21)){LPC_GPIOINT->IO0IntClr |= (1<<21); counterUp++;}
		if(LPC_GPIOINT->IO0IntStatR & (1<<27)){LPC_GPIOINT->IO0IntClr |= (1<<27); counterDown++;}
		if(LPC_GPIOINT->IO0IntStatR & (1<<25)){LPC_GPIOINT->IO0IntClr |= (1<<25); counterLeft++;}
		if(LPC_GPIOINT->IO0IntStatR & (1<<28)){LPC_GPIOINT->IO0IntClr |= (1<<28); counterRight++;}
		if(LPC_GPIOINT->IO0IntStatR & (1<<3)){LPC_GPIOINT->IO0IntClr |= (1<<3); counterUp = 0; counterDown = 0; counterLeft = 0; counterRight = 0;}
	}

int main(void)
{	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Green);
	GLCD_SetTextColor(Yellow);
	GLCD_DisplayString(0,3,FONT_16x24,(unsigned char*)"Lab microproc.");
	GLCD_DisplayString(1,2,FONT_16x24,(unsigned char*)"test3.3 Joyst.-Int.");
	GLCD_DisplayString(2,5,FONT_16x24,(unsigned char*)"Group A.10"); //TO-DO: Set correct group
	
	JoyStick_IRQ_Init();
	
	while(1)
	{
		GLCD_Simulation();
		GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"up:");
		GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"down:");
		GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"left:");
		GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"right:");
		GLCD_DisplayString(4,7,FONT_16x24,(unsigned char*)lcd_dez(counterUp));
		GLCD_DisplayString(5,7,FONT_16x24,(unsigned char*)lcd_dez(counterDown));
		GLCD_DisplayString(6,7,FONT_16x24,(unsigned char*)lcd_dez(counterLeft));
		GLCD_DisplayString(7,7,FONT_16x24,(unsigned char*)lcd_dez(counterRight));
		
	} // end while(1)
}	// end main()

#endif



//
//================================================================================
//  Main-Funktion Versuchsteil T3_4
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

