#include "Timer.h"
#include "xc.h"
#include "pic16f877a.h"
#include "ADC.h"
#include "HAL.h"
#include "stdtypes.h"
volatile u32 SetTempCount=0;
u32 Time_out = 0;


void interrupt ISR()
{

    if(INTCONbits.TMR0IF == 1)
    {
        INTCONbits.TMR0IF = 0;       // Clear timer interrupt flag
        SetTempCount ++;
        Time_out ++;
    }
}

void Timer0_init(void){
    // enable the glabal interrupt
    INTCONbits.GIE =1;
    // enable the prephiral interrupt
    INTCONbits.PEIE = 1;
    // ebable timer 0 interrupt 
    INTCONbits.TMR0IE   = 1;
    INTCONbits.TMR0IF   = 0; // clear timer 0 over flow flag 
    OPTION_REGbits.T0CS = 0;// use internal instruction cycle clock
    OPTION_REGbits.T0SE = 0;//edge selection
    OPTION_REGbits.PSA  = 0;//prescale assined to timer 0
    // Set pre scale as 1:256
    OPTION_REGbits.PS0  = 1;
    OPTION_REGbits.PS1  = 1;
    OPTION_REGbits.PS2  = 1;
}


