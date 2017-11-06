/***********************************************************************************************************************
File: leds_nRF51.c                                                                

Description:
LED driver that provides on, off, toggle, blink and PWM functionality.
The basic on/off/toggle functionality is applied directly to the LEDs.
Blinking and PWMing of LEDs rely on a 1ms system tick to provide timing at
regular 1ms calls to LedUpdate().

------------------------------------------------------------------------------------------------------------------------
API:
LedNumberType: BLUE, GREEN, YELLOW, RED

LedRateType: LED_0_5HZ, LED_1HZ, LED_2HZ, LED_4HZ, LED_8HZ, 
             LED_PWM_0, LED_PWM_5, ..., LED_PWM_100
*Note that PWM values in LedRateType are continuous, thus stepping a variable of LedRateType by one will select the next 
PWM level. However, decrementing past LED_PWM_0 or incrementing past LED_PWM_100 is undefined.


Public:
void LedOn(LedNumberType eLED_)
Turn the specified LED on. LED response is immediate.
e.g. LedOn(BLUE);

void LedOff(LedNumberType eLED_)
Turn the specified LED off. LED response is immediate.
e.g. LedOff(BLUE);

void LedToggle(LedNumberType eLED_)
Toggle the specified LED.  LED response is immediate.
e.g. LedToggle(BLUE);

void LedPWM(LedNumberType eLED_, LedRateType ePwmRate_)
Sets up an LED for PWM mode.  PWM mode requries the main loop to be running at 1ms period.
e.g. LedPWM(BLUE, LED_PWM_5);

void LedBlink(LedNumberType eLED_, LedRateType eBlinkRate_)
Sets an LED to BLINK mode.  BLINK mode requries the main loop to be running at 1ms period.
e.g. LedBlink(BLUE, LED_1HZ);

Protected:
void LedInitialize(void)
Test all LEDs and initialize to OFF state.

DISCLAIMER: THIS CODE IS PROVIDED WITHOUT ANY WARRANTY OR GUARANTEES.  USERS MAY
USE THIS CODE FOR DEVELOPMENT AND EXAMPLE PURPOSES ONLY.  ENGENUICS TECHNOLOGIES
INCORPORATED IS NOT RESPONSIBLE FOR ANY ERRORS, OMISSIONS, OR DAMAGES THAT COULD
RESULT FROM USING THIS FIRMWARE IN WHOLE OR IN PART.
***********************************************************************************************************************/

#include "configuration.h"


/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_xxLed"
***********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
/* New variables (all shall start with G_xxLed*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* External global variables defined in other files (must indicate which file they are defined in) */
extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */

extern volatile u32 G_u32ApplicationFlags;             /* From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "Led_" and be declared as static.
***********************************************************************************************************************/
/* LED locations: order must correspond to the order set in LedNumberType in the header file. */
static u32 Led_au32BitPositions[] = {P0_19_ARED, P0_17_AGRN, P0_18_ABLU, P0_13_DRED, P0_11_DGRN, P0_12_DBLU,
                                     P0_10_YRED, P0_08_YGRN, P0_09_YBLU, P0_15_MRED, P0_14_MGRN, P0_16_MBLU};

/* Control array for all LEDs in system initialized for LedInitialize().  Array values correspond to LedConfigType fields: 
     eMode         eRate      u16Count       eCurrentDuty     eActiveState     ePort      LedNumberType */
