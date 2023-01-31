#include "DIO.h"
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
void HW_init(void){
    
    TRISAbits.TRISA3=0;//seven seg
    TRISAbits.TRISA4=0;//seven seg
    TRISAbits.TRISA2=1; //temp sensor
    TRISBbits.TRISB0=1;//on_off button
    TRISBbits.TRISB1=1;//Up button
    TRISBbits.TRISB2=1;// Down button
    TRISBbits.TRISB4=0;//led1
    TRISBbits.TRISB6=0;
    TRISBbits.TRISB7=0;
    TRISBbits.TRISB5=0;//led2
    TRISCbits.TRISC2=0;//Fan
    TRISCbits.TRISC5=0;//Heater
    TRISCbits.TRISC3=0;//i2c sck
    TRISCbits.TRISC4=0;//i2c sDA
    PORTCbits.RC3 = 1; // set i2c initial value 
    PORTCbits.RC4 = 1; //Set i2c initial value
    PORTBbits.RB0=0;// set on/off button initial value 
    PORTBbits.RB1=0; // set up button initial value 
    PORTBbits.RB2=0; // set down button initial value 
    PORTBbits.RB4=0; //set led1
    PORTBbits.RB5=0; //set led2
    PORTBbits.RB6=0;
    PORTBbits.RB7=0;
}