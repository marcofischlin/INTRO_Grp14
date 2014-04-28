/**
 * \file
 * \brief Tachometer Module
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module to calculate the speed based on the quadrature counter.
 */

#include "Platform.h" /* interface to the platform */
#if PL_HAS_MOTOR_TACHO
#include "Tacho.h"    /* our own interface */
#include "Q4CLeft.h"
#include "Q4CRight.h"
#if PL_HAS_SHELL
  #include "CLS1.h"
#endif
#include "UTIL1.h"
#include "FRTOS1.h"

  /*! \todo Set appropriate values for NOF_ROUND_PULSE, TACHO_SAMPLE_PERIOD_MS and NOF_HISTORY */
#define NOF_ROUND_PULSE      (48)    
  /*!< number of pulses per round, given by encoder hardware, and we are detecting 4 steps for each period. Useful to calculate revolutions per time unit. */
#define TACHO_SAMPLE_PERIOD_MS (1)     
  /*!< speed sample period in ms. Make sure that speed is sampled at the given rate. */
#define NOF_HISTORY (16U+1U) 
  /*!< number of samples for speed calculation (>0):the more, the better, but the slower. */

static volatile uint16_t TACHO_LeftPosHistory[NOF_HISTORY], TACHO_RightPosHistory[NOF_HISTORY];
  /*!< for better accuracy, we calculate the speed over some samples */
static volatile uint8_t TACHO_PosHistory_Index = 0;
  /*!< position index in history */

static int32_t TACHO_currLeftSpeed = 0, TACHO_currRightSpeed = 0;
  /*!< position index in history */

int32_t TACHO_GetSpeed(bool isLeft) {
  if (isLeft) {
    return TACHO_currLeftSpeed;
  } else {
    return TACHO_currRightSpeed;
  }
}

void TACHO_CalcSpeed(void) {
  /*! \todo Implement function */ 
}

void TACHO_Sample(void) {
  /*! \todo Implement function */ 
}

#if PL_HAS_SHELL
/*!
 * \brief Prints the system low power status
 * \param io I/O channel to use for printing status
 */
static void TACHO_PrintStatus(const CLS1_StdIOType *io) {
  TACHO_CalcSpeed();
  CLS1_SendStatusStr((unsigned char*)"Tacho", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  L speed", (unsigned char*)"", io->stdOut);
  CLS1_SendNum32s(TACHO_GetSpeed(TRUE), io->stdOut);
  CLS1_SendStr((unsigned char*)" steps/sec\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  R speed", (unsigned char*)"", io->stdOut);
  CLS1_SendNum32s(TACHO_GetSpeed(FALSE), io->stdOut);
  CLS1_SendStr((unsigned char*)" steps/sec\r\n", io->stdOut);
}

/*! 
 * \brief Prints the help text to the console
 * \param io I/O channel to be used
 */
static void TACHO_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"tacho", (unsigned char*)"Group of tacho commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows tacho help or status\r\n", io->stdOut);
}

uint8_t TACHO_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"tacho help")==0) {
    TACHO_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"tacho status")==0) {
    TACHO_PrintStatus(io);
    *handled = TRUE;
  }
  return ERR_OK;
}
#endif /* PL_HAS_SHELL */

void TACHO_Deinit(void) {
}

void TACHO_Init(void) {
  TACHO_currLeftSpeed = 0;
  TACHO_currRightSpeed = 0;
  TACHO_PosHistory_Index = 0;
}

#endif /* PL_HAS_MOTOR_TACHO */

