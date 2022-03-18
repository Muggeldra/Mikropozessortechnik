#ifndef keys
#define keys

void Switch_Init(void);
unsigned char Get_SwitchPos(void);
void button_Init(void);
unsigned int Get_TA10Stat(void);
unsigned int Get_TA11Stat(void);
unsigned int Get_TA12Stat(void);

unsigned int Get_LeftStat(void);
unsigned int Get_RightStat(void);
unsigned int Get_UpStat(void);
unsigned int Get_DownStat(void);
unsigned int Get_CenterStat(void);

void Matrix_Init(void);
unsigned char Get_Mkey(void);

#endif
