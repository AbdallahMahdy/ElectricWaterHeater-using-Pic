
#include "i2c.h"
#include"eeprom_ext.h"

unsigned char u8_ReadExternalEEPROM(unsigned int addr)
{
  unsigned char ret;
  unsigned char ah;
  unsigned char al;

  ah=(addr&0x0100)>>8;
  al=addr&0x00FF;

  i2c_start();	
  if(ah)
  {
    i2c_wb(0xA2);
  }
  else
  {
    i2c_wb(0xA0);
  }
  i2c_wb(al);

  i2c_start();
  if(ah)
  {
    i2c_wb(0xA3);
  }
  else
  {
    i2c_wb(0xA1);
  }
  ret=i2c_rb(1);
  i2c_stop();

  return ret;	
}


void Vid_WriteExternalEEPROM(unsigned int addr, unsigned char val)
{
  unsigned int tmp;
  unsigned char ah;
  unsigned char al;
  unsigned char nt;

  tmp=val;
  ah=(addr&0x0100)>>8;
  al=addr&0x00FF;
  nt=0;

  do
  {
    i2c_start();
    if(ah)
    { 
      i2c_wb(0xA2);
    }
    else
    {
      i2c_wb(0xA0);
    }
    i2c_wb(al);
    i2c_wb(tmp);
    i2c_stop();

    nt++;
  }
  while((tmp != u8_ReadExternalEEPROM(addr))&&(nt < 10));
}
