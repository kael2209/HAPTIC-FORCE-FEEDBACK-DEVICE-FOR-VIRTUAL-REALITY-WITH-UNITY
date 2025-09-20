#include "stm32f4xx.h"
#define __FILE_INCOMPLETE 1
#include <stdio.h>
#include <stdint.h>

struct __FILE
{
  int handle;
};
FILE __stdout;
int fputc(int ch, FILE *f)
{
  while (!(USART2->SR & (1<<6))); 
  USART2->DR = (char)(ch);
  return ch;
}

#include "encoder.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>
#include "var.h"
#include "hbridge.h"
#include "sample_time.h"
#include "calculation.h"
#include "adc.h"
#include <math.h>