/*
 * Application.c
 *
 *  Created on: Feb 25, 2014
 *      Author: tastyger
 */

#include "Platform.h"
#include "Application.h"
#include "Event.h"
#include "WAIT1.h"
#include "LED.h"
#include "Keys.h"

static void APP_HandleEvent(EVNT_Handle event) {
	  switch(event) { 
	    case EVNT_INIT:
	      LED1_On();
	      WAIT1_Waitms(100);
	      LED1_Off();
	      break;

	#if PL_HAS_LED_HEARTBEAT
	    case EVNT_LED_HEARTBEAT:
	      LED3_Neg();
	      break;
	#endif
	#if PL_NOF_KEYS>=1
	  case EVNT_SW1_PRESSED:
	    LED1_Neg();
	    BUZ_Beep(20,1000);
	    break;
	#endif
	#if PL_NOF_KEYS>=2
	  case EVNT_SW2_PRESSED:
	    LED2_Neg();
	    break;
	#endif
	#if PL_NOF_KEYS>=3
	  case EVNT_SW3_PRESSED:
	    LED3_Neg();
	    break;
	#endif
	#if PL_NOF_KEYS>=4
	  case EVNT_SW4_PRESSED:
	    LED4_Neg();
	    break;
	#endif

	    default:
	      break;
	  }
	}


static void APP_Loop(void) {
	for(;;){
		EVNT_HandleEvent(APP_HandleEvent);
	#if (PL_HAS_KEYS && !(PL_HAS_KBI))
		PL_POLL_KEYS();
	#endif
	}
}


void APP_Run(void) {
	EVNT_Init();
	//PL_LedInit();
	PL_Init();
	BUZ_Init();
	/* stuff here */
	EVNT_SetEvent(EVNT_INIT);
	APP_Loop();
	
	BUZ_Deinit();
	PL_Deinit();
	//PL_LedDeinit();
	EVNT_Deinit();
}
