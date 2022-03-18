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

#define RGB_Red 1
#define RGB_Green 2
#define RGB_Blue 0

int main(void)
{	
	uint8_t walkingLight = 129;
	unsigned char previousSwitches = 0;
	uint32_t walkingLightDelay = 2617;
	uint32_t walkingLightTimer = 0;
	int walkingLightDirection = 0;
	
	int TA12StateBefore = 0;
	int TA11StateBefore = 0;
	int TA10StateBefore = 0;
	
	int LeftStateBefore = 0;
	int RightStateBefore = 0;
	int UpStateBefore = 0;
	int DownStateBefore = 0;
	int CenterStateBeforeR = 0;
	int CenterStateBeforeG = 0;
	int CenterStateBeforeB = 0;
	
	GLCD_Init();
	Switch_Init();
	button_Init();
	Joystick_Init();
	LED_Init();
	RGB_Init();
	
	GPIOSetDir(0,2,GPIO_OUTPUT);
	GPIOSetValue(0,2,0);
	
	GPIOSetDir(OUT_PORT, PORT_PIN, GPIO_OUTPUT);
	GPIOSetValue(OUT_PORT,PORT_PIN,PORT_PIN_LOW);
	
	while(1)
	{	
		
		GLCD_Simulation();
		//prep 1.6
		//LED_Out(Get_SwitchPos());
		
		//prep 1.7
		/*
		TA12StateBefore = RGB_FlipFlop(RGB_Red,Get_TA12Stat(),TA12StateBefore);
		TA10StateBefore = RGB_FlipFlop(RGB_Green,Get_TA10Stat(),TA10StateBefore);
		TA11StateBefore = RGB_FlipFlop(RGB_Blue,Get_TA11Stat(),TA11StateBefore);
		
		//prep 1.8
		LeftStateBefore = LED_FlipFlop(6,Get_LeftStat(),LeftStateBefore);
		RightStateBefore = LED_FlipFlop(2,Get_RightStat(),RightStateBefore);
		UpStateBefore = LED_FlipFlop(0,Get_UpStat(),UpStateBefore);
		DownStateBefore = LED_FlipFlop(4,Get_DownStat(),DownStateBefore);
		
		CenterStateBeforeR = RGB_FlipFlop(RGB_Red,Get_CenterStat(),CenterStateBeforeR);
		CenterStateBeforeG = RGB_FlipFlop(RGB_Green,Get_CenterStat(),CenterStateBeforeG);
		CenterStateBeforeB = RGB_FlipFlop(RGB_Blue,Get_CenterStat(),CenterStateBeforeB);
		*/
		//prep 1.9
		//walkingLight = rolchar(walkingLight, 0);
		
		//prep 1.10 and 1.11
		//value
		if(previousSwitches != Get_SwitchPos()){
			previousSwitches = Get_SwitchPos();
			walkingLight = Get_SwitchPos();
		}
		//direction
		if(Get_LeftStat()){
			walkingLightDirection = 1;
		}
		else if(Get_RightStat()){
			walkingLightDirection = 0;
		}
		//delay
		walkingLightTimer++;
		if(walkingLightTimer >= walkingLightDelay){
			walkingLightTimer = 0;
			walkingLight = rolchar(walkingLight, walkingLightDirection);
			GPIOToggle(2,0);
		}
		//delay changer
		if(Get_UpStat() && walkingLightDelay < 10000){
			walkingLightDelay += 950;
			RGB_Off(RGB_Green);
			RGB_On(RGB_Blue);
		}
		else if(Get_DownStat() && walkingLightDelay > 500){
			walkingLightDelay -= 950;
			RGB_Off(RGB_Red);
			RGB_On(RGB_Blue);
		}
		if(walkingLightDelay >= 10000){
			RGB_Off(RGB_Blue);
			RGB_On(RGB_Red);
		}
		else if(walkingLightDelay <= 500){
			RGB_Off(RGB_Blue);
			RGB_On(RGB_Green);
		}
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

