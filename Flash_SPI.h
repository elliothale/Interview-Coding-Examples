//SDO = RF3
//SDI = RF2
//SCK = RF6

/*#define RS _LATB5
#define RW _LATB6
#define EN _LATB7
#define D4 _LATB0
#define D5 _LATB1
#define D6 _LATB2
#define D7 _LATB3*/

//H,W to be held high at all times

#define CS _LATB4

/////------SPI-------///////////////////////////////////////////////////////////
void SPI_init(void)
{
    SPI1CONbits.FRMEN = 0;          //Framed SPI disabled
    SPI1CONbits.SPIFSD = 0;         //Frame Sync pulse o/p master
    SPI1CONbits.DISSDO = 0;         //SDO pin functions as SDO
    SPI1CONbits.MODE16 = 0;         //byte wide communication (8-bit)
    SPI1CONbits.SMP = 1;            //Input data sampled at end of data output
    SPI1CONbits.CKE = 0;            //Output data changes on idle to active
    SPI1CONbits.SSEN = 0;           //Slave select unused (Module is master)
    SPI1CONbits.CKP = 1;            //Idle low, active high
    SPI1CONbits.MSTEN = 1;          //Master mode
    SPI1CONbits.SPRE = 0b111;       //111 = 1:1     000 = 1:8
    SPI1CONbits.PPRE = 0b00;        //11 = 1:1      00 = 64:1
    
    SPI1STATbits.SPIROV = 0;        //Clears overflow "interrupt"
    SPI1STATbits.SPIEN = 1;         //Enables SPI
    
    CS = 1;
}

static void SPI_wait()
{
    while(!SPI1STATbits.SPIRBF); //SPIRBF goes high once tx then rx is complete
}

void SPI_write(unsigned char byte)
{
    int temp;               //Used to store irrelevant data that must be read
    SPI1BUF = byte;         //write data to the output buffer, begins tx
    SPI_wait();             //Waits for process to complete
    temp = SPI1BUF;          //reads SPI1BUF to clear SPIRBF and end process
}

void SPI_Write_String(const unsigned char *string)
{
    int i;
    for(i = 0;string[i] == '\0'; i++)
    {SPI_write(string[i]);
    }
}

/*unsigned SPI_Ready()
{
    if(BF)
    {   return 1;   }
    else
    {   return 0;   }
}*/

unsigned char SPI_read()
{
    SPI1BUF = 0;                //Dummy byte to begin clock cycles
    SPI_wait();                 //Waits for process to finish
    return(SPI1BUF);            //returns received data
}
/////------EEPROM-------////////////////////////////////////////////////////////
enum Command
{
    READ =  0b00000011,
    WRITE = 0b00000010,
    WRDI =  0b00000100,
    WREN =  0b00000110,
    RSDR =  0b00000101,
    WRSR =  0b00000001,
    CE = 0b11000111,
    DP = 0b10111001,
    RES = 0b10101011
};


int EEPROM_busy(void)
{
    char status;
    CS = 0;
    SPI_write(RSDR);
    status = SPI_read();
    CS = 1;
    return (status & 0x01);
}

void Send_byte(unsigned long address, char data)
{
    LCD_xy(1,4);
    LCD_string("busy                ");
    char address1 = (address>>16) & 0xff;
    char address2 = (address>>8) & 0xff;
    char address3 = address & 0xff;
    CS = 0;             
    SPI_write(WREN);    
    CS = 1; 
    
    CS = 0;
    SPI_write(RSDR);
    while(!(SPI_read() & 0b00000010))
    {
     __builtin_nop();   
    }
    CS = 1;
    
    CS = 0;
    SPI_write(WRITE);
    SPI_write(address1);
    SPI_write(address2);
    SPI_write(address3);
    SPI_write(data);
    CS = 1;
    
    while(EEPROM_busy());
    LCD_xy(1,4);
    LCD_string("free                ");
}

char Read_byte(unsigned long address)
{
    char byte;
    char address1 = (address>>16) & 0xff;
    char address2 = (address>>8) & 0xff;
    char address3 = address & 0xff;
    CS = 0;
    SPI_write(READ);
    SPI_write(address1);
    SPI_write(address2);
    SPI_write(address3);
    byte = SPI_read();
    //SPI_write(0x00);
    CS = 1;
    return byte;
}

void EE_Write(char address, char data)
{
    //Write enable
    CS = 0;             
    SPI_write(WREN);    
    CS = 1; 
    //__delay_us(1);//Check write is enabled
    CS = 0;
    SPI_write(RSDR);
    while(!(SPI_read() & 0b00000010));
    CS = 1;
    //__delay_us(1);//Write data to address
    CS = 0;
    SPI_write(WRITE);
    SPI_write(address);
    SPI_write(data);
    CS = 1;
    //__delay_us(1);
    while(EEPROM_busy());
}

char EE_Read(int address)
{
    char byte;
    CS = 0;
    SPI_write(READ);
    SPI_write(address);
    byte = SPI_read();
    SPI_write(0x00);
    CS = 1;
    return byte;
}