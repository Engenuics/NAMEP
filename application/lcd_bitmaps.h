/*******************************************************************************
* File: lcd_bitmaps.h                                                                
* Description:
* Bitmap data for 1-bit black & white dot matrix LCD
*******************************************************************************/

#ifndef __LCDBITMAPS_H
#define __LCDBITMAPS_H

#include "configuration.h"


/*******************************************************************************
* Constants / Definitions
*******************************************************************************/
/* LCD hardware definitions */
#define LCD_PIXEL_BITS                (u8)1
#define LCD_PAGE_SIZE                 (u8)8
#define LCD_PAGES                     (u8)8
#define LCD_ROWS                      (u16)(LCD_PAGES * LCD_PAGE_SIZE)
#define LCD_COLUMNS                   (u16)128
#define LCD_CENTER_COLUMN             (u16)(LCD_COLUMNS / 2)
#define LCD_IMAGE_ROWS                LCD_ROWS
#define LCD_IMAGE_COLUMNS             (u16)(LCD_COLUMNS * LCD_PIXEL_BITS / 8)

#define LCD_IMAGE_PADDLE_ROW_SIZE         (u8)2
#define LCD_IMAGE_PADDLE_COL_SIZE         (u8)11
#define LCD_IMAGE_PADDLE_COL_BYTES        (u8)((LCD_IMAGE_PADDLE_COL_SIZE * LCD_PIXEL_BITS / 8) + 1)

#define LCD_IMAGE_BALL_ROW_SIZE           (u8)3
#define LCD_IMAGE_BALL_COL_SIZE           (u8)3
#define LCD_IMAGE_BALL_COL_BYTES          (u8)((LCD_IMAGE_BALL_COL_SIZE * LCD_PIXEL_BITS / 8) + 1)

#define LCD_IMAGE_ARROW_ROW_SIZE          (u8)12
#define LCD_IMAGE_ARROW_COL_SIZE          (u8)6
#define LCD_IMAGE_ARROW_COL_BYTES         (u8)((LCD_IMAGE_ARROW_COL_SIZE * LCD_PIXEL_BITS / 8) + 1)

/* Bitmap sizes (x = # of column pixels, y = # of row pixels) */
#define LCD_SMALL_FONT_COLUMNS        (u8)5
#define LCD_SMALL_FONT_COLUMN_BYTES   (u8)1
#define LCD_SMALL_FONT_ROWS           (u8)7
#define LCD_SMALL_FONT_SPACE          (u8)1
#define LCD_MAX_SMALL_CHARS           (u8)(LCD_COLUMNS / (LCD_SMALL_FONT_COLUMNS + LCD_SMALL_FONT_SPACE))
#define LCD_SMALL_FONT_COLSPACE       (u8)(LCD_SMALL_FONT_COLUMNS + LCD_SMALL_FONT_COLUMN_BYTES)

#define LCD_BIG_FONT_COLUMNS          (u8)10
#define LCD_BIG_FONT_COLUMN_BYTES     (u8)2
#define LCD_BIG_FONT_ROWS             (u8)14
#define LCD_BIG_FONT_SPACE            (u8)1

#define LCD_IMAGE_COL_SIZE_50PX       (u8)50
#define LCD_IMAGE_COL_BYTES_50PX      (u8)((LCD_IMAGE_COL_SIZE_50PX * LCD_PIXEL_BITS / 8) + 1)
#define LCD_IMAGE_ROW_SIZE_50PX       (u8)50
#define LCD_IMAGE_COL_SIZE_25PX       (u8)25
#define LCD_IMAGE_COL_BYTES_25PX      (u8)((LCD_IMAGE_COL_SIZE_25PX * LCD_PIXEL_BITS / 8) + 1)
#define LCD_IMAGE_ROW_SIZE_25PX       (u8)25

/*******************************************************************************
* Bookmarks
********************************************************************************
$$$$$ Small Font Character Bitmaps
%%%%% Big Font Character Bitmaps
^^^^^ Image Bitmaps
*******************************************************************************/


/*******************************************************************************
* Single Color Small Font Character Set                                    $$$$$
*******************************************************************************/


#endif /* __LCDBITMAPS_H */


