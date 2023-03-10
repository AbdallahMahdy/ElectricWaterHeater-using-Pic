#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pic16f877a.h>
#include "stdtypes.h"
#include "display7s.h"
#include "DIO.h"

void DisplaySevenSegment_init()
{
    TRISD=0b00000000;
}

unsigned char displaySevenSegment(unsigned char v)
{
  switch(v)
  {
    case 0:
      return 0x3F;
    case 1:
      return 0x06;
    case 2:
      return 0x5B;
    case 3:
      return 0x4F;
    case 4:
      return 0x66;
    case 5:
      return 0x6D;
    case 6:
      return 0x7D;
    case 7:
      return 0x07;
    case 8:
      return 0x7F;
    case 9:
      return 0x6F;
    default:
      return 0;
  }
}

