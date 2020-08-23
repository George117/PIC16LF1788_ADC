/*
 * File:   adc_module.c
 * Author: georg
 *
 * Created on August 23, 2020, 4:26 PM
 */

#include "adc_module.h"
#include "bit_settings.h"

/* 12 bit conversion
 * TAD = 2 us 
 * Single ended
 * VREF- is connected to VSS
 * VREF+ is connected to VDD
 */
void Configure_ADC_Module(void)
{
    ADCON0bits.ADRMD = 0; // ADRESL and ADRESH provide data formatted for a 12-bit result
    
    ADCON1bits.ADFM = 0; // Sign-magnitude result format.
    
    ADCON1bits.ADCS2 = 1; // TAD 2us
    ADCON1bits.ADCS1 = 1; // FOSC/64
    ADCON1bits.ADCS0 = 0;
    
    ADCON1bits.ADNREF = 0; //VREF- is connected to VSS
    
    ADCON1bits.ADPREF1 = 0; //VREF+ is connected to VDD
    ADCON1bits.ADPREF0 = 0; 
    
    ADCON2bits.TRIGSEL = 0; // Disabled
    
    ADCON2bits.CHSN3 = 1; // ADC Negative reference ? selected by ADNREF
    ADCON2bits.CHSN2 = 1;
    ADCON2bits.CHSN1 = 1;
    ADCON2bits.CHSN0 = 1;        
            
    ADCON0bits.ADON = 1; // ADC Enable bit
}

/* AN0 as example
 */
void Configure_ADC_Channel(unsigned char channel)
{
    switch(channel){
        case(AN0):
            TRISAbits.TRISA0 = 1;
            ANSELAbits.ANSA0 = 1;
            WPUAbits.WPUA0 = 0;
            break;
 
        case(AN1):
            TRISAbits.TRISA1 = 1;
            ANSELAbits.ANSA1 = 1;
            WPUAbits.WPUA1 = 0;
            break;
            
        case(AN2):
            TRISAbits.TRISA2 = 1;
            ANSELAbits.ANSA2 = 1;
            WPUAbits.WPUA2 = 0;
            break;
            
        case(AN3):
            TRISAbits.TRISA3 = 1;
            ANSELAbits.ANSA3 = 1;
            WPUAbits.WPUA3 = 0;
            break;
            
        case(AN4):
            TRISAbits.TRISA5 = 1;
            ANSELAbits.ANSA5 = 1;
            WPUAbits.WPUA5 = 0;
            break;
            
        case(AN8):
            TRISBbits.TRISB2 = 1;
            ANSELBbits.ANSB2 = 1;
            WPUBbits.WPUB2 = 0;
            break;

        case(AN9):
            TRISBbits.TRISB3 = 1;
            ANSELBbits.ANSB3 = 1;
            WPUBbits.WPUB3 = 0;
            break;

        case(AN10):
            TRISBbits.TRISB1 = 1;
            ANSELBbits.ANSB1 = 1;
            WPUBbits.WPUB1 = 0;
            break;

        case(AN11):
            TRISBbits.TRISB4 = 1;
            ANSELBbits.ANSB4 = 1;
            WPUBbits.WPUB4 = 0;
            break;

        case(AN12):
            TRISBbits.TRISB0 = 1;
            ANSELBbits.ANSB0 = 1;
            WPUBbits.WPUB0 = 0;                
            break;

        case(AN13):
            TRISBbits.TRISB5 = 1;
            ANSELBbits.ANSB5 = 1;
            WPUBbits.WPUB5 = 0;                
            break;

        default:
            RESET();
    }
    
}


int Get_Value_From_Channel(unsigned char channel)
{
    unsigned short rez_adc = 0;
    unsigned short high_reg = 0;
    unsigned short low_reg = 0;    
    
    ADCON0bits.CHS = channel; // selected channel

    __delay_us(100); // give it some time
    
    //Start acq and wait to finish
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1){};
    
    //get the 12bit result
    high_reg = ADRESH;
    low_reg = ADRESL;
    rez_adc = ((high_reg << 8) | low_reg);
    rez_adc = rez_adc >> 4;
    
    return rez_adc;
}