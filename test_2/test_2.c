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
	
	// Initialize switches
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

#include "GLCD.h"
#include "gpio.h"
#include "keys.h"
#include "lcd.h"

int main(void){	
	// Initialize LCD-Display, write headlines
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(Yellow);
	GLCD_DisplayString(0,3,FONT_16x24,(unsigned char*)"Lab microproc.");
	GLCD_DisplayString(1,2,FONT_16x24,(unsigned char*)"test2.2 switches");
	GLCD_DisplayString(2,5,FONT_16x24,(unsigned char*)"Group A.10"); //TO-DO: Set correct group
	
	// write data fields
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4, 0, FONT_16x24,(unsigned char*)"bin:");
	GLCD_DisplayString(5, 0, FONT_16x24,(unsigned char*)"hex:");
	GLCD_DisplayString(6, 0, FONT_16x24,(unsigned char*)"dez:");
	
	// Initialize switches
	Switch_Init();
	GLCD_Simulation();


	while(1){	
		GLCD_Simulation();
		GLCD_DisplayString(4, 4, FONT_16x24, (unsigned char*)lcd_bin(Get_SwitchPos()));
		GLCD_DisplayString(5, 4, FONT_16x24, (unsigned char*)lcd_hex(Get_SwitchPos()));
		GLCD_DisplayString(6, 4, FONT_16x24, (unsigned char*)lcd_dez(Get_SwitchPos()));
		GLCD_Bargraph(14, 215, 192, 20, (int)4 * Get_SwitchPos());
	}
	
}	// end main()

#endif


//
//================================================================================
//  Test T2_3
//================================================================================
#if (T2_3 == 1)

#include "GLCD.h"
#include "gpio.h"
#include "keys.h"
#include "lcd.h"

int main(void){	
	int value = 0;
	
	// Initialize LCD-Display, write headlines
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Yellow);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(0,1,FONT_16x24,(unsigned char*)"Lab microprocessor");
	GLCD_DisplayString(1,1,FONT_16x24,(unsigned char*)"Test2.3: volt/temp");
	GLCD_DisplayString(2,5,FONT_16x24,(unsigned char*)"Group A.10"); //TO-DO: Set correct group
	
	// set colors
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	
	// Initialize switches
	Switch_Init();
	GLCD_Simulation();

	
	while(1){	
		GLCD_Simulation();
		value = (Get_SwitchPos() << 4)|0xF;
		GLCD_DisplayString(4, 1, FONT_16x24, (unsigned char*)"Value");
		GLCD_DisplayString(4, 7, FONT_16x24, (unsigned char*)lcd_dez(value));
		GLCD_DisplayString(4, 14, FONT_16x24, (unsigned char*)AD_volt(value));
		GLCD_DisplayString(5, 1, FONT_16x24, (unsigned char*)"Temp.");
		GLCD_DisplayString(5, 13, FONT_16x24, (unsigned char*)TempConv(value));
	}
	
}	// end main()

#endif



//
//================================================================================
//  Test T2_4
//================================================================================
#if (T2_4 == 1)

#include "GLCD.h"
#include "gpio.h"
#include "keys.h"
#include "lcd.h"

int main(void){	
	unsigned char lastKey = 0x20;
	// Initialize LCD-Display, write headlines
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(Yellow);
	GLCD_DisplayString(0,3,FONT_16x24,(unsigned char*)"Lab microproc.");
	GLCD_DisplayString(1,1,FONT_16x24,(unsigned char*)"test2.4: matrix");
	GLCD_DisplayString(2,5,FONT_16x24,(unsigned char*)"Group A.10"); //TO-DO: Set correct group
	
	// set colors
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(6, 1, FONT_16x24, (unsigned char*)"Taste:");
	
	// Initialize matrix
	Matrix_Init();
	GLCD_Simulation();
	GPIOSetValue(2, 3, PORT_PIN_LOW);
	GPIOSetValue(2, 4, PORT_PIN_LOW);
	GPIOSetValue(2, 5, PORT_PIN_LOW);

	
	while(1){	
		GLCD_Simulation();
		if(Get_Mkey() != 0x20){ lastKey = Get_Mkey(); }
		else{
			GLCD_DisplayChar(6, 10, FONT_16x24, lastKey);
		}
	}
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



