/*
 * TFT_interface.h
 *
 *  Created on: Sep 22, 2020
 *      Author: Mohamed  Ebead
 */

#ifndef TFT_INTERFACE_H_
#define TFT_INTERFACE_H_





void TFT_voidGPIOInit     (void);
void TFT_voidInit         (void);
void TFT_voidDeInit       (void);
void TFT_voidDisplayImage (const u16* Copy_Image) ;

void TFT_voidFillDisplay (u16 Copy_u16Color) ;
void TFT_voidDrawRectangle (u8 copy_u8X ,u8 copy_u8Y , u8 copy_u16Width , u8 copy_u16Hight , u16 copy_u16Color ) ;

void TFT_voidWriteChar(s8 copy_s8Char,u8 copy_u8X,u8 copy_u8Y,u8 copy_u8Size,u16 copy_u16Color,u16 copy_u16BackColor) ;
void TFT_voidWriteString(s8 *copy_s8Text,u8 copy_u8X,u8 copy_u8Y,u8 copy_u8Size,u16 copy_u16Color,u16 u16copy_u16BackColor) ;

void TFT_voidWriteInteger(u16 Copy_u16Integer , u8 copy_u8X , u8 copy_u8Y, u8 copy_u8Size , u16 copy_u16Color, u16 copy_u16BackColor) ;


void vid_SeparateResult(u16 u16Result , u8 * u8ArrayResult) ;


/**
 *  some RGB color definitions
 */
#define TFT_COLOR_BLACK           0x0000      /*   0,   0,   0 */
#define TFT_COLOR_NAVY            0x000F      /*   0,   0, 128 */
#define TFT_COLOR_DARKGREEN       0x03E0      /*   0, 128,   0 */
#define TFT_COLOR_DARKCYAN        0x03EF      /*   0, 128, 128 */
#define TFT_COLOR_MAROON          0x7800      /* 128,   0,   0 */
#define TFT_COLOR_PURPLE          0x780F      /* 128,   0, 128 */
#define TFT_COLOR_OLIVE           0x7BE0      /* 128, 128,   0 */
#define TFT_COLOR_LIGHTGREY       0xC618      /* 192, 192, 192 */
#define TFT_COLOR_DARKGREY        0x7BEF      /* 128, 128, 128 */
#define TFT_COLOR_BLUE            0x001F      /*   0,   0, 255 */
#define TFT_COLOR_GREEN           0x07E0      /*   0, 255,   0 */
#define TFT_COLOR_CYAN            0x07FF      /*   0, 255, 255 */
#define TFT_COLOR_RED             0xF800      /* 255,   0,   0 */
#define TFT_COLOR_MAGNETA         0xF81F      /* 255,   0, 255 */
#define TFT_COLOR_YELLOW          0xFFE0      /* 255, 255,   0 */
#define TFT_COLOR_WHITE           0xFFFF      /* 255, 255, 255 */
#define TFT_COLOR_ORANGE          0xFD20      /* 255, 165,   0 */
#define TFT_COLOR_GREENYELLOW     0xAFE5      /* 173, 255,  47 */
#define TFT_COLOR_PINK            0xF81F












#endif /* TFT_INTERFACE_H_ */





