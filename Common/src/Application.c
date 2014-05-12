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
#if PL_HAS_MOTOR
  #include "Motor.h"
#endif
#if PL_HAS_ACCEL
  #include "Accel.h"
#endif
#if PL_HAS_MOTOR_TACHO
  #include "Tacho.h"
#endif
#if PL_HAS_ULTRASONIC
  #include "Ultrasonic.h"
#endif
#if PL_HAS_DRIVE
  #include "Drive.h"
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
			LED1_Neg();
		    (void) BUZ_Beep(20,1000);
		  break;
		  
	  case EVNT_SW1_LPRESSED:
		#if PL_HAS_LINE_SENSOR
		  EVNT_SetEvent(EVNT_REF_START_STOP_CALIBRATION);
		#endif
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
	    
		case EVNT_FALL_OFF_ARENA:
			#if PL_HAS_MOTOR
	
			DRV_SetSpeed(0, 0);
			#endif
			break;
		
		case EVNT_FOUND_OPPONENT:			
			#if PL_HAS_MOTOR
	
			DRV_SetSpeed(100, 100);
			#endif
			break;
			
		case EVNT_REF_FULLY_ON_BOARDER:			
			#if PL_HAS_MOTOR
			
			DRV_SetSpeed(-60, -60);
			#endif
			break;
			
		case EVNT_REF_LEFT_ON_BOARDER:			
			#if PL_HAS_MOTOR
			
			DRV_SetSpeed(-40, -60);
			#endif
			break;
			
		case EVNT_REF_RIGHT_ON_BOARDER:			
			#if PL_HAS_MOTOR
			
			DRV_SetSpeed(-60, -40);
			#endif
			break;
			
	
		default:
		  break;
	  }
	}


#if PL_HAS_RTOS
static portTASK_FUNCTION(MainTask, pvParameters) {
	
  int16_t x, y, z;
	
#if PL_IS_FRDM
    ACCEL_LowLevelInit(); 
#endif 
    
    (void)pvParameters; /* parameter not used */
  for(;;)
  {
	  
	EVNT_HandleEvent(APP_HandleEvent);
	
#if PL_HAS_ACCEL && PL_HAS_MOTOR

	  ACCEL_GetValues(&x,&y,&z);
	  if (z>800)
	  {
			EVNT_SetEvent(EVNT_FALL_OFF_ARENA);
	  }
#endif
	  
#if PL_HAS_KEYS && !PL_HAS_KBI
    KEY_Scan(); /* poll keys */
#endif
    
#if PL_HAS_ULTRASONIC	
	if (US_GetLastCentimeterValue() < 60)
	{
		EVNT_SetEvent(EVNT_FOUND_OPPONENT);
	}
#endif
	
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
	        (unsigned char*)"Main", /* task name for kernel awareness debugging */
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