static LedConfigType Leds_asLedArray[TOTAL_LEDS] = 
{
 {LED_NORMAL_MODE, LED_PWM_100, LED_PWM_100, LED_PWM_DUTY_HIGH, LED_ACTIVE_HIGH}, /* ARED       */
 {LED_NORMAL_MODE, LED_PWM_100, LED_PWM_100, LED_PWM_DUTY_HIGH, LED_ACTIVE_HIGH}, /* AGRN      */
 {LED_NORMAL_MODE, LED_PWM_100, LED_PWM_100, LED_PWM_DUTY_HIGH, LED_ACTIVE_HIGH}, /* ABLU        */
 {LED_NORMAL_MODE, LED_PWM_100, LED_PWM_100, LED_PWM_DUTY_HIGH, LED_ACTIVE_HIGH}, /* DRED        */
 {LED_NORMAL_MODE, LED_PWM_100, LED_PWM_100, LED_PWM_DUTY_HIGH, LED_ACTIVE_HIGH}, /* DGRN        */
 {LED_NORMAL_MODE, LED_PWM_100, LED_PWM_100, LED_PWM_DUTY_HIGH, LED_ACTIVE_HIGH}, /* DBLU        */
 {LED_NORMAL_MODE, LED_PWM_100, LED_PWM_100, LED_PWM_DUTY_HIGH, LED_ACTIVE_HIGH}, /* YRED        */
 {LED_NORMAL_MODE, LED_PWM_100, LED_PWM_100, LED_PWM_DUTY_HIGH, LED_ACTIVE_HIGH}, /* YGRN        */
 {LED_NORMAL_MODE, LED_PWM_100, LED_PWM_100, LED_PWM_DUTY_HIGH, LED_ACTIVE_HIGH}, /* YBLU        */
 {LED_NORMAL_MODE, LED_PWM_100, LED_PWM_100, LED_PWM_DUTY_HIGH, LED_ACTIVE_HIGH}, /* MRED        */
 {LED_NORMAL_MODE, LED_PWM_100, LED_PWM_100, LED_PWM_DUTY_HIGH, LED_ACTIVE_HIGH}, /* MGRN       */
 {LED_NORMAL_MODE, LED_PWM_100, LED_PWM_100, LED_PWM_DUTY_HIGH, LED_ACTIVE_HIGH}, /* MBLU       */
};   
 

/***********************************************************************************************************************
* Function Definitions
***********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions */
/*--------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------
Function: LedOn

Description:
Turn the specified LED on.  Automatically takes care of the active low vs. active
high LEDs.  

Requires:
  - eLED_ is a valid LED index
  - Definitions in Leds_asLedArray[eLED_] are correct
  - Supports port 0 GPIO only

Promises:
  - Requested LED is turned on 
  - Requested LED is always set to LED_NORMAL_MODE mode
*/
void LedOn(LedNumberType eLED_)
{

  if(Leds_asLedArray[eLED_].eActiveState == LED_ACTIVE_HIGH)
  {
    NRF_GPIO->OUTSET = Led_au32BitPositions[eLED_];
  }
  else
  {
    NRF_GPIO->OUTCLR = Led_au32BitPositions[eLED_];
  }
  
  /* Always set the LED back to LED_NORMAL_MODE mode */
	Leds_asLedArray[(u8)eLED_].eMode = LED_NORMAL_MODE;

} /* end LedOn() */


/*----------------------------------------------------------------------------------------------------------------------
Function: LedOff

Description:
Turn the specified LED off.  Automatically takes care of the active low vs. active
high LEDs.  

Requires:
  - eLED_ is a valid LED index
  - Definitions in Leds_asLedArray[eLED_] are correct

Promises:
  - Requested LED is turned off
  - Requested LED is always set to LED_NORMAL_MODE mode
*/
void LedOff(LedNumberType eLED_)
{
  if(Leds_asLedArray[eLED_].eActiveState == LED_ACTIVE_HIGH)
  {
    NRF_GPIO->OUTCLR = Led_au32BitPositions[eLED_];
  }
  else
  {
    NRF_GPIO->OUTSET = Led_au32BitPositions[eLED_];
  }

  /* Always set the LED back to LED_NORMAL_MODE mode */
	Leds_asLedArray[(u8)eLED_].eMode = LED_NORMAL_MODE;
  
} /* end LedOff() */


/*----------------------------------------------------------------------------------------------------------------------
Function: LedToggle

Description:
Toggle the specified LED.

Requires:
  - eLED_ is a valid LED index
  - eLED_ *should* be in LED_NORMAL_MODE

Promises:
  - Requested LED is toggled
*/
void LedToggle(LedNumberType eLED_)
{
  u32 u32Current_Leds;
  
  u32Current_Leds = NRF_GPIO->IN;
  u32Current_Leds ^= Led_au32BitPositions[eLED_];
  NRF_GPIO->OUT = u32Current_Leds;
                                            
} /* end LedToggle() */


/*----------------------------------------------------------------------------------------------------------------------
Function: LedPWM

Description:
Sets an LED to PWM mode

Requires:
  - eLED_ is a valid LED index
  - ePwmRate_ is an allowed duty cycle:
    LED_PWM_0, LED_PWM_5, LED_PWM_10, ..., LED_PWM_95, LED_PWM_100

Promises:
  - Requested LED is set to PWM mode at the duty cycle specified
*/
void LedPWM(LedNumberType eLED_, LedRateType ePwmRate_)
{
	Leds_asLedArray[(u8)eLED_].eMode = LED_PWM_MODE;
	Leds_asLedArray[(u8)eLED_].eRate = ePwmRate_;
	Leds_asLedArray[(u8)eLED_].u16Count = (u16)ePwmRate_;
  Leds_asLedArray[(u8)eLED_].eCurrentDuty = LED_PWM_DUTY_HIGH;

} /* end LedPWM() */


