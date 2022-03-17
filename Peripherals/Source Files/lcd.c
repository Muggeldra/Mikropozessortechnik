// includes
#include <LPC17xx.h>


// functions
char *lcd_bin (uint8_t value){
	static char text_string[9];
	unsigned char asc[] = "0123456789ABCDEF";
	text_string[0] = asc[(value >> 7)&1];
	text_string[1] = asc[(value >> 6)&1];
	text_string[2] = asc[(value >> 5)&1];
	text_string[3] = asc[(value >> 4)&1];
	text_string[4] = asc[(value >> 3)&1];
	text_string[5] = asc[(value >> 2)&1];
	text_string[6] = asc[(value >> 1)&1];
	text_string[7] = asc[(value >> 0)&1];
	text_string[8] = 0; //end of string
	return (text_string);
}

char *lcd_hex (uint16_t value){
	static char text_string[7];
	unsigned char asc[] = "0123456789ABCDEFx";
	text_string[0] = asc[0];
	text_string[1] = asc[16];
	text_string[2] = asc[((value/(16*16*16)) % 16)];
	text_string[3] = asc[((value/(16*16)) % 16)];
	text_string[4] = asc[((value/(16)) % 16)];
	text_string[5] = asc[((value/(1)) % 16)];
	text_string[6] = 0;
	return (text_string);
}

char *lcd_dez (uint16_t value){
	static char text_string[6];
	unsigned char asc[] = "0123456789ABCDEF";
	text_string[0] = asc[(value/(10000))%10];
	text_string[1] = asc[(value/(1000))%10];
	text_string[2] = asc[(value/(100))%10];
	text_string[3] = asc[(value/(10))%10];
	text_string[4] = asc[(value/(1))%10];
	text_string[5] = 0; //text_string[5] must be 0 (end0 of string)
	// sprintf (text_string,"%5u",value); //alternative use sprintf
	return (text_string);
}
