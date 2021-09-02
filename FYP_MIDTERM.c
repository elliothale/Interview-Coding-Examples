#include <xc.h>
#include "dsPIC_Config.h"
#include <libpic30.h>
#include <stdio.h>
#include <stdbool.h>
#include "LCD_Functions.h"
#include "ADC_functions.h"
#include "UART_functions.h"
#include "Flash_SPI.h"

char value[21];
char UART_str[30];

#define UP_con _LATB8
#define DOWN_con _LATC14
#define FP_con _LATC13


#define OK PORTDbits.RD0
#define INCREMENT PORTDbits.RD1
#define LEFT PORTDbits.RD2
#define RIGHT PORTDbits.RD3
#define UP_BUTTON PORTDbits.RD8
#define DOWN_BUTTON PORTDbits.RD9

//#define DOWN_SAFE PORTBbits.RB12

unsigned int DS_Flag = 0;
unsigned int US_Flag = 0;
unsigned int ES_Flag = 0;

unsigned char Cycle_bits[6] = {0,0,0,0,0,0};
unsigned char UP_bits[3] = {0,0,0};
unsigned char DOWN_bits[3] = {0,0,0};
unsigned char REST_bits[3] = {0,0,0};
unsigned long Cycles = 0;
unsigned long Cycles_complete = 0;
unsigned int UP_time = 0;
unsigned int DOWN_time = 0;
unsigned int REST_time = 0;

unsigned static int FP_time = 7;
unsigned int Cursor_Position = 1;
unsigned int startMode = 0;

unsigned long address = 3;
unsigned char address_lsb = 0;
unsigned char address_nsb = 0;
unsigned char address_msb = 0;
unsigned long data = 0;

unsigned char vbatt_start_MSB = 0;
unsigned char vbatt_middle_MSB = 0;
unsigned char vbatt_end_MSB = 0;
unsigned char vbatt_start_LSB = 0;
unsigned char vbatt_middle_LSB = 0;
unsigned char vbatt_end_LSB = 0;

unsigned int vbatt_start = 0;
unsigned int vbatt_middle = 0;
unsigned int vbatt_end = 0;
bool FP_ON = false;
bool Complete = false;
bool UP = false;
bool DOWN = false;
#include "Setup_Functions.h"
void delay_seconds(int time);
void delay_minutes(int mins);
void INT0_INIT(void);

//////////////////////////////////////////////////////////