/*----------------------------------------------------------------------------------------------------------------------
Function: LedBlink

Description:
Sets an LED to BLINK mode.

Requires:
  - eLED_ is a valid LED index
  - eBlinkRate_ is an allowed frequency:
    LED_0_5HZ, LED_1HZ, LED_2HZ, LED_4HZ, LED_8HZ

Promises:
  - Requested LED is set to BLINK mode at the rate specified
*/
void LedBlink(LedNumberType eLED_, LedRateType eBlinkRate_)
{
	Leds_asLedArray[(u8)eLED_].eMode = LED_BLINK_MODE;
	Leds_asLedArray[(u8)eLED_].eRate = eBlinkRate_;
	Leds_asLedArray[(u8)eLED_].u16Count = eBlinkRate_;

} /* end LedBlink() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions */
/*--------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------
Function: LedInitialize

Description:
Initialization of LED system paramters and visual LED check.

Requires:
  - G_u32SystemTime1ms ticking
  - All LEDs already initialized to LED_NORMAL_MODE mode ON

Promises:
  - All LEDs in LED_NORMAL_MODE mode with OFF
*/
void LedInitialize(void)
{
  u32 u32Timer;
  LedNumberType aeLedSequence[] = {ARED};

  /* Static Display of all colors */
  LedOn(ARED);
  LedOff(AGRN);
  LedOn(ABLU);
  
  LedOn(DRED);
  LedOff(DGRN);
  LedOff(DBLU);

  LedOff(YRED);
  LedOn(YGRN);
  LedOff(YBLU);

  LedOff(MRED);
  LedOff(MGRN);
  LedOn(MBLU);
  
  while(1);
  /* end of static display */

  
  while(1)
#if 0
  {
    /* Sequentially light up a specific color of LEDs */
    for(u8 k = 0; k < 3; k++)
    {
      for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
      {
        LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * k)]);
        for(u32 j = 0; j < 200000; j++);
      }
      
      /* Pause for show */
      for(u32 i = 0; i < 500000; i++);

      /* Turn off the current LEDs */
      for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
      {
        LedOff(aeLedSequence[i + (8 * k)]);
      }
    }
#endif

#if 0 /* one-way sequence */
  {
    /* Red */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 0)]);
      for(u32 j = 0; j < STEP_TIME; j++);
    }    

    /* Pause for show */
    for(u32 i = 0; i < PAUSE_TIME; i++);

    /* All off */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOff(aeLedSequence[i + (8 * 0)]);
      LedOff(aeLedSequence[i + (8 * 1)]);
      LedOff(aeLedSequence[i + (8 * 2)]);
    }

    /* Yellow */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 0)]);
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 1)]);
      for(u32 j = 0; j < STEP_TIME; j++);
    }    

    /* Pause for show */
    for(u32 i = 0; i < PAUSE_TIME; i++);

    /* All off */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOff(aeLedSequence[i + (8 * 0)]);
      LedOff(aeLedSequence[i + (8 * 1)]);
      LedOff(aeLedSequence[i + (8 * 2)]);
    }

    /* Green */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 1)]);
      for(u32 j = 0; j < STEP_TIME; j++);
    }    

    /* Pause for show */
    for(u32 i = 0; i < PAUSE_TIME; i++);

    /* All off */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOff(aeLedSequence[i + (8 * 0)]);
      LedOff(aeLedSequence[i + (8 * 1)]);
      LedOff(aeLedSequence[i + (8 * 2)]);
    }

    /* Cyan */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 1)]);
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 2)]);
      for(u32 j = 0; j < STEP_TIME; j++);
    }    

    /* Pause for show */
    for(u32 i = 0; i < PAUSE_TIME; i++);

    /* All off */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOff(aeLedSequence[i + (8 * 0)]);
      LedOff(aeLedSequence[i + (8 * 1)]);
      LedOff(aeLedSequence[i + (8 * 2)]);
    }

    /* Blue */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 2)]);
      for(u32 j = 0; j < STEP_TIME; j++);
    }    

    /* Pause for show */
    for(u32 i = 0; i < PAUSE_TIME; i++);

    /* All off */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOff(aeLedSequence[i + (8 * 0)]);
      LedOff(aeLedSequence[i + (8 * 1)]);
      LedOff(aeLedSequence[i + (8 * 2)]);
    }

    
    /* Purple */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 0)]);
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 2)]);
      for(u32 j = 0; j < STEP_TIME; j++);
    }    

    /* Pause for show */
    for(u32 i = 0; i < PAUSE_TIME; i++);

    /* All off */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOff(aeLedSequence[i + (8 * 0)]);
      LedOff(aeLedSequence[i + (8 * 1)]);
      LedOff(aeLedSequence[i + (8 * 2)]);
    }

    /* White */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 0)]);
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 1)]);
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 2)]);
      for(u32 j = 0; j < STEP_TIME; j++);
    }    

    /* Pause for show */
    for(u32 i = 0; i < PAUSE_TIME; i++);

    /* All off */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOff(aeLedSequence[i + (8 * 0)]);
      LedOff(aeLedSequence[i + (8 * 1)]);
      LedOff(aeLedSequence[i + (8 * 2)]);
    }

  }
