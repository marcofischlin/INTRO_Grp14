/*
 * Timer.c
 *
 *  Created on: Mar 11, 2014
 *      Author: Marco
 */

#include "Platform.h"
#if PL_HAS_TIMER
#include "Timer.h"
#if PL_HAS_EVENTS
  #include "Event.h"
#endif
#if PL_HAS_TRIGGER
  #include "Trigger.h"
#endif
#if PL_HAS_QUADRATURE
  #include "Q4CLeft.h"
  #include "Q4CRight.h"
#endif
#if PL_HAS_MOTOR_TACHO
  #include "Tacho.h"
#endif
#if PL_HAS_BUZZER
  #include "Buzzer.h"
#endif

void TMR_OnInterrupt(void) {
  /* this one gets called from an interrupt!!!! */
#if PL_HAS_LED_HEARTBEAT
  /* timer interrupt is calling us every TMR_TICK_MS ms */
  static uint16_t cnt = 0; /* using static local variable */

  cnt++;
  if (cnt==1000/TMR_TICK_MS) { /* every second */
    /* using event method */
    EVNT_SetEvent(EVNT_LED_HEARTBEAT);
    cnt = 0; /* reset counter */
  }
#endif
#if PL_HAS_TRIGGER
  TRG_IncTick();
#endif
#if PL_HAS_QUADRATURE
  Q4CLeft_Sample();
  Q4CRight_Sample();
#endif
#if PL_HAS_MOTOR_TACHO
  TACHO_Sample();
#endif
  
  INC_5s_Timer();
}

uint16_t value = 0;
bool trigger;
void INC_5s_Timer(void)
{
	if(trigger)
	{
		value++;
	}

}

bool TMR_wate_200ms(void)
{
	if (value >= 400)
	{
		BUZ_Beep(1000, 400);
		value = 0;
		trigger = 0;
		return 1;
	}
	else
	{
		trigger = 1;
	}
	return 0;
		
}

bool TMR_wate_5sec(void)
{
	
	if (value >= 5000)
	{
		BUZ_Beep(1000, 400);
		value = 0;
		trigger = 0;
		return 1;
	}
	else if(value >= 4000 && value <=4050)
	{
		BUZ_Beep(1000, 400);
	}
	else if(value >= 3000 && value <=3050)
	{
		BUZ_Beep(1000, 400);
	}
	else if(value >= 2000 && value <=2050)
	{
		BUZ_Beep(1000, 400);
	}
	else
	{
		trigger = 1;
	}
	return 0;
	
}

/*! \brief Timer driver initialization */
void TMR_Init(void) {
  /* nothing needed right now */
}

/*! \brief Timer driver de-initialization */
void TMR_Deinit(void) {
  /* nothing needed right now */
}

#endif
