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
#include "gpio.h"

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

	// time measuring with pin output PORT2.0
	GPIOSetDir(2, 0, 1);
	
	// test1 from script
	ADC_Init((1<<3),0); //initialize channel 3 without interrupt -
	ADC_StartCnv((1<<3), 0);
	//GPIOSetValue(2, 0, 1);

	while(1){
		if(((ADC_Stat()>>3)&1)){//wait for end of conversion
			GPIOSetValue(2, 0, 0);
			result3 = ADC_GetValue(3);	//output result3 to the LCD
			//GLCD_DisplayString(6, 13, FONT_16x24, (unsigned char*)lcd_dez(result3));
			ADC_StartCnv((1<<3), 0);
			GPIOSetValue(2, 0, 1);
		}
	}
}	// end main()

#endif

//
//================================================================================
//  Test T41_2
//================================================================================
#if (T41_2==1)

uint16_t result3 = 0, result4 = 0, result5 = 0;

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
	GLCD_DisplayString(4, 0, FONT_16x24,(unsigned char*)"Pot1 AD0.4");
	GLCD_DisplayString(5, 0, FONT_16x24,(unsigned char*)"Pot2 AD0.5");
	GLCD_DisplayString(6, 0, FONT_16x24,(unsigned char*)"LM35 AD0.3");
	
	// test1 from script
	ADC_Init((7<<3),0);
	ADC_StartCnv((1<<3), 0);
	
	while(1){
		if((ADC_Stat()>>3)&1){
			result3 = ADC_GetValue(3);
			ADC_StartCnv((1<<4), 0);
		}
		else if((ADC_Stat()>>4)&1){
			result4 = ADC_GetValue(4);
			ADC_StartCnv((1<<5), 0);
		}
		else if((ADC_Stat()>>5)&1){
			result5 = ADC_GetValue(5);
			ADC_StartCnv((1<<3), 0);
		}
		
		GLCD_DisplayString(5, 13, FONT_16x24, (unsigned char*)lcd_dez(result5));
		GLCD_DisplayString(4, 13, FONT_16x24, (unsigned char*)lcd_dez(result4));
		GLCD_DisplayString(6, 13, FONT_16x24, (unsigned char*)lcd_dez(result3));
	}
}	// end main()
#endif



//
//================================================================================
//  Test T41_3
//================================================================================
#if (T41_3==1)

uint16_t result3 = 0, result4 = 0, result5 = 0;

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
	GLCD_DisplayString(4, 0, FONT_16x24,(unsigned char*)"Pot1 AD0.4");
	GLCD_DisplayString(5, 0, FONT_16x24,(unsigned char*)"Pot2 AD0.5");
	GLCD_DisplayString(6, 0, FONT_16x24,(unsigned char*)"LM35 AD0.3");
	
	// test1 from script
	ADC_Init((7<<3),0);
	ADC_StartCnv((1<<3), 0);
	
	while(1){
		if((ADC_Stat()>>3)&1){
			result3 = ADC_GetValue(3);
			ADC_StartCnv((1<<4), 0);
		}
		else if((ADC_Stat()>>4)&1){
			result4 = ADC_GetValue(4);
			ADC_StartCnv((1<<5), 0);
		}
		else if((ADC_Stat()>>5)&1){
			result5 = ADC_GetValue(5);
			ADC_StartCnv((1<<3), 0);
		}
		
		GLCD_DisplayString(5, 14, FONT_16x24, (unsigned char*)AD_volt(result5));
		GLCD_DisplayString(4, 14, FONT_16x24, (unsigned char*)AD_volt(result4));
		GLCD_DisplayString(6, 13, FONT_16x24, (unsigned char*)TempConv(result3));
	}
}	// end main()

#endif
//
//================================================================================
//  Test T41_4
//================================================================================
#if (T41_4==1)

uint16_t adresult[8];

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
	GLCD_DisplayString(4, 0, FONT_16x24,(unsigned char*)"Pot1 AD0.4");
	GLCD_DisplayString(5, 0, FONT_16x24,(unsigned char*)"Pot2 AD0.5");
	GLCD_DisplayString(6, 0, FONT_16x24,(unsigned char*)"LM35 AD0.3");
	
	// test1 from script
	ADC_Init((7<<3), 1);
	ADC_StartCnv((7<<3), 1);
	
	while(1){
		GLCD_DisplayString(5, 14, FONT_16x24, (unsigned char*)AD_volt(adresult[5]));
		GLCD_DisplayString(4, 14, FONT_16x24, (unsigned char*)AD_volt(adresult[4]));
		GLCD_DisplayString(6, 13, FONT_16x24, (unsigned char*)TempConv(adresult[3]));
	}
} // end main()

void ADC_IRQHandler(void){
	int i;
	for(i = 0; i < 8; i++){
		if((ADC_Stat()>>i)&1){
			adresult[i] = ADC_GetValue(i);
		}
	}
}

#endif

//
//================================================================================
//  Test T41_5
//================================================================================
#if (T41_5==1)

