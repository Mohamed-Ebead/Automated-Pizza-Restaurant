/*
 * TFT_private.h
 *
 *  Created on: Sep 22, 2020
 *      Author: Mohamed  Ebead
 */

#ifndef TFT_PRIVATE_H_
#define TFT_PRIVATE_H_



static void TFT_voidWriteCommand(u8 Copy_u8Command);
static void TFT_voidWriteData   (u8 Copy_u8Data);
static void TFT_voidSetArea (u8 X1 ,u8 X2 , u8 Y1 , u8 Y2 ) ;
static void TFT_voidSetColor(u16 copy_u16Color) ;
static void TFT_voidDrawPixel (u8 copy_u8X , u8 copy_u8Y , u16 copy_u16Colour) ;



#define TFT_COMMAND_SLPOUT      0x11     // sleep out
#define TFT_COMMAND_COLMOD      0x3A     // color mode
#define TFT_COMMAND_DISPON      0x29     // display on
#define TFT_COMMAND_CASET       0x2A     // column address set
#define TFT_COMMAND_RASET       0x2B     // row address set
#define TFT_COMMAND_RAMWR       0x2C     // ram write



#endif /* TFT_PRIVATE_H_ */
