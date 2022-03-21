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

#define RGB_Red 1
#define RGB_Green 2
#define RGB_Blue 0

//================================================================================
//  Main-Funktion Test1 T1_1
//================================================================================
#if (T1_1 == 1)


#define OUT_PORT 0
#define PORT_PIN 0

int main(void)
{		
	GLCD_Init();
	Switch_Init();
	LED_Init();
	
	GPIOSetDir(OUT_PORT, PORT_PIN, GPIO_OUTPUT);
	GPIOSetValue(OUT_PORT,PORT_PIN,PORT_PIN_LOW);
	
	while(1)
	{	
		//prep 1.6
		GLCD_Simulation();
		LED_Out(Get_SwitchPos());

	} //end while(1)
	
}	// end main()
#endif


//================================================================================
//  Main-Function Test T1_2
//================================================================================
#if (T1_2 == 1)


int main(void)
{	
	int TA12StateBefore = 0;
	int TA11StateBefore = 0;
	int TA10StateBefore = 0;
	
	GLCD_Init();
	button_Init();
	RGB_Init();
	Joystick_Init();

	while(1)
	{
		//prep 1.7
		GLCD_Simulation();
		TA12StateBefore = RGB_FlipFlop(RGB_Red,Get_TA12Stat(),TA12StateBefore);
		TA10StateBefore = RGB_FlipFlop(RGB_Green,Get_TA10Stat(),TA10StateBefore);
		TA11StateBefore = RGB_FlipFlop(RGB_Blue,Get_TA11Stat(),TA11StateBefore);
		
	} // end while(1)
}	// end main()

#endif



//================================================================================
//  Main-Function Test T1_3
//================================================================================
#if (T1_3 == 1)


int main(void)
{	
	int LeftStateBefore = 0;
	int RightStateBefore = 0;
	int UpStateBefore = 0;
	int DownStateBefore = 0;
	int CenterStateBeforeR = 0;
	int CenterStateBeforeG = 0;
	int CenterStateBeforeB = 0;
	
	GLCD_Init();
	Joystick_Init();
	LED_Init();
	RGB_Init();

	while(1)
	{
		//prep 1.8
		GLCD_Simulation();
		LeftStateBefore = LED_FlipFlop(6,Get_LeftStat(),LeftStateBefore);
		RightStateBefore = LED_FlipFlop(2,Get_RightStat(),RightStateBefore);
		UpStateBefore = LED_FlipFlop(0,Get_UpStat(),UpStateBefore);
		DownStateBefore = LED_FlipFlop(4,Get_DownStat(),DownStateBefore);
		
		CenterStateBeforeR = RGB_FlipFlop(RGB_Red,Get_CenterStat(),CenterStateBeforeR);
		CenterStateBeforeG = RGB_FlipFlop(RGB_Green,Get_CenterStat(),CenterStateBeforeG);
		CenterStateBeforeB = RGB_FlipFlop(RGB_Blue,Get_CenterStat(),CenterStateBeforeB);
		
	} // end while(1)
}	// end main()

#endif



//================================================================================
//  Main-Function TestT1_4
//================================================================================
#if (T1_4 == 1)

int main(void)
{	
	uint8_t walkingLight = 129;
	LED_Init();
	GLCD_Init();
	walkingLight = rolchar(walkingLight, 0); //0 = right //1 = left
	
	while(1)
	{
		//prep 1.9
		GLCD_Simulation();
	} // end while(1)
}	// end main()

#endif

//================================================================================
//  Main-Function Test T1_5
//================================================================================
#if (T1_5 == 1)

int main(void)
{	
	uint8_t walkingLight = 129;
	unsigned char previousSwitches = 0;
	uint32_t walkingLightDelay = 1308;
	uint32_t walkingLightTimer = 0;
	uint32_t joystickDelay = 261;
	uint32_t joystickTimer = 0;
	int walkingLightDirection = 0;
	
	GLCD_Init();
	Switch_Init();
	button_Init();
	Joystick_Init();
	LED_Init();
	RGB_Init();
	
	GPIOSetDir(2,0,GPIO_OUTPUT);
	GPIOSetValue(2,0,0);
	GPIOSetDir(2,1,GPIO_OUTPUT);
	GPIOSetValue(2,1,0);

	while(1)
	{
		//prep 1.10 and 1.11
		GLCD_Simulation();
		//value
		if(previousSwitches != Get_SwitchPos()){
			previousSwitches = Get_SwitchPos();
			walkingLight = Get_SwitchPos();
		}
		
		//delay
		walkingLightTimer++;
		if(walkingLightTimer >= walkingLightDelay){
			walkingLightTimer = 0;
			walkingLight = rolchar(walkingLight, walkingLightDirection);
			GPIOToggle(2,0);
		}
		//Joystick
		joystickTimer++;
		if(joystickTimer >= joystickDelay){
			joystickTimer = 0;
			GPIOToggle(2,1);
			//direction
			if(Get_LeftStat()){
				walkingLightDirection = 1;
			}
			else if(Get_RightStat()){
				walkingLightDirection = 0;
			}
			//delay changer
			if(Get_UpStat() && walkingLightDelay < 5000){
				walkingLightDelay += 475;
				RGB_Off(RGB_Green);
				RGB_On(RGB_Blue);
			}
			else if(Get_DownStat() && walkingLightDelay > 250){
				walkingLightDelay -= 475;
				RGB_Off(RGB_Red);
				RGB_On(RGB_Blue);
			}
			if(walkingLightDelay >= 5000){
				RGB_Off(RGB_Blue);
				RGB_On(RGB_Red);
			}
			else if(walkingLightDelay <= 250){
				RGB_Off(RGB_Blue);
				RGB_On(RGB_Green);
			}
		}
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

