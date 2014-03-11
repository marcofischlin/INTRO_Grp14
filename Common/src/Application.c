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

static void APP_HandleEvent(EVNT_Handle event) {
	switch(event){
					case EVNT_INIT:
						LED1_On();
						WAIT1_Waitms(100);
						LED1_Off();
						break;
					case EVNT_LED_HEARTBEAT:
						LED2_Neg();
						break;
					default:
						break;
	}
	
}

static void APP_Loop(void) {
	for(;;){
		EVNT_HandleEvent(APP_HandleEvent);
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