#endif
  
  
  {
    /* Red */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 0)]);
      for(u32 j = 0; j < STEP_TIME; j++);
    }    

    for(u32 j = 0; j < STEP_TIME; j++);

    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOff(aeLedSequence[7 - i + (NUM_LEDS_PER_COLOR * 0)]);
      for(u32 j = 0; j < STEP_TIME; j++);
    }    

    /* Yellow */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 0)]);
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 1)]);
      for(u32 j = 0; j < STEP_TIME; j++);
    }    

    for(u32 j = 0; j < STEP_TIME; j++);

    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOff(aeLedSequence[7 - i + (NUM_LEDS_PER_COLOR * 0)]);
      LedOff(aeLedSequence[7 - i + (NUM_LEDS_PER_COLOR * 1)]);
      for(u32 j = 0; j < STEP_TIME; j++);
    }    

    /* Green */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 1)]);
      for(u32 j = 0; j < STEP_TIME; j++);
    }    

    for(u32 j = 0; j < STEP_TIME; j++);

    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOff(aeLedSequence[7 - i + (NUM_LEDS_PER_COLOR * 1)]);
      for(u32 j = 0; j < STEP_TIME; j++);
    }    

    /* Cyan */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 1)]);
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 2)]);
      for(u32 j = 0; j < STEP_TIME; j++);
    }    

    for(u32 j = 0; j < STEP_TIME; j++);

    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOff(aeLedSequence[7 - i + (NUM_LEDS_PER_COLOR * 1)]);
      LedOff(aeLedSequence[7 - i + (NUM_LEDS_PER_COLOR * 2)]);
      for(u32 j = 0; j < STEP_TIME; j++);
    }    

    /* Blue */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 2)]);
      for(u32 j = 0; j < STEP_TIME; j++);
    }    

    for(u32 j = 0; j < STEP_TIME; j++);

   for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOff(aeLedSequence[7 - i + (NUM_LEDS_PER_COLOR * 2)]);
      for(u32 j = 0; j < STEP_TIME; j++);
    }    

    /* Purple */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 0)]);
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 2)]);
      for(u32 j = 0; j < STEP_TIME; j++);
    }    

    for(u32 j = 0; j < STEP_TIME; j++);

    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOff(aeLedSequence[7 - i + (NUM_LEDS_PER_COLOR * 0)]);
      LedOff(aeLedSequence[7 - i + (NUM_LEDS_PER_COLOR * 2)]);
      for(u32 j = 0; j < STEP_TIME; j++);
    }    

    /* While */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 0)]);
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 1)]);
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 2)]);
      for(u32 j = 0; j < STEP_TIME; j++);
    }    

    for(u32 j = 0; j < STEP_TIME; j++);

    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOff(aeLedSequence[7 - i + (NUM_LEDS_PER_COLOR * 0)]);
      LedOff(aeLedSequence[7 - i + (NUM_LEDS_PER_COLOR * 1)]);
      LedOff(aeLedSequence[7 - i + (NUM_LEDS_PER_COLOR * 2)]);
      for(u32 j = 0; j < STEP_TIME; j++);
    }    



  }
#if 0
  {
    /* Red */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOn(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 0)]);
      for(u32 j = 0; j < STEP_TIME; j++);
      LedOff(aeLedSequence[i + (NUM_LEDS_PER_COLOR * 0)]);
    }    

    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOn(aeLedSequence[(7 - i) + (NUM_LEDS_PER_COLOR * 0)]);
      for(u32 j = 0; j < STEP_TIME; j++);
      LedOff(aeLedSequence[(7 - i) + (NUM_LEDS_PER_COLOR * 0)]);
    }    

  }
#endif
  
  /* Finish with all white */
    for(u8 i = 0; i < NUM_LEDS_PER_COLOR; i++)
    {
      LedOn(aeLedSequence[i]);
      LedOn(aeLedSequence[i + NUM_LEDS_PER_COLOR]);
      LedOn(aeLedSequence[i + (2 * NUM_LEDS_PER_COLOR)]);
      for(u32 j = 0; j < 100000; j++);
    }

    /* Pause for show */
  for(u32 i = 0; i < 2000000; i++);

#if 0
  /* Turn all LEDs on full, then fade them out over a few seconds */
  for(u8 i = 20; i > 0; i--)
  {
    
    /* Spend 40ms in each level of intensity */
    for(u16 j = 40; j > 0; j--)
    {
      u32Timer = G_u32SystemTime1ms;
      while( !IsTimeUp(&u32Timer, 1) );
      LedUpdate();
    }
    /* Pause for a bit on the first iteration to show the LEDs on for little while */
    if(i == 20)
    {
      while( !IsTimeUp(&u32Timer, 1500) );
    }
    
    /* Set the LED intensity for the next iteration */
    for(u8 j = 0; j < TOTAL_LEDS; j++)
    {
      Leds_asLedArray[j].eRate = (LedRateType)(i - 1);
    }
  }

  /* Final update to set last state, hold for a short period */
  LedUpdate();
  while( !IsTimeUp(&u32Timer, 200) );
#endif
  
} /* end LedInitialize() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions */
/*--------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------
Function: LedUpdate

Description:
Update all LEDs for the current cycle.

Requires:
 - G_u32SystemTime1ms is counting

Promises:
   - All LEDs updated based on their counters
*/
void LedUpdate(void)
{
	/* Loop through each LED */
  for(u8 i = 0; i < TOTAL_LEDS; i++)
  {
    /* Check if LED is PWMing */
    if(Leds_asLedArray[(LedNumberType)i].eMode == LED_PWM_MODE)
    {
      /* Handle special case of 0% duty cycle */
      if( Leds_asLedArray[i].eRate == LED_PWM_0 )
      {
        LedOff( (LedNumberType)i );
      }
      
      /* Handle special case of 100% duty cycle */
      else if( Leds_asLedArray[i].eRate == LED_PWM_100 )
      {
        LedOn( (LedNumberType)i );
      }
  
      /* Otherwise, regular PWM: decrement counter; toggle and reload if counter reaches 0 */
      else
      {
        if(--Leds_asLedArray[(LedNumberType)i].u16Count == 0)
        {
          if(Leds_asLedArray[(LedNumberType)i].eCurrentDuty == LED_PWM_DUTY_HIGH)
          {
            /* Turn the LED off and update the counters for the next cycle */
            LedOff( (LedNumberType)i );
            Leds_asLedArray[(LedNumberType)i].u16Count = LED_PWM_PERIOD - Leds_asLedArray[(LedNumberType)i].eRate;
            Leds_asLedArray[(LedNumberType)i].eCurrentDuty = LED_PWM_DUTY_LOW;
          }
          else
          {
            /* Turn the LED on and update the counters for the next cycle */
            LedOn( (LedNumberType)i );
            Leds_asLedArray[i].u16Count = Leds_asLedArray[i].eRate;
            Leds_asLedArray[i].eCurrentDuty = LED_PWM_DUTY_HIGH;
          }
        }
      }

      /* Set the LED back to PWM mode since LedOff and LedOn set it to normal mode */
     	Leds_asLedArray[(LedNumberType)i].eMode = LED_PWM_MODE;
      
    } /* end if PWM mode */
    
    /* LED is in LED_BLINK_MODE mode */
    else if(Leds_asLedArray[(LedNumberType)i].eMode == LED_BLINK_MODE)
    {
      /* Decrement counter; toggle and reload if counter reaches 0 */
      if( --Leds_asLedArray[(LedNumberType)i].u16Count == 0)
      {
        LedToggle( (LedNumberType)i );
        Leds_asLedArray[(LedNumberType)i].u16Count = Leds_asLedArray[(LedNumberType)i].eRate;
      }
    }
  } /* end for */
} /* end LedUpdate() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File */
/*--------------------------------------------------------------------------------------------------------------------*/


