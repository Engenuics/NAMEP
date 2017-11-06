/***********************************************************************************************************************
File: main.c                                                                

Description:
Container for the MPG nRF51422 firmware.  
***********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32SystemFlags = 0;                     /* Global system flags */

/*--------------------------------------------------------------------------------------------------------------------*/
/* External global variables defined in other files (must indicate which file they are defined in) */
extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "Main_" and be declared as static.
***********************************************************************************************************************/
u32 Main_u32ErrorCode;

u8 Main_u8TestMessage[] = "9876 test message from ANT";

/***********************************************************************************************************************
Main Program
Main has two sections:

1. Initialization which is run once on power-up or reset.  All drivers and applications are setup here without timing
contraints but must complete execution regardless of success or failure of starting the application. 

2. Main loop.  This is an event-driven system that sequentially executes tasks that require servicing in the event queue.

***********************************************************************************************************************/

void main(void)
{
  u32 u32Counter = 0;
  u32 u32M3PeriodCounter = 0;
  
  /* Low level initialization */
  G_u32SystemFlags |= _SYSTEM_INITIALIZING;  

  InterruptSetup();
  ClockSetup();
  GpioSetup();
  I2cMasterInitialize();

  WatchDogSetup(); /* During development, set to not reset processor if timeout */
  SysTickSetup();

  /* Driver initialization */
  LedInitialize();
  //AntInitialize();

  /* Application initialization */
  PovInitialize();
  
  /* Exit initialization */
  G_u32SystemFlags &= ~_SYSTEM_INITIALIZING;
  
  
  /* Main loop */  
  while(1)
  {
    /* If no acceleration is detected, turn off all LEDs, LP the accelerometer, and sleep the processor */
    
    /**/
    
    LedUpdate();
    
        
    /* System sleep */
    SystemSleep();
    
  } /* end while(1) main super loop */
  
} /* end main() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File */
/*--------------------------------------------------------------------------------------------------------------------*/
