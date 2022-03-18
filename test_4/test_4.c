/******************************************************************************

test_4.c

	Autor: 
	Datum: 

********************************************************************************/

//================================================================================
//Einbinden v. Header Files:
//================================================================================
#include <LPC17xx.h>
#include <stdio.h>

#include "tests.h"
#include "GLCD.h"
#include "adc.h"
#include "lcd.h"

//================================================================================
//Definition v. Konstanten:
//================================================================================

#define FONT_6x8   0     //Font-Index für ASCII Font 6x8
#define FONT_16x24 1     //Font-Index für ASCII Font 16x24

//
//================================================================================
//  Test T41_1
//================================================================================
#if (T41_1==1)

uint16_t result3 = 0;

int main(void)
{
	// Initialize LCD-Display, write headlines
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Yellow);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(0,1,FONT_16x24,(unsigned char*)"Lab microprocessor");
	GLCD_DisplayString(1,3,FONT_16x24,(unsigned char*)"test4.1.1: ADC");
	GLCD_DisplayString(2,5,FONT_16x24,(unsigned char*)"Group A.10"); //TO-DO: Set correct group

	// write data fields
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(6, 0, FONT_16x24,(unsigned char*)"LM35 AD0.3");
	
	// test from script
	ADC_Init((1<<3),0); //initialize channel 3 without interrupt -
	ADC_StartCnv((1<<3), 0);
	while(1){
		while (!((ADC_Stat()>>3)&1)){//wait for end of conversion
			result3 = ADC_GetValue(3);	//output result3 to the LCD
			GLCD_DisplayString(6, 13, FONT_16x24, (unsigned char*)lcd_dez(result3));
			ADC_StartCnv((1<<3), 0);
		}
	}
}	// end main()

#endif

//
//================================================================================
//  Test T41_2
//================================================================================
#if (T41_2==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif



//
//================================================================================
//  Test T41_3
//================================================================================
#if (T41_3==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif
//
//================================================================================
//  Test T41_4
//================================================================================
#if (T41_4==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  Test T41_5
//================================================================================
#if (T41_5==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  Test T41_6
//================================================================================
#if (T41_6==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  Test T42_1
//================================================================================
#if (T42_1==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  Test T42_2
//================================================================================
#if (T42_2==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif
