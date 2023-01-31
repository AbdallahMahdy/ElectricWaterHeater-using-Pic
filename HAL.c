#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pic16f877a.h>
#include "DIO.h"
#include "HAL.h"
#include "display7s.h"
#include "ADC.h"
#include "stdtypes.h"

#define _XTAL_FREQ 8000000
u8 UP_Switch=FALSE,Down_switch=FALSE,ChangeMode=FALSE;
volatile u8  Temp ;
u8 CurrentTemp;
u16 u16DigitalRead = 0;
u16 u16AnalogeRead = 0 ;


typedef enum Switch_Status
{
   Switch_Released = 0 ,
   Switch_Pressed
}ButtonState;

ButtonState OnOffSwitch_State   = Switch_Released ;
ButtonState UpSwitch_State      = Switch_Released ;
ButtonState DownSwitch_State    = Switch_Released ;


void Task_vidDisplayTemp(unsigned char u8Temprature)
{
        PORTAbits.RA3=1;
        PORTAbits.RA4=0;
        PORTD = displaySevenSegment( (unsigned char)(u8Temprature / (unsigned char)10)); //Most Bit
        __delay_ms(3);
        PORTAbits.RA3=0;
        PORTAbits.RA4=1;
        PORTD = displaySevenSegment( (unsigned char)(u8Temprature % (unsigned char)10)); //least bit 
        __delay_ms(2);
}
   
void Task_vidGetTemp()
{  
    u16DigitalRead = ADC_Read();
    u16AnalogeRead = (u16)((u16DigitalRead * 5.0 * 1000.0 ) / 1023.0 );//analog read 
    CurrentTemp =  (u8)( u16AnalogeRead / 10.0 )   ;  //temperature read 
 
}

void TASK_vidReadOnOffSwitch( )
{

        switch(OnOffSwitch_State) 
        {
            case  Switch_Released:
               if(PORTBbits.RB0 == STD_HIGH)
                {
                   OnOffSwitch_State = Switch_Pressed ;
                }
                break;
            case Switch_Pressed:
                if(PORTBbits.RB0 == STD_LOW)
                {
                   OnOffSwitch_State = Switch_Released;
                   ChangeMode = TRUE ;
                   
                }
                break;
            default:
                break;
        }
}

void TASK_vidReadUPDOWNSwitch( )
{

        switch(UpSwitch_State)
        {
            case  Switch_Released:
               if(PORTBbits.RB1 == STD_HIGH )
                {
                   UpSwitch_State = Switch_Pressed ;
                }
                break;
            case Switch_Pressed:
                if(PORTBbits.RB1 == STD_LOW )
                {
                   UpSwitch_State = Switch_Released;
                   UP_Switch = TRUE ;
                }
                break;
             default:
                break;
        }
        switch(DownSwitch_State)
        {
            case  Switch_Released:
               if( PORTBbits.RB2 == STD_HIGH)
                {
                   DownSwitch_State = Switch_Pressed ;
                }
                break;
            case Switch_Pressed:
                if(PORTBbits.RB2 == STD_LOW)
                {
                   DownSwitch_State = Switch_Released;
                   Down_switch = TRUE ;
                }
                break;
             default:
                break;
        }
}

void TASK_vidWaterConditioning()
{
    u8 j=0;
    u32 SumTemp[10];
    u32 AllSum  = 0;
    u32 AvgTemp = 0;
    static u8 i = 0 ;
    
  
    SumTemp[i]=CurrentTemp; // Store 10 readings between each 100 MS
    i++;
    if(i==10)
    {
        i=0;
        for(j = 0 ; j < 10 ; j++)
        {
          AllSum += SumTemp[j];  
        }
        AvgTemp =  (u32) (AllSum / 10.0); // get the Average of the 10 readings 
    
        if (AvgTemp > (Temp+5))
        {
            PORTCbits.RC2=1;
            PORTCbits.RC5=0;
            PORTBbits.RB4=1;
            PORTBbits.RB5=0;
        }
            
        else if (AvgTemp < (Temp-5))
        {
            PORTCbits.RC2=0;
            PORTCbits.RC5=1;
            PORTBbits.RB4=0;
            PORTBbits.RB5=1;      
        }
    }
}

void TASK_vidSwitchOFFALLPeripherals(void)
{
    PORTAbits.RA3=0; //seven seg off 
    PORTAbits.RA4=0; //seven seg off 
    PORTBbits.RB4=0; //led1 off 
    PORTBbits.RB5=0; //led2 off 
    PORTCbits.RC2=0; //Fan off 
    PORTCbits.RC5=0; //Heater off 
    ADCON0bits.ADON=0; //ADC off 
}