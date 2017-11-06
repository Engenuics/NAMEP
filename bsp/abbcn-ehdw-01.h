/***********************************************************************************************************************
* File: adymn-pcb-01.h                                                                
* 
* Description:
* This file provides header information for the board support functions for nRF51422 processor on the 
adymn-pcb-01 board.
***********************************************************************************************************************/

#ifndef __ADYMN_H
#define __ADYMN_H

/***********************************************************************************************************************
Type Definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Constants
***********************************************************************************************************************/


/***********************************************************************************************************************
* Macros
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Declarations
***********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public Functions */
/*--------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected Functions */
/*--------------------------------------------------------------------------------------------------------------------*/
void WatchDogSetup(void);
void PowerSetup(void);
void GpioSetup(void);
void ClockSetup(void);
void InterruptSetup(void);
void SysTickSetup(void);
void SystemSleep(void);


/***********************************************************************************************************************
Perihperal Setup Initializations

Bookmarks:
@@@@@ Clock, Power Control, Systick and Watchdog setup values
!!!!! GPIO pin names
##### GPIO initial setup values
$$$$$ PWM setup values

***********************************************************************************************************************/

/***********************************************************************************************************************
@@@@@ Clock, Systick and Power Control setup values
***********************************************************************************************************************/
#define FOSC                    __SYSTEM_CLOCK    /* Crystal speed from system_nrf51.c */
#define OSC_STARTUP_TIMOUT      (u32)1000000      /* Timeout for oscillator to start up */
  
/* Timer 1
To get roughly a 1ms tick, set the prescale register value to 0 which results in a prescale value of 1.
Then we can count up to 33 to get a 1.0071ms tick.  That gives 993 for the value to count to for the 1 second tick. */

#define LFCLK_FREQ               (u32)32768
#define HFCLK_FREQ               (u32)16000000

#define RTC_COMPARE_PERIOD       (u32)33
#define RTC_TICK_PER_SECOND      (u32)993

/* Watch Dog Values */

/* TIMER
The built-in timer will provide the system tick
It is clocked from HFCLK.  To get the desired 1ms tick use a compare period of 0.001 / (1/HFCLK) or HFCLK/1000.
*/
#define TIMER_COUNT_1MS        (u32)(HFCLK_FREQ / 1000)


/***********************************************************************************************************************
!!!!! GPIO pin names
***********************************************************************************************************************/
/* Hardware Definition for nRF51422 on ADYMN-PCB-01 */

/* Port 0 bit positions */
#define P0_31_               (u32)0x80000000
#define P0_30_               (u32)0x40000000
#define P0_29_               (u32)0x20000000
#define P0_28_               (u32)0x10000000
#define P0_27_               (u32)0x08000000
#define P0_26_               (u32)0x04000000 
#define P0_25_               (u32)0x02000000
#define P0_24_               (u32)0x01000000
#define P0_23_               (u32)0x00800000
#define P0_22_               (u32)0x00400000 
#define P0_21_               (u32)0x00200000
#define P0_20_               (u32)0x00100000
#define P0_19_ARED           (u32)0x00080000
#define P0_18_ABLU           (u32)0x00040000
#define P0_17_AGRN           (u32)0x00020000
#define P0_16_MBLU           (u32)0x00010000
#define P0_15_MRED           (u32)0x00008000
#define P0_14_MGRN           (u32)0x00004000
#define P0_13_DRED           (u32)0x00002000
#define P0_12_DBLU           (u32)0x00001000
#define P0_11_DGRN           (u32)0x00000800
#define P0_10_YRED           (u32)0x00000400
#define P0_09_YBLU           (u32)0x00000200
#define P0_08_YGRN           (u32)0x00000100
#define P0_07_BUTTON0        (u32)0x00000080
#define P0_06_BUTTON1        (u32)0x00000040
#define P0_05_BUTTON2        (u32)0x00000020
#define P0_04_BUTTON3        (u32)0x00000010
#define P0_03_               (u32)0x00000008
#define P0_02_               (u32)0x00000004
#define P0_01_               (u32)0x00000002 
#define P0_00_               (u32)0x00000001 

#define P0_31_INDEX          (u32)31
#define P0_30_INDEX          (u32)30
#define P0_29_INDEX          (u32)29
#define P0_28_INDEX          (u32)28
#define P0_27_INDEX          (u32)27
#define P0_26_INDEX          (u32)26
#define P0_25_INDEX          (u32)25
#define P0_24_INDEX          (u32)24
#define P0_23_INDEX          (u32)23
#define P0_22_INDEX          (u32)22
#define P0_21_INDEX          (u32)21
#define P0_20_INDEX          (u32)20
#define P0_19_INDEX          (u32)19
#define P0_18_INDEX          (u32)18
#define P0_17_INDEX          (u32)17
#define P0_16_INDEX          (u32)16
#define P0_15_INDEX          (u32)15
#define P0_14_INDEX          (u32)14
#define P0_13_INDEX          (u32)13
#define P0_12_INDEX          (u32)12
#define P0_11_INDEX          (u32)11
#define P0_10_INDEX          (u32)10
#define P0_09_INDEX          (u32)9
#define P0_08_INDEX          (u32)8
#define P0_07_INDEX          (u32)7
#define P0_06_INDEX          (u32)6
#define P0_05_INDEX          (u32)5
#define P0_04_INDEX          (u32)4
#define P0_03_INDEX          (u32)3
#define P0_02_INDEX          (u32)2
#define P0_01_INDEX          (u32)1
#define P0_00_INDEX          (u32)0