uint16_t adresult[8];

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
	GLCD_DisplayString(4, 0, FONT_16x24,(unsigned char*)"Pot1 AD0.4");
	GLCD_DisplayString(5, 0, FONT_16x24,(unsigned char*)"Pot2 AD0.5");
	GLCD_DisplayString(6, 0, FONT_16x24,(unsigned char*)"LM35 AD0.3");
	
	
	// gpio pins for time measurements
	GPIOSetDir(2, 0, 1);
	GPIOSetDir(2, 1, 1);
	
	// test1 from script
	ADC_Init((7<<3), 1);
	ADC_StartCnv((7<<3), 1);
	
	while(1){
		GPIOToggle(2, 0);
		GLCD_DisplayString(5, 14, FONT_16x24, (unsigned char*)AD_volt(adresult[5]));
		GLCD_DisplayString(4, 14, FONT_16x24, (unsigned char*)AD_volt(adresult[4]));
		GLCD_DisplayString(6, 13, FONT_16x24, (unsigned char*)TempConv(adresult[3]));
	}
} // end main()

void ADC_IRQHandler(void){
	int i;
	GPIOSetValue(2, 1, 1);
	for(i = 0; i < 8; i++){
		if((ADC_Stat()>>i)&1){
			adresult[i] = ADC_GetValue(i);
		}
	}
	for(i=0;i<100;i++){}
	GPIOSetValue(2, 1, 0);
}

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

#include "dac.h"

#define PERIOD 200

static unsigned int ticks = 0;
unsigned int lastStart = 0, value = 0;

// systick handler
void SysTick_Handler(void){
	ticks++;
}

//main
int main(void)
{	
	// initialize systick timer
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);
	
	// Initialize LCD-Display, write headlines
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Yellow);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(0,1,FONT_16x24,(unsigned char*)"Lab microprocessor");
	GLCD_DisplayString(1,3,FONT_16x24,(unsigned char*)"test4.2.1: DAC");
	GLCD_DisplayString(2,5,FONT_16x24,(unsigned char*)"Group A.10"); //TO-DO: Set correct group

	// write data fields
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4, 0, FONT_16x24,(unsigned char*)"output:");
	GLCD_DisplayString(4, 11, FONT_16x24,(unsigned char*)"triangle");
	GLCD_DisplayString(5, 0, FONT_16x24,(unsigned char*)"period:");
	GLCD_DisplayString(5, 11, FONT_16x24,(unsigned char*)lcd_dez(PERIOD));
	GLCD_DisplayString(6, 0, FONT_16x24,(unsigned char*)"value:");

	// initialize dac
	DAC_Init();
	
	// set start variable
	lastStart = ticks;
	
	while(1){
		if(ticks - lastStart <= (PERIOD / 2)){
			value = (2 * 1023 * (ticks - lastStart)) / PERIOD;
		}
		else if(ticks - lastStart <= (PERIOD - 1)){
			value = 2046 - ((2 * (1023) * (ticks - lastStart)) / PERIOD);
		}
		else{
			lastStart = ticks;
		}
		DAC_Out(value);
		//GLCD_DisplayString(6, 11, FONT_16x24,(unsigned char*)lcd_dez(value));
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  Test T42_2
//================================================================================
#if (T42_2==1)

#include "dac.h"

#define PERIOD 200

static unsigned int ticks = 0;
unsigned int lastStart, value;

// systick handler
void SysTick_Handler(void){
	ticks++;
}

//main
int main(void)
{	
	// sin values
	uint16_t sin[90] = { /*sin[0,…,89 degree], mean-value=511*/
	511,520,529,538,547,556,564,573,582,591,
	600,609,617,626,635,643,652,660,669,677,
	686,694,702,711,719,727,735,743,751,759,
	767,774,782,789,797,804,811,819,826,833,
	839,846,853,860,866,872,879,885,891,897,
	902,908,914,919,924,930,935,940,944,949,
	954,958,962,966,970,974,978,981,985,988,
	991,994,997,1000,1002,1005,1007,1009,1011,1013,
	1014,1016,1017,1018,1019,1020,1021,1021,1022,1022};
	
	// initialize systick timer
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);
	
	// Initialize LCD-Display, write headlines
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Yellow);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(0,1,FONT_16x24,(unsigned char*)"Lab microprocessor");
	GLCD_DisplayString(1,3,FONT_16x24,(unsigned char*)"test4.2.1: DAC");
	GLCD_DisplayString(2,5,FONT_16x24,(unsigned char*)"Group A.10"); //TO-DO: Set correct group

	// write data fields
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4, 0, FONT_16x24,(unsigned char*)"output:");
	GLCD_DisplayString(4, 11, FONT_16x24,(unsigned char*)"sine");
	GLCD_DisplayString(5, 0, FONT_16x24,(unsigned char*)"period:");
	GLCD_DisplayString(5, 11, FONT_16x24,(unsigned char*)lcd_dez(PERIOD));
	GLCD_DisplayString(6, 0, FONT_16x24,(unsigned char*)"value:");

	// initialize dac
	DAC_Init();
	
	// set start variable
	lastStart = ticks;
	
	while(1){
		if(ticks - lastStart < 90){
			value = sin[ticks - lastStart];
		}
		else if(ticks - lastStart == 90){
			value = 1023;
		}
		else if(ticks - lastStart < 180){
			value = sin[180 - (ticks - lastStart)];
		}
		else if(ticks - lastStart < 270){
			value = 1023 - sin[ticks - lastStart - 180];
		}
		else if(ticks - lastStart == 270){
			value = 0;
		}
		else if(ticks - lastStart < 359){
			value = 1023 - sin[360 - (ticks - lastStart)];
		}
		else{
			lastStart = ticks;
		}
		DAC_Out(value);
		//GLCD_DisplayString(6, 11, FONT_16x24,(unsigned char*)lcd_dez(value));
	} // end while(1)
}	// end main()

#endif
