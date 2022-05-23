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
#include "i2c.h"
#include "keys.h"

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
			if(seconds >= 70){
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
	GLCD_DisplayString(5, 1, FONT_16x24, (unsigned char*)"out left:");
	GLCD_DisplayString(6, 1, FONT_16x24, (unsigned char*)"out right:");
	
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
		GLCD_DisplayString(4, 11, FONT_16x24, (unsigned char*)lcd_dez(seconds));
		GLCD_DisplayString(5, 11, FONT_16x24, (unsigned char*)lcd_hex(outLeft));
		GLCD_DisplayString(6, 11, FONT_16x24, (unsigned char*)lcd_hex(outRight));
	} // end while(1)
}	// end main()


#endif


//
//================================================================================
//  test T6_2
//================================================================================
#if (T6_2==1)

unsigned int ticks = 0;
unsigned int seconds = 0;
unsigned char SegChars[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned char sbuf[3];
int32_t ret;

int32_t out7seg(uint8_t seg1, uint8_t seg2, uint8_t seg3, uint8_t seg4){
	uint8_t tx_dat[5];
	tx_dat[0] = 0x01;
	tx_dat[1] = SegChars[seg1&0xF]|(seg1&0x80);
	tx_dat[2] = SegChars[seg2&0xF]|(seg2&0x80);
	tx_dat[3] = SegChars[seg3&0xF]|(seg3&0x80);
	tx_dat[4] = SegChars[seg4&0xF]|(seg4&0x80);
	
	return I2C1Write(0x38, tx_dat, 5);
}

void SysTick_Handler(void){
		ticks++;
	
		// seconds variable
		if(!(ticks % 100)){
			seconds++;
			if(seconds >= 60){
				seconds = 0;
			}
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
	GLCD_DisplayString(5, 1, FONT_16x24, (unsigned char*)"out bytes:");
	
	//i2c init
	I2C1_Init();sbuf[0]=0;sbuf[1]=0x17;//initialize 7 segment display, sbuf[] is to define
	ret=I2C1Write(0x38,sbuf,2); //it is only possible with connected hardware

	while(1)
	{
		out7seg((seconds/10)%10, seconds%10|0x80, 5-((seconds/10)%10), 9-(seconds%10));
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  test T6_3
//================================================================================
#if (T6_3==1)

unsigned int ticks = 0;
unsigned int seconds = 0;
unsigned char SegChars[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned char sbuf[3];
int32_t ret;
int32_t temp;

int32_t out7seg(uint8_t seg1, uint8_t seg2, uint8_t seg3, uint8_t seg4){
	uint8_t tx_dat[5];
	tx_dat[0] = 0x01;
	tx_dat[1] = SegChars[seg1&0xF]|(seg1&0x80);
	tx_dat[2] = SegChars[seg2&0xF]|(seg2&0x80);
	tx_dat[3] = SegChars[seg3&0xF]|(seg3&0x80);
	tx_dat[4] = SegChars[seg4&0xF]|(seg4&0x80);
	
	return I2C1Write(0x38, tx_dat, 5);
}

void SysTick_Handler(void){
		ticks++;
	/*
		// seconds variable
		if(!(ticks % 100)){
			seconds++;
			if(seconds >= 60){
				seconds = 0;
			}
		}*/
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
	GLCD_DisplayString(5, 1, FONT_16x24, (unsigned char*)"out bytes:");
	
	//i2c init
	I2C1_Init();sbuf[0]=0;sbuf[1]=0x17;//initialize 7 segment display, sbuf[] is to define
	ret=I2C1Write(0x38,sbuf,2); //it is only possible with connected hardware
	
	//temp sensor init
	sbuf[0]=1;sbuf[1]=0x60; ret=I2C1Write(0x48,sbuf,2);//sbuf[] is to define
	sbuf[0]=0;
	
	while(1)
	{
		if(!sbuf[0]){
			ret=I2C1Write(0x48,sbuf,1); //sbuf[] is to define
		}
		if(!ret){
			ret=I2C1Read(0x48,sbuf,2);
			if(!ret){
				temp = (((sbuf[0]<<8)|sbuf[1])>>4); // 10101010 1111----  ----xxxx xxxxxxxx
				if((temp>>11)&1){
					temp |= (0x8 << 12);
				}
				sbuf[0]=0;
			}
		}
		if(temp){
			
			temp *= 625;
			temp /= 100;
			
			out7seg((temp/1000)%10, (temp/100)%10|0x80, (temp/10)%10, temp%10);
			
			temp=0;
		}
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  test T6_4
//================================================================================
#if (T6_4==1)

unsigned char sbuf[3];
int32_t ret;

int main(void)
{	
	// LCD Init
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Maroon);
	GLCD_SetTextColor(Yellow);
	GLCD_DisplayString(0,3,FONT_16x24,(unsigned char*)"Lab microproc.");
	GLCD_DisplayString(1,2,FONT_16x24,(unsigned char*)"test2.2 switches");
	GLCD_DisplayString(2,5,FONT_16x24,(unsigned char*)"Group A.7"); //TO-DO: Set correct group
	
	GLCD_DisplayString(4, 1, FONT_16x24, (unsigned char*)"switches:");
	GLCD_DisplayString(5, 1, FONT_16x24, (unsigned char*)"address:");
	GLCD_DisplayString(6, 1, FONT_16x24, (unsigned char*)"read byte:");
	
	//i2c init
	I2C1_Init();
	
	//switch init
	Switch_Init();
	button_Init();
	
	//eeprom address
	sbuf[0] = 0x15;
	sbuf[1] = 0x55;

	while(1)
	{
		if(Get_TA12Stat()){
			//read switchpos
			sbuf[2] = Get_SwitchPos();
			//write to eeprom
			I2C1Write(0x50, sbuf, 3);
			
			//read from eeprom
			I2C1Write(0x50, sbuf, 2);
			I2C1Read(0x50, &sbuf[2], 1);
			
			//display values
			GLCD_DisplayString(4, 13, FONT_16x24, (unsigned char*)lcd_hex(Get_SwitchPos()));
			GLCD_DisplayString(5, 13, FONT_16x24, (unsigned char*)lcd_hex((sbuf[0]<<8|sbuf[1])));
			GLCD_DisplayString(6, 13, FONT_16x24, (unsigned char*)lcd_hex(sbuf[2]));
		}
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  test T6_5
//================================================================================
#if (T6_5==1)

unsigned char sbuf[4];
int32_t lux;

int main(void)
{	
	// LCD Init
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Maroon);
	GLCD_SetTextColor(Yellow);
	GLCD_DisplayString(0,3,FONT_16x24,(unsigned char*)"Lab microproc.");
	GLCD_DisplayString(1,2,FONT_16x24,(unsigned char*)"test2.2 switches");
	GLCD_DisplayString(2,5,FONT_16x24,(unsigned char*)"Group A.7"); //TO-DO: Set correct group
	
	GLCD_DisplayString(4, 1, FONT_16x24, (unsigned char*)"lux:");
	
	//i2c init
	I2C1_Init();
	
	//light sensor init
	sbuf[0] = 0x00;
	sbuf[1] = 0x80;
	I2C1Write(0x44, sbuf, 2);
	
	//set sbuf
	sbuf[0] = 0x04;
	sbuf[1] = 0x05;

	while(1)
	{
		//read from light sensor
		I2C1Write(0x44, &sbuf[0], 1);
		I2C1Read(0x44, &sbuf[2], 1);
		I2C1Write(0x44, &sbuf[1], 1);
		I2C1Read(0x44, &sbuf[3], 1);
		
		//calculate lux value
		lux = 973*((sbuf[3]<<8)|sbuf[2])/(1<<16);
		
		//display values
		GLCD_DisplayString(4, 13, FONT_16x24, (unsigned char*)lcd_dez(lux));
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

