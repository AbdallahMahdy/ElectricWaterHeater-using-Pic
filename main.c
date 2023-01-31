#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pic16f877a.h>
#include "stdtypes.h" //include self defined types
#include "display7s.h"
#include "DIO.h"
#include "Timer.h"
#include "i2c.h"
#include "HAL.h"
#include "ADC.h"
#include "eeprom_ext.h"




typedef enum Mode
{
   ElectricWaterHeaterOn =0 ,
   ElectricalWaterHeaterSet,
   ElectricWaterHeaterOff
}ElectricHeaterState;

ElectricHeaterState ElectricHeaterCurrentState = ElectricWaterHeaterOff;
void main(void) {
    
     //Initialize hardware Prephirals 
    ADC_Init(); // Analog to digital Converter Module Initializing 
    HW_init();   // Buttons and LEDs Pin Configurations 
    Timer0_init();  // Timer 0 Initializing
    DisplaySevenSegment_init();
    i2c_init();

    Temp = u8_ReadExternalEEPROM(10); //eeprom data retrieved
    if((Temp < 35) || (Temp > 75)) /* Check Invalid reading */ 
    {
        /* Set Default Value */
        Temp =  TEMP_DEFAULT_VALUE;
    }
     
    while(1)
    { // start infinite Loop 
        switch(ElectricHeaterCurrentState)
        {
            case ElectricWaterHeaterOn:  /* State_1*/
                TASK_vidReadOnOffSwitch( );
                TASK_vidReadUPDOWNSwitch( );
                if(ChangeMode == TRUE)
                {
                    INTCONbits.TMR0IE = 0; /*StopTimer*/  
                    TASK_vidSwitchOFFALLPeripherals();//prepare for off mode 
                    ElectricHeaterCurrentState = ElectricWaterHeaterOff ;
                    ChangeMode = FALSE; //reset flag 
                }
                else if(UP_Switch == TRUE || Down_switch == TRUE)
                {
                    ElectricHeaterCurrentState = ElectricalWaterHeaterSet ;
                    Time_out=0; //Start time counting 
                    UP_Switch = FALSE; //reset Flag 
                    Down_switch = FALSE; //reset Flag 
                }
                else 
                {
                    Task_vidGetTemp(); // Get temperature value      
                    Task_vidDisplayTemp(CurrentTemp); // display temperature   
                    if(SetTempCount>=3) //100 MS 
                    {
                        TASK_vidWaterConditioning(); //decide heater or cooler 
                        SetTempCount=0; //reset Flag 
                    }
                }
             
                break;
            case ElectricalWaterHeaterSet:  /* State_2*/
                  
                TASK_vidReadUPDOWNSwitch( );
                if ( ( UP_Switch   == TRUE  )
                &&   ( Down_switch == FALSE ) )
                {
                    if(Temp < 75)
                    {
                        Temp = Temp + (unsigned char)5;
                    }
                    else if(Temp >= (unsigned char) 75)
                    {
                        Temp = (unsigned char) 75;
                    }
                    Time_out  = 0;
                    UP_Switch = FALSE;
                }
                else if (   ( UP_Switch   ==  FALSE )
                       &&   ( Down_switch ==  TRUE  ) )
                {
                    if(Temp>35)
                    {
                        Temp=Temp - (unsigned char) 5;
                    }
                    else if(Temp<= (unsigned char) 35)
                    {
                        Temp=(unsigned char) 35;
                    }
                      
                    Time_out=0;
                    Down_switch = FALSE;
                }
                else
                {
                      
                }
                
                if (Time_out >= 137) //wait for 5 sec for the action
                  {
                    ElectricHeaterCurrentState = ElectricWaterHeaterOn;
                    Vid_WriteExternalEEPROM(10,Temp);//eeprom data store 
                    Time_out=0; //reset time flag 
                  }
               
                Task_vidDisplayTemp((unsigned char)Temp);
                Task_vidGetTemp();
                if(SetTempCount>=3) //100 MS 
                    {
                        TASK_vidWaterConditioning(); //decide heater or cooler 
                        SetTempCount=0; //reset Flag 
                    }
                

                break;
   
            case ElectricWaterHeaterOff:  /* State_3*/
                TASK_vidReadOnOffSwitch();
               
                if(ChangeMode == TRUE)
                {
                    ElectricHeaterCurrentState = ElectricWaterHeaterOn ;
                    INTCONbits.TMR0IE = 1; // turn Timer On  
                    ADCON0bits.ADON=1; //Turn ADC on 
                    /*RunTimer */
                    ChangeMode = FALSE; //Clear Flag 
                }
                TASK_vidReadOnOffSwitch(); // Read on/Off switch 
                break;
            default:
                  break;
          }
    }
}