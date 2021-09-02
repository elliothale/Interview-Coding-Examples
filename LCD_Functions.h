#define	DISP_FS		0x3f  	//Function set
#define FOUR_FS     0x28
#define	DISP_ON		0x0c  	//Display on w/o blink or flash
#define	DISP_OFF	0x08  	//Display, blink, cursor off 
#define	DISP_CL		0x01  	//Clear display 
#define	DISP_EN 	0x06  	//Data entry mode 
#define	LINE_1		0x80	//DDRAM address for first line 
#define	LINE_2		0xc0	//DDRAM address for second line 
#define LINE_3      0x94    //DDRAM address for third line
#define LINE_4      0xd4    //DDRAM address for fourth line
#define	SH_LFT		0x18	//Left-shift display 
#define	SH_RT		0x1c 	//Right-shift display 
#define	HOME		0x02  	//Return home

#define RS _LATB5
#define RW _LATB6
#define EN _LATB7
#define D4 _LATB0
#define D5 _LATB1
#define D6 _LATB2
#define D7 _LATB3

void LCD_nibble(char nibble)
{
    if(nibble & 1)
    {   D4 = 1; }
    else{ D4 = 0;    }
    
    if(nibble & 2)
    {   D5 = 1; }
    else{ D5 = 0;    }
    
    if(nibble & 4)
    {   D6 = 1; }
    else{ D6 = 0;    }
    
    if(nibble & 8)
    {   D7 = 1; }
    else{ D7 = 0;    }
}

void LCD_command(char command)
{
    char MSB,LSB;
    LSB = command & 0x0f;
    MSB = command & 0xf0;
    RS = 0;
    LCD_nibble(MSB>>4);
    EN = 1;
    __delay_us(40);
    EN = 0;
    LCD_nibble(LSB);
    EN = 1;
    __delay_us(40);
    EN = 0;
    //__delay_ms(2);
}

void LCD_char(char ch)
{
    char MSB,LSB;
    LSB = ch & 0x0f;
    MSB = ch & 0xf0;
    RS = 1;
    LCD_nibble(MSB>>4);
    EN = 1;
    __delay_us(40);
    EN = 0;
    LCD_nibble(LSB);
    EN = 1;
    __delay_us(40);
    EN = 0;
}

void LCD_string(const char *string)
{
    int i;
    for(i = 0; string[i]!='\0';i++)
    {
        LCD_char(string[i]);
    }
}

void LCD_init(void)
{
    TRISB = 0b1111000000000;
    PORTB = 0x00;
    __delay_ms(20);
    LCD_nibble(0x03);   EN =1;__delay_us(40);EN=0;
    __delay_ms(10);
    LCD_nibble(0x03);   EN =1;__delay_us(40);EN=0;
    __delay_ms(1);
    LCD_nibble(0x03);   EN =1;__delay_us(40);EN=0;
    __delay_ms(1);
    LCD_nibble(0x02);   EN =1;__delay_us(40);EN=0;__builtin_nop();
    //////////////////////////////////
    LCD_command(FOUR_FS);
    __delay_ms(1);
    LCD_command(DISP_ON);
    __delay_us(40);
    LCD_command(DISP_EN);
    __delay_us(40);
    LCD_command(DISP_CL);
    __delay_ms(2);
}

void LCD_xy(int x, int y)
{
    char MSB,LSB,PLACE;
    if(y == 1)
    {
        PLACE = LINE_1 + x - 1;
        LSB = PLACE & 0x0f;
        MSB = PLACE & 0xf0;
        RS = 0;     
        LCD_nibble(MSB>>4);     EN =1;__delay_us(40);EN=0;
        LCD_nibble(LSB);        EN =1;__delay_us(40);EN=0;
    }
    else if(y == 2)
    {
        PLACE = LINE_2 + x - 1;
        LSB = PLACE & 0x0f;
        MSB = PLACE & 0xf0;
        RS = 0;
        LCD_nibble(MSB>>4);     EN =1;__delay_us(40);EN=0;
        LCD_nibble(LSB);        EN =1;__delay_us(40);EN=0;
    }
    else if(y == 3)
    {
        PLACE = LINE_3 + x - 1;
        LSB = PLACE & 0x0f;
        MSB = PLACE & 0xf0;
        RS = 0;     
        LCD_nibble(MSB>>4);     EN =1;__delay_us(40);EN=0;
        LCD_nibble(LSB);        EN =1;__delay_us(40);EN=0;
    }
    else if(y == 4)
    {
        PLACE = LINE_4 + x - 1;
        LSB = PLACE & 0x0f;
        MSB = PLACE & 0xf0;
        RS = 0;
        LCD_nibble(MSB>>4);     EN =1;__delay_us(40);EN=0;
        LCD_nibble(LSB);        EN =1;__delay_us(40);EN=0;
    }
    //__delay_ms(2)
}