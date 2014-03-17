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
	switch(event){
					case EVNT_INIT:
						LED1_On();
						WAIT1_Waitms(100);
						LED1_Off();
						break;
				#if PL_HAS_LED_HEARTBEAT
					case EVNT_LED_HEARTBEAT:
						LED2_Neg();
						break;
				#endif
						
				#if PL_HAS_KBI
					case EVNT_KEY1_PRESSED:
						LED1_Neg();
						break;
					case EVNT_KEY2_PRESSED:
						LED2_Neg();
						break;
					case EVNT_KEY3_PRESSED:
						LED3_Neg();
						break;
					case EVNT_KEY4_PRESSED:
						LED4_Neg();
						break;
				#endif
						
				#if PL_HAS_KEYS && !PL_HAS_KBI
					case EVNT_KEY1_PRESSED:
						LED1_Neg();
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
	PL_Init();
	/* stuff here */
	EVNT_SetEvent(EVNT_INIT);
	APP_Loop();

	PL_Deinit();
	EVNT_Deinit();
}
