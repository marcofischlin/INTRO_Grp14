/*
 * Application.c
 *
 *  Created on: Feb 25, 2014
 *      Author: tastyger
 */

#include "Platform.h"
#include "Application.h"

void APP_Run(void) {
  PL_Init();
  /* stuff here */
  LED_Test();
  
  PL_Deinit();
}
