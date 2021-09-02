void ADC_init(void){
       
    ADCON1bits.ADSIDL = 0;  //Continue in idle(doesn't matter)
    ADCON1bits.FORM = 0;    //set output as integer value
    ADCON1bits.SSRC = 0;    //Clearing SAMP ends sampling and starts adc
    ADCON1bits.ASAM = 0;    //sampling begins when SAMP = 1
    
    ADCON2bits.VCFG = 0;    //reference to Avss
    ADCON2bits.CSCNA = 0;   //do not scan inputs
    ADCON2bits.SMPI = 0;    //interrupt at each sample(Doesn't matter)
    ADCON2bits.BUFM = 0;    //result returned as on 16 bit number
    ADCON2bits.ALTS = 0;    //Uses MUX A as input
    
    ADCON3bits.SAMC = 0;
    ADCON3bits.ADRC = 0;    //use system clock not rc
    ADCON3bits.ADCS = 28;
    
    ADCHSbits.CH0SA = 11;    //CH0 input is AN11
    ADCHSbits.CH0NA = 0;    //Vref- is negative reference.
    
    ADPCFG = 0b000000000000;    //sets AN12 to analogue
    ADCSSL = 0;
    
    ADCON1bits.ADON = 1;    //ADC enabled
}

int ADC_read(void){
    ADCON1bits.SAMP = 1;
    __delay_ms(5);
    ADCON1bits.SAMP = 0;
    while( !ADCON1bits.DONE);
    return ADCBUF0;
}