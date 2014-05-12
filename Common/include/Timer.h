/**
 * \file
 * \brief Timer driver interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the driver for the timers used in the system.
 */

#ifndef TIMER_H_
#define TIMER_H_

//#include "FreeRTOS.h"

#define TMR_TICK_MS  1 /*portTICK_RATE_MS */
  /*!< we get called every x ms */

/*! \brief Function called from timer interrupt every TMR_TICK_MS. */
void TMR_OnInterrupt(void);

/* increment a timer */
void INC_5s_Timer(void);

/* controls the 5s Timer */
bool TMR_wate_5sec(void);

/*! \brief Timer driver initialization */
void TMR_Init(void);

/*! \brief Timer driver de-initialization */
void TMR_Deinit(void);

#endif /* TIMER_H_ */
