/******************************************************************************
test_1.c
******************************************************************************/


//	Autor: 
//	date: 
	       

/********************************************************************************/

//================================================================================
//include Header Files:
//================================================================================
#include <LPC17xx.h>
#include "tests.h"
#include "GLCD.h"
#include "gpio.h"
#include "delay.h"
#include "led.h"
#include "keys.h"

//================================================================================
//definition constants:
//================================================================================


//================================================================================
//  Main-Funktion Test1 T1_1
//================================================================================
#if (T1_1 == 1)


#define OUT_PORT 0
#define PORT_PIN 0

int main(void)
{	
	int TA12StateBefore = 0;
	int TA11StateBefore = 0;
	int TA10StateBefore = 0;
	
	int LeftStateBefore = 0;
	int RightStateBefore = 0;
	int UpStateBefore = 0;
	int DownStateBefore = 0;
	int CenterStateBefore = 0;
	
	GLCD_Init();
	
	GPIOSetDir(OUT_PORT, PORT_PIN, GPIO_OUTPUT);
	GPIOSetValue(OUT_PORT,PORT_PIN,PORT_PIN_LOW);
	
	while(1)
	{	
		//prep 1.6
		LED_Out(Get_SwitchPos());
		
		//prep 1.7
		//Red
		RGB_FlipFlop(1,Get_TA12Stat(),TA12StateBefore);
		
		

		
		
		GPIOSetValue(OUT_PORT,PORT_PIN,PORT_PIN_HIGH);
		GLCD_Simulation();
		delayXms(5);
		GPIOSetValue(OUT_PORT,PORT_PIN,PORT_PIN_LOW);	
		GLCD_Simulation();
		delayXms(5);
	}
	
}	// end main()
#endif


//================================================================================
//  Main-Function Test T1_2
//================================================================================
#if (T1_2 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif



//================================================================================
//  Main-Function Test T1_3
//================================================================================
#if (T1_3 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif



//================================================================================
//  Main-Function TestT1_4
//================================================================================
#if (T1_4 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//================================================================================
//  Main-Function Test T1_5
//================================================================================
#if (T1_5 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif


//================================================================================
//  Main-Function Test T1_6
//================================================================================
#if (T1_6 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif


//================================================================================
//  Main-Funktion Test T1_7
//================================================================================
#if (T1_7 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

