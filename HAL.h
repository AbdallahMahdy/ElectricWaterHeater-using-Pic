#ifndef _modes_h
#define _modes_h
#define STD_LOW     (0u)
#define STD_HIGH    (1u)
#define TRUE        (1u)
#define FALSE       (0u)
#include "stdtypes.h"
   

extern u8 UP_Switch,Down_switch ,ChangeMode;
extern volatile u8 Temp ;
extern u8 CurrentTemp;

extern void Task_vidDisplayTemp(unsigned char u8Temprature);
extern void Task_vidGetTemp(void);
extern void TASK_vidReadOnOffSwitch(void);
extern void TASK_vidReadUPDOWNSwitch(void);
extern void TASK_vidWaterConditioning(void);
extern void TASK_vidSwitchOFFALLPeripherals(void);
#endif