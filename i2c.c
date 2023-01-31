#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pic16f877a.h>
#include "stdtypes.h"
#include "display7s.h"
#include "DIO.h"
#include "Timer.h"
#include "i2c.h"
#include "HAL.h"
#include "ADC.h"
 

void Ndelay(void)
{
  #asm
     NOP
     NOP 
     NOP
     NOP
     NOP
     NOP
     NOP
     NOP
  #endasm
}

void i2c_init(void)
{
  TIDAT=0;
  ICLK=1;
  IDAT=1;
}

void i2c_start(void)
{
  ICLK=1;
  IDAT=1;
  Ndelay();
  IDAT=0;
  Ndelay();
}

void i2c_stop(void)
{
  ICLK=1;
  IDAT=0;
  Ndelay();
  IDAT=1;
  Ndelay();
}

void i2c_wb(unsigned char val)
{
  unsigned char i;
  ICLK=0;
  for(i=0;i<8;i++)
  {
    IDAT=((val>>(7-i))& 0x01);
    ICLK=1;
    Ndelay();
    ICLK=0;
  }	
  IDAT=1;
  Ndelay();
  ICLK=1;
  Ndelay();
  ICLK=0;
}

unsigned char i2c_rb(unsigned char ack)
{
  char i;
  unsigned char ret=0;

  ICLK=0;
  TIDAT=1;
  IDAT=1;
  for(i=0;i<8;i++)
  {
    ICLK=1;
    Ndelay();
    ret|=(IDAT<<(7-i));
    ICLK=0;
  }
  TIDAT=0;
  if(ack)
    IDAT=0;
  else
	IDAT=1;
  Ndelay();
  ICLK=1;
  Ndelay();
  ICLK=0;

  return ret;
}



