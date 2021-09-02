void UART_init(void)
{
    U2BRG = 32;
    
    U2MODEbits.UARTEN = 1;
    
    U2STAbits.UTXEN = 1;
    
}

void Write_Char(char character)//write a charachter to transmit
{
    while(!U2STAbits.TRMT);
    U2TXREG = character;
}

void Write_String(const char *string)//write a charachter to transmit
    {
    int i;
    for(i = 0;string[i]!='\0';i++)
        {
        Write_Char(string[i]);
        }
    }

char UART_RX_Ready()
{
    return U2STAbits.URXDA;
}

char Read_Char()
{
    while(!U2STAbits.URXDA);
    return U2RXREG;
}