#define F_OSC 20000000
#define FCY F_OSC/4

// FOSC
#pragma config FOSFPR = HS             
#pragma config FCKSMEN = CSW_FSCM_OFF

// FWDT
#pragma config FWPSB = WDTPSB_16        
#pragma config FWPSA = WDTPSA_512
#pragma config WDT = WDT_OFF

// FBORPOR
#pragma config FPWRT = PWRT_64
#pragma config BODENV = BORV20
#pragma config BOREN = PBOR_OFF
#pragma config MCLRE = MCLR_DIS

// FGS
#pragma config GWRP = GWRP_OFF
#pragma config GCP = CODE_PROT_OFF

// FICD
#pragma config ICS = ICS_PGD