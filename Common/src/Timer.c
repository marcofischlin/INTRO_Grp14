/*
 * Timer.c
 *
 *  Created on: Mar 11, 2014
 *      Author: Marco
 */


#include "Platform.h"
#if PL_HAS_TIMER
#include "Timer.h" /* own interface */
#include "Event.h"


/* Event on Timer Interrupt */
void TMR_OnInterrupt(void){
	static int cnt = 0;
#if PL_HAS_LED_HEARTBEAT
	if (cnt == 1000) {
		EVNT_SetEvent(EVNT_LED_HEARTBEAT);
		cnt = 0;
	} else {
		cnt += TMR_TICK_MS;
	}
#endif
}


#endif
