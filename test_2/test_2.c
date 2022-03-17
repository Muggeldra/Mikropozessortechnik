/******************************************************************************
test_2.c
*******************************************************************************
	Autor: 
	Datum: 

********************************************************************************/

//================================================================================
//include Header Files:
//================================================================================
#include <LPC17xx.h>
#include "tests.h"
#include "GLCD.h"


//================================================================================
//Definitions and constants:
//================================================================================

#define FONT_6x8   0     //Font-Index für ASCII Font 6x8
#define FONT_16x24 1     //Font-Index für ASCII Font 16x24


//================================================================================
//  Test T2_1
//================================================================================
#if (T2_1 == 1)

#include "GLCD.h"
#include "gpio.h"
#include "keys.h"
#include "lcd.h"


#define OUT_PORT PORT2
#define PORT_PIN 2


int main(void){	
	// Initialize LCD-Display, write headlines
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(Yellow);
	GLCD_DisplayString(0,3,FONT_16x24,(unsigned char*)"Lab microproc.");
	GLCD_DisplayString(1,1,FONT_16x24,(unsigned char*)"test2.1 switchpos");
	GLCD_DisplayString(2,5,FONT_16x24,(unsigned char*)"Group A.10"); //TO-DO: Set correct group
	
	// write data fields
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4, 0, FONT_16x24,(unsigned char*)"bin:");
	GLCD_DisplayString(5, 0, FONT_16x24,(unsigned char*)"hex:");
	GLCD_DisplayString(6, 0, FONT_16x24,(unsigned char*)"dez:");
	
	// TO-DO: Initialize switches
	Switch_Init();
	GLCD_Simulation();


	while(1){	
		GLCD_Simulation();
		GLCD_DisplayString(4, 4, FONT_16x24, (unsigned char*)lcd_bin(Get_SwitchPos()));
		GLCD_DisplayString(5, 4, FONT_16x24, (unsigned char*)lcd_hex(Get_SwitchPos()));
		GLCD_DisplayString(6, 4, FONT_16x24, (unsigned char*)lcd_dez(Get_SwitchPos()));
	}
	
}	// end main()

#endif


//
//================================================================================
//  Test T2_2
//================================================================================
#if (T2_2 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif


//
//================================================================================
//  Test T2_3
//================================================================================
#if (T2_3 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif



//
//================================================================================
//  Test T2_4
//================================================================================
#if (T2_4 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif


//
//================================================================================
//  Test T2_5
//================================================================================
#if (T2_5 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  Test T2_6
//================================================================================
#if (T2_6 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif



