#ifndef adc
#define adc

void ADC_Init(uint8_t chsel, uint8_t intEn);	
void ADC_StartCnv(uint8_t chsel, uint8_t burst);

#endif