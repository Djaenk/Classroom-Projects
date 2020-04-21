/******************************************************************************/
/* BLINKY.C: LED Flasher                                                      */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005-2009 Keil Software. All rights reserved.                */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/



#define LED_NUM     8                   /* Number of user LEDs                */

const long led_mask[] = { 1<<15, 1<<14, 1<<13, 1<<12, 1<<11, 1<<10, 1<<9, 1<<8 };


int main (void) {
  int AD_val, i;
  int num = -1; 
  int dir =  1;

  /* Setup GPIO for LEDs                                                      */
  RCC->APB2ENR |=  1 <<  6;             /* Enable GPIOE clock                 */
  GPIOE->CRH    = 0x33333333;           /* Configure the GPIO for LEDs        */
 
  for (;;) {                            /* Loop forever                       */

    /* Calculate 'num': 0, 1, ... , LED_NUM-1, LED_NUM-1, ... , 1, 0, 0, ...  */
    num += dir;
    if (num >= LED_NUM) { dir = -1; num = LED_NUM-1; } 
    else if   (num < 0) { dir =  1; num = 0;         }

    GPIOE->BSRR = led_mask[num];        /* Turn LED on                        */
    for (i = 0; i < ((AD_val << 8) + 100000); i++);
    GPIOE->BSRR = led_mask[num] << 16;  /* Turn LED off                       */
  }
}