/***********************************************************************************************************************
##### GPIO setup values
***********************************************************************************************************************/

/* Pin configuration (pg. 58) - Pins are set up using the PIN_CNF registers (one register per pin)
*/
#define P0_30_CNF      ( (GPIO_PIN_CNF_DIR_Input       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_29_CNF      ( (GPIO_PIN_CNF_DIR_Input       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_28_CNF      ( (GPIO_PIN_CNF_DIR_Input       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_27_CNF      ( (GPIO_PIN_CNF_DIR_Input       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_26_CNF      ( (GPIO_PIN_CNF_DIR_Input       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_25_CNF      ( (GPIO_PIN_CNF_DIR_Input       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_24_CNF      ( (GPIO_PIN_CNF_DIR_Input       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_23_CNF      ( (GPIO_PIN_CNF_DIR_Input       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_22_CNF      ( (GPIO_PIN_CNF_DIR_Input       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_21_CNF      ( (GPIO_PIN_CNF_DIR_Input       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_20_CNF    ( (GPIO_PIN_CNF_DIR_Input        << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Connect    << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_19_ARED_CNF      ( (GPIO_PIN_CNF_DIR_Output        << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect    << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled      << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_18_ABLU_CNF      ( (GPIO_PIN_CNF_DIR_Output        << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect    << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled      << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_17_AGRN_CNF      ( (GPIO_PIN_CNF_DIR_Output        << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect    << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_16_MBLU_CNF       ( (GPIO_PIN_CNF_DIR_Output        << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect    << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_15_MRED_CNF       ( (GPIO_PIN_CNF_DIR_Output        << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect    << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_14_MGRN_CNF      ( (GPIO_PIN_CNF_DIR_Output        << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect    << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_13_DRED_CNF      ( (GPIO_PIN_CNF_DIR_Output       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_12_DBLU_CNF      ( (GPIO_PIN_CNF_DIR_Output       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_11_DGRN_CNF      ( (GPIO_PIN_CNF_DIR_Output       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_10_YRED_CNF      ( (GPIO_PIN_CNF_DIR_Output       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_09_YBLU_CNF      ( (GPIO_PIN_CNF_DIR_Output       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_08_YGRN_CNF      ( (GPIO_PIN_CNF_DIR_Output       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_07_BUTTON0_CNF      ( (GPIO_PIN_CNF_DIR_Input       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_06_BUTTON1_CNF      ( (GPIO_PIN_CNF_DIR_Input       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_05_BUTTON2_CNF      ( (GPIO_PIN_CNF_DIR_Input       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_04_BUTTON3_CNF      ( (GPIO_PIN_CNF_DIR_Input       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_03_CNF      ( (GPIO_PIN_CNF_DIR_Input       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_02_CNF      ( (GPIO_PIN_CNF_DIR_Input       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_01_CNF      ( (GPIO_PIN_CNF_DIR_Input       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

#define P0_00_CNF      ( (GPIO_PIN_CNF_DIR_Input       << GPIO_PIN_CNF_DIR_Pos)   | \
                              (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) | \
                              (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)  | \
                              (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos) | \
                              (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos) )

                                
                                

/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File */
/*--------------------------------------------------------------------------------------------------------------------*/

#define TEMPLATE_INIT (u32)0x
/*
    31 [0] P0_31_
    30 [0] P0_30_BLU7
    29 [0] P0_29_GRN7
    28 [0] P0_28_RED2

    27 [0] P0_27_RED3
    26 [0] P0_26_LED_BLUE
    25 [0] P0_25_RED5
    24 [0] P0_24_RED7

    23 [0] P0_23_RED0
    22 [0] P0_22_RED6
    21 [0] P0_21_RED1
    20 [0] P0_20_BUTTON

    19 [0] P0_19_EXT1
    18 [0] P0_18_EXT2
    17 [0] P0_17_EXT3
    16 [0] P0_16_SCL

    15 [0] P0_15_SDA
    14 [0] P0_14_INT2
    13 [0] P0_13_BLU1
    12 [0] P0_12_BLU0

    11 [0] P0_11_GRN0
    10 [0] P0_10_GRN1
    09 [0] P0_09_BLU2
    08 [0] P0_08_GRN2

    07 [0] P0_07_BLU3
    06 [0] P0_06_GRN3
    05 [0] P0_05_BLU4
    04 [0] P0_04_GRN4

    03 [0] P0_03_BLU5
    02 [0] P0_02_GRN5
    01 [0] P0_01_BLU6
    00 [0] P0_00_GRN6
*/




#endif /* __ADYMN_H */



/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File */
/*--------------------------------------------------------------------------------------------------------------------*/
