/**
 * \file
 * \brief Real Time Operating System (RTOS) main program.
 * \author Erich Styger, erich.styger@hslu.ch
 */

#include "Platform.h"
#if PL_HAS_RTOS
#include "RTOS.h"
#include "FRTOS1.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "WAIT1.h"

#if 0
static portTASK_FUNCTION(T1, pvParameters) {
  for(;;) {
    //LED3_Neg();
    FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
  }
}
#endif
#if 0
static portTASK_FUNCTION(T2, pvParameters) {
  for(;;) {
    //LED2_Neg();
    FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
  }
}
#endif

void RTOS_Init(void) {
  /*! \todo Add RTOS here */
#if 0
  if (FRTOS1_xTaskCreate(T1, (signed portCHAR *)"T1", configMINIMAL_STACK_SIZE, NULL, 3, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
#if 0
  if (FRTOS1_xTaskCreate(T2, (signed portCHAR *)"T2", configMINIMAL_STACK_SIZE, NULL, 3, NULL) != pdPASS) {
    for(;;){} /* error */
  }
#endif
}

void RTOS_Deinit(void) {
}

#endif /* PL_HAS_RTOS */
