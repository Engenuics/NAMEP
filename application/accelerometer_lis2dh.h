/**********************************************************************************************************************
File: accelerometer_lis2di.h                                                                

Description:
Header file for accelerometer_lis2di.c source.

The default values in this file configure the accelerometer to operate in "Low power" mode (8 bit resolution) at 
a read frequency of 100Hz which should result in operating current consumption of 10uA.

Notes:
Allow 5ms device startup
**********************************************************************************************************************/

#ifndef __TEMPLATE_H
#define __TEMPLATE_H

/**********************************************************************************************************************
Type Definitions
**********************************************************************************************************************/


/**********************************************************************************************************************
Constants / Definitions
**********************************************************************************************************************/

#define CTRL_REG1_INIT (u8)0x
/*
    07 [0] 
    06 [0] 
    05 [0] 
    04 [0] 

    03 [0] LPen Normal mode (10 bit output)
    02 [0] 
    01 [0] 
    00 [0] 
*/

#define CTRL_REG4_INIT (u8)0x
/*
    07 [0] 
    06 [0] 
    05 [0] 
    04 [0] 

    03 [0] HR Normal mode (10 bit output)
    02 [0] 
    01 [0] 
    00 [0] 
*/

/* Sleep to wake / Return to sleep mode register settings (if used) */
#define ACT_THS_INIT (u8)0x
/*
    07 [0] Threshold accleration value
    06 [0] 
    05 [0] 
    04 [0] 

    03 [0] 
    02 [0] 
    01 [0] 
    00 [0] 
*/

#define ACT_DUR_INIT (u8)0x
/*
    07 [0] Threshold accleration value duration
    06 [0] 
    05 [0] 
    04 [0] 

    03 [0] 
    02 [0] 
    01 [0] 
    00 [0] 
*/

#define TEMPLATE_INIT (u32)0x
/*
    31 [0] 
    30 [0] 
    29 [0] 
    28 [0] 

    27 [0] 
    26 [0] 
    25 [0] 
    24 [0] 

    23 [0] 
    22 [0] 
    21 [0] 
    20 [0] 

    19 [0] 
    18 [0] 
    17 [0] 
    16 [0] 

    15 [0] 
    14 [0] 
    13 [0] 
    12 [0] 

    11 [0] 
    10 [0] 
    09 [0] 
    08 [0] 

    07 [0] 
    06 [0] 
    05 [0] 
    04 [0] 

    03 [0] 
    02 [0] 
    01 [0] 
    00 [0] 
*/

/* I�C Addresses */
#define LIS2DH_READ     (u8)0x33      /* Read address (assumes SDO tied high) */
#define LIS2DH_WRITE    (u8)0x32      /* Write address (assumes SDO tied high) */

#define AUTO_INCREMENT  (u8)0x80      /* OR this into a sub address to auto increment the sub address after an access */

/* Register definitions */
#define STATUS_REG_AUX  (u8)0x07
#define _STATUS_REG_AUX_TOR (u8)0x40   /* Temperature data overrun */
#define _STATUS_REG_AUX_TDA (u8)0x04   /* New temperature data availabble */

#define OUT_TEMP_L      (u8)0x0C
#define OUT_TEMP_H      (u8)0x0D

#define INT_COUNTER_REG (u8)0x0E

#define WHO_AM_I        (u8)0x0F
#define I_AM            (u8)0x33

#define TEMP_CFG_REG             (u8)0x1F
#define _TEMP_CFG_REG_TEMP_EN0   (u8)0x40  /* Set both to enable temperature sensor */
#define _TEMP_CFG_REG_TEMP_EN1   (u8)0x80

#define CTRL_REG1        (u8)0x20
#define _CTRL_REG1_ODR0  (u8)0x00          /* Power down mode */
#define _CTRL_REG1_ODR1  (u8)0x01          /* HR / normal / Low power mode (1 Hz) */
#define _CTRL_REG1_ODR2  (u8)0x02          /* HR / normal / Low power mode (10 Hz) */
#define _CTRL_REG1_ODR3  (u8)0x03          /* HR / normal / Low power mode (25 Hz) */
#define _CTRL_REG1_ODR4  (u8)0x04          /* HR / normal / Low power mode (50 Hz) */
#define _CTRL_REG1_ODR5  (u8)0x05          /* HR / normal / Low power mode (100 Hz) */
#define _CTRL_REG1_ODR6  (u8)0x06          /* HR / normal / Low power mode (200 Hz) */
#define _CTRL_REG1_ODR7  (u8)0x07          /* HR / normal / Low power mode (400 Hz) */
#define _CTRL_REG1_ODR8  (u8)0x08          /* Low power mode (1620 Hz) */
#define _CTRL_REG1_ODR9  (u8)0x09          /* HR / normal (1344 Hz); Low power mode (5376 Hz) */


#define CTRL_REG1_INIT  (u8)0x57
/*
    07 [0] ODR HR / normal / Low power mode (100 Hz)
    06 [1] "
    05 [0] "
    04 [1] "

    03 [0] LPEN Normal mode
    02 [1] ZEN Z-axis enabled
    01 [1] YEN Y-axis enabled
    00 [1] ZEN X-axis enabled
*/
  


#define CTRL_REG2       (u8)0x21
/*
    07 [0] 
    06 [0] 
    05 [0] 
    04 [0] 

    03 [0] 
    02 [0] 
    01 [0] 
    00 [0] 
*/

#define CTRL_REG3       (u8)0x22
#define CTRL_REG4       (u8)0x23
#define CTRL_REG5       (u8)0x24
#define CTRL_REG6       (u8)0x25

#define REFERENCE       (u8)0x26
#define STATUS_REG2     (u8)0x27

#define OUT_X_L         (u8)0x28
#define OUT_X_H         (u8)0x29
#define OUT_Y_L         (u8)0x2A
#define OUT_Y_H         (u8)0x2B
#define OUT_Z_L         (u8)0x2C
#define OUT_Z_H         (u8)0x2D

#define FIFO_CTRL_REG   (u8)0x2E
#define FIFO_SRC_REG    (u8)0x2F

#define INT1_CFG        (u8)0x30
#define INT1_SOURCE     (u8)0x31
#define INT1_THS        (u8)0x32
#define INT1_DURATION   (u8)0x33

#define INT2_CFG        (u8)0x34
#define INT2_SOURCE     (u8)0x35
#define INT2_THS        (u8)0x36
#define INT2_DURATION   (u8)0x37

#define CLICK_CFG       (u8)0x38
#define CLICK_SRC       (u8)0x39
#define CLICK_THS       (u8)0x3A

#define TIME_LIMIT      (u8)0x3B
#define TIME_LATENCY    (u8)0x3C
#define TIME_WINDOW     (u8)0x3D

#define ACT_THS         (u8)0x3E
#define ACT_DUR         (u8)0x3F



/**********************************************************************************************************************
Function Declarations
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/
void TemplateInitialize(void);


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/



#endif /* __TEMPLATE_H */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
