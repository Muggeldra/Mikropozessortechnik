/******************************************************************************

test_6.c

	Autor: 
	Datum: 

********************************************************************************/

//================================================================================
//Einbinden v. Header Files:
//================================================================================
#include <LPC17xx.h>
#include <stdio.h>

#include "tests.h"
#include "delay.h"
#include "glcd.h"
#include "gpio.h"
#include "lcd.h"

//================================================================================
//Definition v. Konstanten:
//================================================================================

#define FONT_6x8   0     //Font-Index für ASCII Font 6x8
#define FONT_16x24 1     //Font-Index für ASCII Font 16x24

//================================================================================
//  test T6_1
//================================================================================
#if (T6_1==1)

static unsigned int ticks = 0;
static unsigned int seconds = 0;
const unsigned char SegChars[10] = {0x24, 0xAF, 0xE0, 0xA2, 0x2B, 0x32, 0x30, 0xA7, 0x20, 0x22};
static unsigned char outLeft, outRight;

void SysTick_Handler(void){
		ticks++;
	
		// seconds variable
		if(!(ticks % 100)){
			seconds++;
			if(seconds >= 60){
				seconds = 0;
			}
			// generate output
			outLeft = SegChars[(seconds/10)%10];
			outRight = SegChars[seconds%10];
		}
		if(ticks%2){
			GPIOSetValue(0, 1, 1);
			LPC_SSP0->DR = outRight;
			GPIOSetValue(3,25, 0);
		}
		else{
			GPIOSetValue(3,25, 1);
			LPC_SSP0->DR = outLeft;
			GPIOSetValue(0, 1, 0);
		}
}

int main(void)
{	
	// systick 10ms
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/100);
	SysTick_Handler();
	
	// LCD Init
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Maroon);
	GLCD_SetTextColor(Yellow);
	GLCD_DisplayString(0,3,FONT_16x24,(unsigned char*)"Lab microproc.");
	GLCD_DisplayString(1,2,FONT_16x24,(unsigned char*)"test2.2 switches");
	GLCD_DisplayString(2,5,FONT_16x24,(unsigned char*)"Group A.7"); //TO-DO: Set correct group
	
	GLCD_DisplayString(4, 1, FONT_16x24, (unsigned char*)"sec:");
	GLCD_DisplayString(4, 1, FONT_16x24, (unsigned char*)"out left:");
	GLCD_DisplayString(4, 1, FONT_16x24, (unsigned char*)"out right:");
	
	// SPI Init
	LPC_PINCON->PINSEL0 &=~ (3<<30); //P0.15
	LPC_PINCON->PINSEL0 |=  (2<<30);
	LPC_PINCON->PINSEL1 &=~ 0x3F; //P0.16-18
	LPC_PINCON->PINSEL1 |=  0x2A;
	LPC_PINCON->PINMODE1 &=~ (3<<2); //P0.17 neither pull up nor pull down
	LPC_PINCON->PINMODE1 |=  (2<<2);
	
	LPC_SC->PCLKSEL1 &=~ (3<<10); //clk = cclk
	LPC_SC->PCLKSEL1 |=  (1<<10);
	
	LPC_SSP0->CR0 &=~ (0xFFFF); //control register 0
	LPC_SSP0->CR0 |=  (0x0007);
	
	LPC_SSP0->CPSR = 100; //clock prescale
	
	LPC_SSP0->CR1 = 2; //control register 1
	
	// gpio init
	GPIOSetDir(0, 1, 1);
	GPIOSetDir(3,25, 1);
	
	GPIOSetValue(0, 1, 1);
	GPIOSetValue(3,25, 1);

	while(1)
	{
		GLCD_DisplayString(4, 1, FONT_16x24, (unsigned char*)lcd_dez(seconds));
		GLCD_DisplayString(4, 1, FONT_16x24, (unsigned char*)lcd_hex(outLeft));
		GLCD_DisplayString(4, 1, FONT_16x24, (unsigned char*)lcd_hex(outRight));
	} // end while(1)
}	// end main()


#endif


//
//================================================================================
//  test T6_2
//================================================================================
#if (T6_2==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  test T6_3
//================================================================================
#if (T6_3==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  test T6_4
//================================================================================
#if (T6_4==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  test T6_5
//================================================================================
#if (T6_5==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif


#if (T6_6==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  test T6_7
//================================================================================
#if (T6_7==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

