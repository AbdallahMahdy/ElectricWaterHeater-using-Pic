#include "ADC.h"
#include<pic16f877a.h>
#include "stdtypes.h"
#include <xc.h>



void ADC_Init()
 {
   TRISAbits.TRISA2=1;
    // Select Conversion Clock FOSC/2
    ADCON0bits.ADCS0=0;
    ADCON0bits.ADCS1=1;
    ADCON1bits.ADCS2=0;
    
    //Select Channel  2
    ADCON0bits.CHS0=0;
    ADCON0bits.CHS1=1;
    ADCON0bits.CHS2=0;
  
    // Result Format Selection
    ADCON1bits.ADFM=1;//Right Justify
    
    //Port Configuration 
    ADCON1bits.PCFG0=0;
    ADCON1bits.PCFG1=0;
    ADCON1bits.PCFG2=0;
    ADCON1bits.PCFG3=0;
    //SET Status Bit 
    ADCON0bits.GO_DONE=1;
    
    //Switch On ADC
    ADCON0bits.ADON=1;
}  
unsigned short ADC_Read()
 {  
    while(ADCON0bits.GO_DONE==1);      // Wait for the conversion to complete
                                       // GO_DONE bit will be cleared once conversion is complete
    ADCON0bits.GO_DONE = 1;                          // Start ADC conversion
    return((ADRESH<<8) + ADRESL)    ;   // return right justified 10-bit result
}