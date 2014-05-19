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
#if PL_HAS_TIMER
  #include "Timer.h"
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
#if PL_HAS_SHELL
  #include "Shell.h"
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

typedef enum {
  APP_STATE_INIT,
  APP_STATE_STOP,
  APP_STATE_SEARCH_OPPONENT,
  APP_STATE_FOUND_OPPONENT,
  APP_STATE_BOARDER_REACHED,
  APP_STATE_BOARDER_REACHED_LEFT,
  APP_STATE_BOARDER_REACHED_RIGHT
} AppStateType;
static volatile AppStateType appState = APP_STATE_INIT; /* state machine state */

#if PL_HAS_MOTOR
MOT_MotorDevice *motorL, *motorR;
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
		if (appState == APP_STATE_STOP)
		{
			  SHELL_SendString((unsigned char*)"Starting Wait 5s.\r\n");
			  while(!TMR_wate_5sec()){}
			  
			  SHELL_SendString((unsigned char*)"Starting Combat.\r\n");
			  
			  appState = APP_STATE_SEARCH_OPPONENT;
		}
		else
		{
			appState = APP_STATE_STOP;
			SHELL_SendString((unsigned char*)"Stop.\r\n");
		}
			
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
			
			appState = APP_STATE_STOP;
			SHELL_SendString((unsigned char*)"Fall of Arena.\r\n");
			break;
		
		case EVNT_FOUND_OPPONENT:			
			if (appState != APP_STATE_STOP)
			{
				appState = APP_STATE_FOUND_OPPONENT;
				SHELL_SendString((unsigned char*)"Found Opponent.\r\n");
			}
			break;
			
		case EVNT_REF_FULLY_ON_BOARDER:			
			if (appState != APP_STATE_STOP)
			{			
				appState = APP_STATE_BOARDER_REACHED;
				SHELL_SendString((unsigned char*)"Boarder Reached full.\r\n");
			}
			break;
			
		case EVNT_REF_LEFT_ON_BOARDER:						
			if (appState != APP_STATE_STOP)
			{
				appState = APP_STATE_BOARDER_REACHED_LEFT;
				SHELL_SendString((unsigned char*)"Boarder Reached left.\r\n");
			}
			break;
			
		case EVNT_REF_RIGHT_ON_BOARDER:			
			if (appState != APP_STATE_STOP)
			{
				appState = APP_STATE_BOARDER_REACHED_RIGHT;
				SHELL_SendString((unsigned char*)"Boarder Reached right.\r\n");
			}
			break;
			
	
		default:
		  break;
	  }
	}

uint16 driveBackCnt;
static void APP_StateMachine(void)
{
	switch (appState){
	
		case APP_STATE_INIT:
			appState = APP_STATE_STOP;
			break;

		case APP_STATE_STOP:			
			#if PL_HAS_MOTOR
				MOT_SetSpeedPercent(motorL, 0);
				MOT_SetSpeedPercent(motorR, 0);
			#endif
			break;

		case APP_STATE_SEARCH_OPPONENT:			
			#if PL_HAS_MOTOR
			MOT_SetSpeedPercent(motorL, 12);
			MOT_SetSpeedPercent(motorR, -12);
			#endif
			
			break;

		case APP_STATE_FOUND_OPPONENT:
			#if PL_HAS_MOTOR
			MOT_SetSpeedPercent(motorL, 50);
			MOT_SetSpeedPercent(motorR, 50);
			#endif
			break;

		case APP_STATE_BOARDER_REACHED:
			driveBackCnt += 20;
						
			#if PL_HAS_MOTOR
			MOT_SetSpeedPercent(motorL, -50);
			MOT_SetSpeedPercent(motorR, -50);
			#endif	
			
			if (driveBackCnt >= 600)
			{
				driveBackCnt = 0;
				appState = APP_STATE_SEARCH_OPPONENT;
			}
			break;

		case APP_STATE_BOARDER_REACHED_LEFT:
			driveBackCnt += 20;
						
			#if PL_HAS_MOTOR
			MOT_SetSpeedPercent(motorL, -40);
			MOT_SetSpeedPercent(motorR, -20);
			#endif
				
			if (driveBackCnt >= 400)
			{		
				driveBackCnt = 0;
				appState = APP_STATE_SEARCH_OPPONENT;
			}
			break;

		case APP_STATE_BOARDER_REACHED_RIGHT:
			driveBackCnt += 20;
						
			#if PL_HAS_MOTOR
			MOT_SetSpeedPercent(motorL, -20);
			MOT_SetSpeedPercent(motorR, -40);
			#endif	
			
			if (driveBackCnt >= 400)
			{		
				driveBackCnt = 0;	
				appState = APP_STATE_SEARCH_OPPONENT;
			}
			break;
			

		default:
			break;
			
		
	}
}


#if PL_HAS_RTOS
static portTASK_FUNCTION(MainTask, pvParameters) {
	
  int16_t x, y, z;
  int cnt_accel = 0;
	
#if PL_IS_FRDM
    ACCEL_LowLevelInit(); 
#endif 
    
    (void)pvParameters; /* parameter not used */
  for(;;)
  {
	  
	EVNT_HandleEvent(APP_HandleEvent);
	
#if PL_HAS_ACCEL && PL_HAS_MOTOR

	  ACCEL_GetValues(&x,&y,&z);
	  if (z>700)
	  {
		  cnt_accel++;
		  if(cnt_accel>=5)
		  {
			EVNT_SetEvent(EVNT_FALL_OFF_ARENA);
		  }
	  }
	  else
	  {
		  cnt_accel = 0;
	  }
#endif
	  
#if PL_HAS_KEYS && !PL_HAS_KBI
    KEY_Scan(); /* poll keys */
#endif
    
#if PL_HAS_ULTRASONIC	
	if ((US_GetLastCentimeterValue() < 50) && (appState != APP_STATE_FOUND_OPPONENT))
	{
		EVNT_SetEvent(EVNT_FOUND_OPPONENT);
	}
	else
	{
/*		if (appState != APP_STATE_STOP)
		{
			appState = APP_STATE_SEARCH_OPPONENT;
		}
*/	}
#endif
	
	APP_StateMachine();
	
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
	motorL = MOT_GetMotorHandle(MOT_MOTOR_LEFT);
	motorR = MOT_GetMotorHandle(MOT_MOTOR_RIGHT);
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
