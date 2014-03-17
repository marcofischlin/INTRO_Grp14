/**
 * \file
 * \brief Key/Switch driver implementation.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic keyboard driver for up to 4 Keys.
 * It is using macros for maximum flexibility with minimal code overhead.
 */

#include "Platform.h"
#if PL_HAS_KEYS
  #include "Keys.h"
#if PL_HAS_EVENTS
  #include "Event.h"
#endif

void KEY_Scan(void) {
  /*! \todo Implement handling of keys */
	if (KEY1_Get()){
		EVNT_SetEvent(EVNT_KEY1_PRESSED);
		
	}else if (KEY2_Get()){
		EVNT_SetEvent(EVNT_KEY2_PRESSED);
		
	}else if (KEY3_Get()){
			EVNT_SetEvent(EVNT_KEY3_PRESSED);
			
	}else if (KEY4_Get()){
			EVNT_SetEvent(EVNT_KEY4_PRESSED);
	}
}

#if PL_HAS_KBI
void KEY_OnInterrupt(void) {
  KEY_Scan();
}
#endif

/*! \brief Key driver initialization */
void KEY_Init(void) {
  /* nothing needed for now */
}

/*! \brief Key driver de-initialization */
void KEY_Deinit(void) {
  /* nothing needed for now */
}
#endif /* PL_HAS_KEYS */
