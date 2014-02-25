/*
 * LED.c
 *
 *  Created on: Feb 25, 2014
 *      Author: Röms
 */

#include "Platform.h"
#include "LED.h"
#include "WAIT1.h"

#define LED_TEST_LED  1 
  /*!< Set to 1 if test LED function is available, 0 otherwise */

void LED_Deinit(void) {
  LED1_Deinit();
  LED2_Deinit();
  LED3_Deinit();
  LED4_Deinit();
  LED5_Deinit();
}

void LED_Init(void) {
  LED1_Init();
  LED2_Init();
  LED3_Init();
  LED4_Init();
  LED5_Init();
}

#if LED_TEST_LED
/*!
 * \brief LED test routine.
 * This routine tests if:
 * - we can turn the LEDs properly on and off
 * - if we can negate them
 * - if we can set an LED value
 * - if we can get the LED value
 * If the test fails, the program will hanging in an endless loop
 */
void LED_Test(void) {
  //bool isOn = TRUE;
  
for (;;) {
	LED1_On();
	WAIT1_Waitms(500);
	LED2_On();
	WAIT1_Waitms(500);
	LED3_On();
	WAIT1_Waitms(500);
	LED4_On();
	WAIT1_Waitms(500);
	LED5_On();
	
	LED1_Off();
	WAIT1_Waitms(500);
	LED2_Off();
	WAIT1_Waitms(500);
	LED3_Off();
	WAIT1_Waitms(500);
	LED4_Off();
	WAIT1_Waitms(500);
	LED5_Off();
	
	LED1_Neg();
	WAIT1_Waitms(500);
	LED2_Neg();
	WAIT1_Waitms(500);
	LED3_Neg();
	WAIT1_Waitms(500);
	LED4_Neg();
	WAIT1_Waitms(500);
	LED5_Neg();
}

/*  LED1_On();
  if (!LED1_Get()) {
    for(;;){};  error  ! \todo Need a dedicated error routine 
  }
  LED1_Off();
  if (LED1_Get()) {
    for(;;){};  error 
  }
  LED1_Put(isOn);
  if (!LED1_Get()) {
    for(;;){};  error 
  }*/
}
#endif
