// includes
#include <LPC17xx.h>
#include "gpio.h"
#include <stdio.h>
#include <time.h>

// functions
char *lcd_bin (uint8_t value){
	static char text_string[9];
	unsigned char asc[] = "0123456789ABCDEF";
	int i;
	
	// values
	for(i = 0; i < 8; i++){
		text_string[i] = asc[(value >> (7-i))&1];
	}
	
	// end of string
	text_string[8] = 0;
	
	return (text_string);
}

char *lcd_hex (uint16_t value){
	static char text_string[7];
	unsigned char asc[] = "0123456789ABCDEFx";
	int i;
	
	// time measurements
	/*GPIOSetDir(2, 0, 1);
	GPIOSetDir(2, 1, 1);
	
	GPIOSetValue(2, 0, 1);*/
	
	// 0x
	text_string[0] = asc[0];
	text_string[1] = asc[16];
	
	// values
	for(i = 0; i < 4; i++){
		text_string[2 + i] = asc[(value >> (12 - (4 * i))) & 0xF];
	}
	
	// end of string
	text_string[6] = 0;
	
	// time measurements
	/*GPIOSetValue(2, 0, 0);
	GPIOSetValue(2, 1, 1);
	sprintf(text_string,"%5u",value); //alternative use sprintf
	GPIOSetValue(2, 1, 0);*/
	
	return (text_string);
}

char *lcd_dez (uint16_t value){
	static char text_string[6];
	unsigned char asc[] = "0123456789ABCDEF";
	GPIOSetDir(2, 0, 1);
	GPIOSetDir(2, 1, 1);
	
	GPIOSetValue(2, 0, 1);
	text_string[0] = asc[(value/(10000))%10];
	text_string[1] = asc[(value/(1000))%10];
	text_string[2] = asc[(value/(100))%10];
	text_string[3] = asc[(value/(10))%10];
	text_string[4] = asc[(value/(1))%10];
	text_string[5] = 0;	//text_string[5] must be 0 (end0 of string)
	
	GPIOSetValue(2, 0, 0);
	GPIOSetValue(2, 1, 1);
	//sprintf(text_string,"%5u",value); //alternative use sprintf
	//GPIOSetValue(2, 1, 0);
	return (text_string);
}

char *lcd_time (uint32_t value){
		static char text_string[8];
    struct tm  ts;
    char       buf[80];

    // Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
    ts = *localtime(&value);
    strftime(buf, sizeof(buf), "%H:%M:%S", &ts);
	  sprintf(text_string,"%s",buf);
	
	return (text_string);
}

char *AD_volt(unsigned short val){
	static char text_string[6];
	unsigned char asc[] = "0123456789.V";
	val = (val * 3300) / 4095;
	text_string[0] = asc[(val/1000)%10];
	text_string[1] = asc[10];
	text_string[2] = asc[(val/100)%10];
	text_string[3] = asc[(val/10)%10];
	text_string[4] = asc[11];
	text_string[5] = 0;
	return (text_string);
}

char *TempConv(unsigned short val){
	static char text_string[7];
	unsigned char asc[] = "0123456789.C";
	val = (val * 3300) / 4095;
	text_string[0] = asc[(val/1000)%10];
	text_string[1] = asc[(val/100)%10];
	text_string[2] = asc[10];
	text_string[3] = asc[(val/10)%10];
	text_string[4] = asc[(val/1)%10];
	text_string[5] = asc[12];
	text_string[6] = 0;
	return (text_string);
}
