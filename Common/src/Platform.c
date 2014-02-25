/*
 * Platform.c
 *
 *  Created on: Feb 25, 2014
 *      Author: Röms
 */
#include "Platform.h"

#if PL_HAS_LED
#if PL_NOF_LED>=1
#include "LED1.h"
#endif
#if PL_NOF_LED>=2
#include "LED2.h"
#endif
#if PL_NOF_LED>=3
#include "LED3.h"
#endif
#if PL_NOF_LED>=4
#include "LED4.h"
#endif
#if PL_NOF_LED>=5
#include "LED5.h"
#endif
#endif

#if PL_HAS_LED
static void PL_LedInit(void) {
  /* all LED's on by default */
  #if PL_NOF_LED>=1
  LED1_On();
  #endif
  #if PL_NOF_LED>=2
  LED2_On();
  #endif
  #if PL_NOF_LED>=3
  LED3_On();
  #endif
  #if PL_NOF_LED>=4
  LED4_On();
  #endif
  #if PL_NOF_LED>=5
  LED5_On();
  #endif
}
#endif /* PL_HAS_LED */

#if PL_HAS_LED
static void PL_LedDeinit(void) {
  /* all LED's off by default */
  #if PL_NOF_LED>=1
  LED1_Off();
  #endif
  #if PL_NOF_LED>=2
  LED2_Off();
  #endif
  #if PL_NOF_LED>=3
  LED3_Off();
  #endif
  #if PL_NOF_LED>=4
  LED4_Off();
  #endif
  #if PL_NOF_LED>=5
  LED5_Off();
  #endif
}
#endif /* PL_HAS_LED */

void PL_Init(void) { 
#if PL_HAS_LED 
	LED_Init();
#endif
}

void PL_Deinit(void) { 
#if PL_HAS_LED 
	LED_Deinit();
#endif
}
