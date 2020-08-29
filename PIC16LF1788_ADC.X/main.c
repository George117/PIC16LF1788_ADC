/*
 * File:   main.c
 * Author: georg
 *
 * Created on August 8, 2020, 9:48 PM
 */

#include <xc.h>
#include "bit_settings.h"
#include "config.h"
#include "adc_module.h"

#define resolution 3.339/4096

float adc_result;

void main(void) 
{
    IO_First_Init();
    Configure_Clock();    
    
    Configure_ADC_Module();
    Configure_ADC_Channel(AN0);

    while(1){
        adc_result = Get_Value_From_Channel(AN0) * resolution;
        
        LATCbits.LATC7 = 0;
        __delay_ms(1);
        LATCbits.LATC7 = 1;
        __delay_ms(1);
    }
    
    
    
}
