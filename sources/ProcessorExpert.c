/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-03-21, 10:55, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file ProcessorExpert.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup ProcessorExpert_module ProcessorExpert module documentation
**  @{
*/         
/* MODULE ProcessorExpert */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Led_Blue.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "Led_Green.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "Led_Red.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "CC_VREG_EN.h"
#include "BitIoLdd4.h"
#include "CC_RESET.h"
#include "BitIoLdd5.h"
#include "CC_CSN.h"
#include "BitIoLdd6.h"
#include "CC_CLK.h"
#include "BitIoLdd7.h"
#include "CC_FIFO.h"
#include "BitIoLdd8.h"
#include "CC_CCA.h"
#include "BitIoLdd10.h"
#include "CC_SFD.h"
#include "BitIoLdd11.h"
#include "USBD.h"
#include "USB0.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "CS1.h"
#include "CS2.h"
#include "INT_TPM0.h"
#include "INT_SysTick.h"
#include "GI2C1.h"
#include "WAIT1.h"
#include "I2C0.h"
#include "MMA1.h"
#include "UTIL1.h"
#include "INT_LPTimer.h"
#include "INT_DMA0.h"
#include "INT_PORTD.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
void SysTick_IRQHandler(void){}
void TPM0_IRQHandler(void){}

#if USB_CDC
static uint8_t cdc_buffer[USBD_DATA_BUFF_SIZE];
static uint8_t in_buffer[USBD_DATA_BUFF_SIZE];
 
static void
CDC_Run(void)
{
  int i;

  for (;;)
    {
      while (CDC1_App_Task(cdc_buffer, sizeof(cdc_buffer)) == ERR_BUSOFF)
        {
          /* device not enumerated */
          Led_Red_Neg();
          Led_Green_Off();
          WAIT1_Waitms(10);
        }
      Led_Red_Off();
      Led_Green_Neg();
      if (CDC1_GetCharsInRxBuf() != 0)
        {
          i = 0;
          while (i < sizeof(in_buffer) - 1
              && CDC1_GetChar(&in_buffer[i]) == ERR_OK)
            {
              i++;
            }
          in_buffer[i] = '\0';
          (void) CDC1_SendString((unsigned char*) "echo: ");
          (void) CDC1_SendString(in_buffer);
          (void) CDC1_SendString((unsigned char*) "\r\n");
        }
      else
        {
          WAIT1_Waitms(10);
        }
    }
}
#endif

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
#if USB_CDC
  CDC_Run();
#endif

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.08]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