void main(void) {
    TRISD = 1;
    PORTD = 0;
    TRISA = 1;
    PORTA = 0;
    TRISCbits.TRISC13 = 0;
    TRISCbits.TRISC14 = 0;
    PORTC = 0;
    LCD_init();
    ADC_init();
    SPI_init();
    address_msb = Read_byte(0);
    address_nsb = Read_byte(1);
    address_lsb = Read_byte(2);
    data = address_msb<<8;
    data = data | address_nsb;
    data = data<<8;
    data = data | address_lsb;
    
    LCD_xy(1,1);
    LCD_string("Select Operation");
    LCD_xy(1,2);
    LCD_string("Start new test  <<");
    LCD_xy(1,3);
    LCD_string("Transfer data     ");
    LCD_xy(1,4);
    sprintf(value,"%ld",data);
    LCD_string(value);

    while(!OK)
    {
        if(UP_BUTTON)
        {
            LCD_xy(1,2);
            LCD_string("Start new test  <<");
            LCD_xy(1,3);
            LCD_string("Transfer data     ");
            startMode = 0;
        }
        else if(DOWN_BUTTON)
        {
            LCD_xy(1,2);
            LCD_string("Start new test    ");
            LCD_xy(1,3);
            LCD_string("Transfer data   <<");
            startMode = 1;
        }
    }
    while(OK)
    {
        __delay_ms(25);
    }

    if(startMode) //data transfer mode
    {
        int i = 0;
        UART_init();
        Write_String("Cycle\tV(start)\tV(middle)\tV(end)\n");
        for(i = 0;i < data;i++)
        {
            vbatt_start_MSB = Read_byte(address);
            address++;
            vbatt_start_LSB = Read_byte(address);
            address++;
            vbatt_start = vbatt_start_MSB<<8;
            vbatt_start = vbatt_start | vbatt_start_LSB;
            
            vbatt_middle_MSB = Read_byte(address);
            address++;
            vbatt_middle_LSB = Read_byte(address);
            address++;
            vbatt_middle = vbatt_middle_MSB<<8;
            vbatt_middle = vbatt_middle | vbatt_middle_LSB;
            
            vbatt_end_MSB = Read_byte(address);
            address++;
            vbatt_end_LSB = Read_byte(address);
            address++;
            vbatt_end = vbatt_end_MSB<<8;
            vbatt_end = vbatt_end | vbatt_end_LSB;
            
            US_Flag = Read_byte(address);
            address++;
            
            DS_Flag = Read_byte(address);
            address++;
            
            ES_Flag = Read_byte(address);
            address++;
            
            sprintf(UART_str,"%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i,vbatt_start,vbatt_middle,vbatt_end,US_Flag,DS_Flag,ES_Flag);
            Write_String(UART_str);
        }
        LCD_command(DISP_CL);
        __delay_ms(2);
        LCD_xy(1,1);
        LCD_string("data transferred");
        while(1)
        {
            __builtin_nop();
        }
    }

    //test mode 

    Get_Values();
    Get_Footplate();
    Confirm_Settings();
    CS = 0;             
    SPI_write(WREN);    
    CS = 1; 
    CS = 0;             
    SPI_write(CE);    
    CS = 1;
    INT0_INIT();
    
    LCD_command(DISP_CL);
    __delay_ms(2);
    LCD_xy(1,1);
    LCD_string("Test in Progress\0");
    sprintf(value,"Cycle#%8ld",Cycles_complete);
    LCD_xy(1,2);
    LCD_string(value);
    __delay_ms(1000);
    while(Complete == false)
    {
        vbatt_start = ADC_read();
        UP_con = 1;
        delay_seconds(UP_time);
        UP_con = 0;

        if(FP_ON)
        {
            FP_con = 1;
            delay_seconds(FP_time);
            FP_con = 0;
            delay_seconds(FP_time);
        }
        vbatt_middle = ADC_read();
        
        DOWN_con = 1;
        delay_seconds(DOWN_time);
        DOWN_con = 0;
        vbatt_end = ADC_read();
        
        Cycles_complete++;
        sprintf(value,"%8ld Cycles",Cycles_complete);
        LCD_xy(1,2);
        LCD_string(value);
        sprintf(value,"%d %d %d %d %d", vbatt_start,vbatt_middle,vbatt_end,DS_Flag,US_Flag);
        LCD_xy(1,3);
        LCD_string(value);
        
        vbatt_start_MSB = vbatt_start>>8;
        vbatt_start_LSB = vbatt_start & 0b11111111;
        
        vbatt_middle_MSB = vbatt_middle>>8;
        vbatt_middle_LSB = vbatt_middle & 0b11111111;
        
        vbatt_end_MSB = vbatt_end>>8;
        vbatt_end_LSB = vbatt_end & 0b11111111;
        
        Send_byte(address,vbatt_start_MSB);
        address++;
        Send_byte(address,vbatt_start_LSB);
        address++;
        
        Send_byte(address,vbatt_middle_MSB);
        address++;
        Send_byte(address,vbatt_middle_LSB);
        address++;
        
        Send_byte(address,vbatt_end_MSB);
        address++;
        Send_byte(address,vbatt_end_LSB);
        address++;
        
        Send_byte(address,US_Flag);
        address++;
        
        Send_byte(address,DS_Flag);
        address++;
        
        Send_byte(address,ES_Flag);
        address++;
        
        
        /*vbatt_middle = vbatt_middle/16;
        vbatt_end = vbatt_end/16;
        
        Send_byte(address,vbatt_middle);
        address++;
        Send_byte(address,vbatt_end);
        address++;*/
        
        if(Cycles_complete == Cycles)
        {
            Complete = true;
            address_msb = Cycles_complete>>16;
            address_nsb = (Cycles_complete>>8) & 0b11111111;
            address_lsb = Cycles_complete & 0b11111111;
            Send_byte(0,address_msb);
            Send_byte(1,address_nsb);
            Send_byte(2,address_lsb);
        }
        else
        {
            //delay_minutes(REST_time);)
            //Send_byte(0,Cycles_complete);
            delay_seconds(REST_time);
            DS_Flag = 0;
            US_Flag = 0;
        }  
    }
    sprintf(value,"%-6ld cycles",Cycles_complete);
    LCD_command(DISP_CL);
    __delay_ms(2);
    LCD_xy(1,1);
    LCD_string("Test finished at\0");
    LCD_xy(1,2);
    LCD_string(value);
    while(1){
        __builtin_nop();
    }
    
    
}

void delay_seconds(int time){
    int i = 0;
    for(i = 0;i<time;i++)
    {
        ADCHSbits.CH0SA = 12;
        if(ADC_read() < 1500)
        {
            US_Flag = 1;
        }
        ADCHSbits.CH0SA = 10;
        if(ADC_read() < 1500)
        {
            DS_Flag = 1;
        }
        ADCHSbits.CH0SA = 9;
        if(ADC_read() < 1500)
        {
            ES_Flag = 1;
        }
        ADCHSbits.CH0SA = 11;
        __delay_ms(1000);
    }
}

void delay_minutes(int mins){
    int i = 0;
    for(i = 0;i<mins;i++)
    {
        delay_seconds(60);
    }
}

void INT0_INIT(void)
{
    INTCON2bits.INT0EP = 1;
    IPC0bits.INT0IP = 0x01;
    IFS0bits.INT0IF = 0;
    IEC0bits.INT0IE = 1;
}

void __attribute__((interrupt, no_auto_psv)) _INT0Interrupt(void)
{
    IEC0bits.INT0IE = 0;
    if(UP_con == 1){UP = true;}
    else if(DOWN_con == 1){DOWN = true;}
    UP_con = 0;
    DOWN_con = 0;
    LCD_command(DISP_CL);
    __delay_ms(2);
    LCD_xy(1,1);
    __delay_ms(2);
    LCD_string("Paused, press OK to");
    LCD_xy(1,2);
    LCD_string("resume test at");
    sprintf(value,"%ld Cycles",Cycles_complete);
    LCD_xy(1,3);
    __delay_ms(2);
    LCD_string(value);
    while(OK == 0){
        __builtin_nop();
    }
    LCD_command(DISP_CL);
    __delay_ms(2000);
    LCD_string("Test in Progress\0");
    sprintf(value,"Cycle#%8ld",Cycles_complete);
    LCD_xy(1,2);
    LCD_string(value);
    if(UP == true){
        UP_con = 1;
        __delay_ms(3000);
    }
    else if(DOWN == true){
        DOWN_con = 1;
        __delay_ms(3000);
    }
    DOWN = false;
    UP = false;
    
    IFS0bits.INT0IF = 0;
    IEC0bits.INT0IE = 1;
}

