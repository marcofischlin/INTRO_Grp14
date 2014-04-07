/*
 * Application.c
 *
 *  Created on: Feb 25, 2014
 *      Author: tastyger
 */

#include "Platform.h"
#include "Application.h"
#include "WAIT1.h"
#if PL_HAS_EVENTS
  #include "Event.h"
#endif
#if PL_HAS_LED
  #include "LED.h"
#endif
#if PL_HAS_KEYS
  #include "Keys.h"
#endif
#if PL_HAS_BUZZER
  #include "Buzzer.h"
#endif
#if PL_HAS_RTOS
  #include "FRTOS1.h"
  #include "RTOS.h"
#endif

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
		EVNT_SetEvent(EVNT_REF_START_STOP_CALIBRATION);
		LED1_Neg();
	    (void) BUZ_Beep(20,1000);
	    break;
	#endif
	#if PL_NOF_KEYS>=2
	  case EVNT_SW2_PRESSED:
	    //LED2_Neg();
	    break;
	#endif
	#if PL_NOF_KEYS>=3
	  case EVNT_SW3_PRESSED:
	    //LED3_Neg();
	    break;
	#endif
	#if PL_NOF_KEYS>=4
	  case EVNT_SW4_PRESSED:
	    //LED4_Neg();
	    break;
	#endif

	    default:
	      break;
	  }
	}


#if PL_HAS_RTOS
static portTASK_FUNCTION(MainTask, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    EVNT_HandleEvent(APP_HandleEvent);
#if PL_HAS_KEYS && !PL_HAS_KBI
    KEY_Scan(); /* poll keys */
#endif
   //LED1_Neg();
   //SHELL_SendString("Hello");
    FRTOS1_vTaskDelay(20/portTICK_RATE_MS);
    
    
  }
}
#else
static void APP_Loop(void) {
  for(;;) {
    EVNT_HandleEvent(APP_EvntHandler);
#if PL_HAS_KEYS && !PL_HAS_KBI
    KEY_Scan(); /* poll keys */
#endif
  } /* for */
}
#endif


void APP_Run(void) {
	PL_Init();
	  EVNT_SetEvent(EVNT_INIT);
	#if PL_HAS_RTOS
	  if (FRTOS1_xTaskCreate(
	        MainTask,  /* pointer to the task */
	        "Main", /* task name for kernel awareness debugging */
	        configMINIMAL_STACK_SIZE, /* task stack size */
	        (void*)NULL, /* optional task startup argument */
	        tskIDLE_PRIORITY,  /* initial priority */
	        (xTaskHandle*)NULL /* optional task handle to create */
	      ) != pdPASS) {
	    /*lint -e527 */
	    for(;;){} /* error! probably out of memory */
	    /*lint +e527 */
	  }
	  FRTOS1_vTaskStartScheduler();
	#else
	  APP_Loop();
	#endif
	  PL_Deinit();
}
