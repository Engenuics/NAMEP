/**********************************************************************************************************************
File: configuration.h      

Description:
Main configuration header file for project.  This file bridges many of the generic features of the 
firmware to the specific features of the design. The definitions should be updated
to match the target hardware.  
 
Bookmarks:
!!!!! External module peripheral assignments
@@@@@ GPIO board-specific parameters
##### Communication peripheral board-specific parameters


***********************************************************************************************************************/

#ifndef __CONFIG_H
#define __CONFIG_H

/**********************************************************************************************************************
Runtime Switches
***********************************************************************************************************************/

/**********************************************************************************************************************
Type Definitions
**********************************************************************************************************************/


/**********************************************************************************************************************
Includes


#include <stdint.h>
#include <stdbool.h>
#include "nrf.h"
#include "system_nrf51.h"

***********************************************************************************************************************/
/* Standard C and nRF SoC/SDK headers */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "nordic_common.h"
#include "nrf.h"
#include "nrf_assert.h"
#include "nrf_delay.h"
#include "nrf_error.h"
#include "nrf_soc.h"
#include "nrf_sdm.h"

#include "ant_interface.h"
#include "ant_parameters.h"
#include "ant_error.h"
#include "app_error.h"
//#include "appconfig.h"
//#include "boardconfig.h"
//#include "command.h"
//#include "global.h"
//#include "serial.h"
//#include "system.h"
//#include "ant_boot_settings_api.h"
//#include "soc_integration.h"

/* MPG nRF51422 implementation headers */
#include "interrupts.h"
#include "main.h"
#include "typedefs.h"
#include "utilities.h"
#include "i2c_master.h"
#include "lcd_bitmaps.h"

#include "abbcn-ehdw-01.h"

/* Driver header files */
#include "leds_abbcn.h" 

/* Application header files */


/**********************************************************************************************************************
!!!!! External device peripheral assignments
***********************************************************************************************************************/
#define TWI_MASTER_CONFIG_CLOCK_PIN_NUMBER  P0_16_INDEX
#define TWI_MASTER_CONFIG_DATA_PIN_NUMBER   P0_15_INDEX


#endif /* __CONFIG_H */

/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File */
/*--------------------------------------------------------------------------------------------------------------------*/

