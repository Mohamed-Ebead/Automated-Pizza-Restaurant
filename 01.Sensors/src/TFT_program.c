/*
 * TFT_program.c
 *
 *  Created on: Sep 22, 2020
 *      Author: Mohamed  Ebead
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"

#include "STK_interface.h"
#include "SPI_interface.h"

#include "TFT_interface.h"
#include "TFT_config.h"
#include "TFT_private.h"
#include "TFT_font.h"



/**-------------------------------------------------------------------------------------------------------**/
/**
 *
 */
void TFT_voidGPIOInit     (void)
{
	GPIO_Handle_t TFT_RST  ;
	TFT_RST.pGPIOx = TFT_RST_PORT ;
	TFT_RST.GPIO_PinConfig.GPIO_PinNumber = TFT_RST_PIN ;
	TFT_RST.GPIO_PinConfig.GPIO_PinMode   = OUTPUT_2MHZ_PP ;
	GPIO_vidInit(&TFT_RST) ;

	GPIO_Handle_t TFT_A0  ;
	TFT_A0.pGPIOx = TFT_A0_PORT ;
	TFT_A0.GPIO_PinConfig.GPIO_PinNumber = TFT_A0_PIN ;
	TFT_A0.GPIO_PinConfig.GPIO_PinMode   = OUTPUT_2MHZ_PP ;
	GPIO_vidInit(&TFT_A0) ;

	GPIO_Handle_t TFT_SDA  ;
	TFT_SDA.pGPIOx = TFT_SDA_PORT ;
	TFT_SDA.GPIO_PinConfig.GPIO_PinNumber = TFT_SDA_PIN ;
	TFT_SDA.GPIO_PinConfig.GPIO_PinMode   = OUTPUT_10MHZ_AFPP ;
	GPIO_vidInit(&TFT_SDA) ;

	GPIO_Handle_t TFT_SCK  ;
	TFT_SCK.pGPIOx = TFT_SCK_PORT ;
	TFT_SCK.GPIO_PinConfig.GPIO_PinNumber = TFT_SCK_PIN ;
	TFT_SCK.GPIO_PinConfig.GPIO_PinMode   = OUTPUT_10MHZ_AFPP ;
	GPIO_vidInit(&TFT_SCK) ;


}

/**-------------------------------------------------------------------------------------------------------**/
/**
 *
 */
void TFT_voidInit         (void)
{
	TFT_voidGPIOInit();

	/* Reset Pulse */
	GPIO_WriteToOutputPin(TFT_RST_PORT,TFT_RST_PIN,GPIO_PIN_SET);
	STK_voidSetBusyWait(100);
	GPIO_WriteToOutputPin(TFT_RST_PORT,TFT_RST_PIN,GPIO_PIN_RESET);
	STK_voidSetBusyWait(1);
	GPIO_WriteToOutputPin(TFT_RST_PORT,TFT_RST_PIN,GPIO_PIN_SET);
	STK_voidSetBusyWait(100);
	GPIO_WriteToOutputPin(TFT_RST_PORT,TFT_RST_PIN,GPIO_PIN_RESET);
	STK_voidSetBusyWait(100);
	GPIO_WriteToOutputPin(TFT_RST_PORT,TFT_RST_PIN,GPIO_PIN_SET);
	STK_voidSetBusyWait(120000);

	/* Sleep Out Command */
	TFT_voidWriteCommand(TFT_COMMAND_SLPOUT);

	/* Wait 150 ms */
	STK_voidSetBusyWait(150000);

	/* Color Mode Command */
	TFT_voidWriteCommand(TFT_COMMAND_COLMOD);
	TFT_voidWriteData   (0x05);

	/* Display On Command */
	TFT_voidWriteCommand(TFT_COMMAND_DISPON);

}

/**-------------------------------------------------------------------------------------------------------**/
/**
 *
 */
void TFT_voidDeInit       (void)
{

}

/**-------------------------------------------------------------------------------------------------------**/
/**
 *
 * @param Copy_Image
 */
void TFT_voidDisplayImage (const u16* Copy_Image)
{
	u16 Local_u16Counter;
	u8  Local_u8Data;

	TFT_voidSetArea(0,TFT_MAX_X,0,TFT_MAX_Y) ;

	for(Local_u16Counter = 0; Local_u16Counter< TFT_MAX_AREA ;Local_u16Counter++)
	{
		/* Write the high byte */
		Local_u8Data = Copy_Image[Local_u16Counter] >> 8;
		TFT_voidWriteData(Local_u8Data);

		/* Write the low byte */
		Local_u8Data = Copy_Image[Local_u16Counter] & 0x00ff;
		TFT_voidWriteData(Local_u8Data);
	}


}

/**-------------------------------------------------------------------------------------------------------**/
/**
 *
 * @param Copy_u16Color
 */
void TFT_voidFillDisplay (u16 Copy_u16Color)
{
	TFT_voidDrawRectangle(0,0,TFT_MAX_X,TFT_MAX_Y,Copy_u16Color) ;
}
/**-------------------------------------------------------------------------------------------------------**/
/**
 *
 * @param Copy_u16Color
 */
void TFT_voidDrawRectangle (u8 copy_u8X ,u8 copy_u8Y , u8 copy_u16Width , u8 copy_u16Hight , u16 copy_u16Color )
{
	u16 loacal_u8EndX = copy_u8X + copy_u16Width - 1;
	u16 loacal_u8EndY = copy_u8Y + copy_u16Hight - 1;

	/* Set area of addresses */
	TFT_voidSetArea(copy_u8X ,loacal_u8EndX,copy_u8Y ,loacal_u8EndY );

	/* Draw the Rectangle*/
	for (u16 i = 0 ; i < (copy_u16Width *copy_u16Hight ) ; i++)
	{
		TFT_voidSetColor(copy_u16Color);
	}
}
/**-------------------------------------------------------------------------------------------------------**/

void TFT_voidWriteChar(s8 copy_s8Char , u8 copy_u8X , u8 copy_u8Y, u8 copy_u8Size , u16 copy_u16Color , u16 copy_u16BackColor)
{
	/* Get array index */
	u8 local_u8CharIndex = 0 ;
	u8 Local_u8X = 0 ;
	u8 Local_u8Y = 0 ;
	if (( copy_s8Char >= ' ' ))
	{
		local_u8CharIndex = copy_s8Char - 32 ;
	}

	/* Background */
	TFT_voidDrawRectangle( copy_u8X, copy_u8Y ,copy_u8Size*TFT_CHARACTER_WIDTH ,copy_u8Size*TFT_CHARACTER_HIGHT ,copy_u16BackColor);

	for (Local_u8X = 0; Local_u8X <TFT_CHARACTER_WIDTH ; Local_u8X++ )
	{
		for (Local_u8Y = 0 ; Local_u8Y <TFT_CHARACTER_HIGHT ; Local_u8Y++)
		{
			if (u8_TFT_Font[local_u8CharIndex][Local_u8X] & (1 << Local_u8Y))
			{
				if (copy_u8Size == 1)
				{
					TFT_voidDrawPixel(copy_u8X+Local_u8X , copy_u8Y+Local_u8Y , copy_u16Color);
				}
				else
				{
					u8 Local_u8X1 = copy_u8X+(Local_u8X*copy_u8Size) ;
					u8 Local_u8Y1 = copy_u8Y+(Local_u8Y*copy_u8Size) ;
					TFT_voidDrawRectangle( Local_u8X1, Local_u8Y1 ,copy_u8Size ,copy_u8Size ,copy_u16Color);
				}
			}
		}
	}
}

/**-------------------------------------------------------------------------------------------------------**/

void TFT_voidWriteString(s8 *copy_s8Text , u8 copy_u8X , u8 copy_u8Y, u8 copy_u8Size , u16 copy_u16Color, u16 copy_u16BackColor)
{
	while (*copy_s8Text)
	{
		TFT_voidWriteChar(*copy_s8Text , copy_u8X ,copy_u8Y ,copy_u8Size ,copy_u16Color,copy_u16BackColor );
		copy_u8X += (copy_u8Size *TFT_CHARACTER_WIDTH)  ;
		copy_s8Text++;
	}
}

/**-------------------------------------------------------------------------------------------------------**/

/**
 *
 * @param Copy_u8Command
 */
static void TFT_voidWriteCommand(u8 Copy_u8Command)
{
	u8 Local_u8Command = Copy_u8Command ;

	/* Set A0 Pin to Low */
	GPIO_WriteToOutputPin(TFT_A0_PORT,TFT_A0_PIN,GPIO_PIN_RESET);

	/* Send Command over SPI */
	SPI_SendDataSynch(SPI1,&Local_u8Command,1);

}
/**-------------------------------------------------------------------------------------------------------**/

/**
 *
 * @param Copy_u8Data
 */
static void TFT_voidWriteData   (u8 Copy_u8Data)
{
	u8 Local_u8Data = Copy_u8Data;

	/* Set A0 Pin to High */
	GPIO_WriteToOutputPin(TFT_A0_PORT,TFT_A0_PIN,GPIO_PIN_SET);

	/* Send data over SPI */
	SPI_SendDataSynch(SPI1,&Local_u8Data,1);


}

/**-------------------------------------------------------------------------------------------------------**/
static void TFT_voidSetArea (u8 X1 ,u8 X2 , u8 Y1 , u8 Y2 )
{
	if ( (X2>X1) && (Y2>Y1) && (X2<=TFT_MAX_X) && (Y2<=TFT_MAX_Y) )
	{
		/* Set X Address */
		TFT_voidWriteCommand(TFT_COMMAND_CASET);
		// Start point of x
		TFT_voidWriteData(0);
		TFT_voidWriteData(X1);
		// End point of x
		TFT_voidWriteData(0);
		TFT_voidWriteData(X2);

		/* Set Y Address */
		TFT_voidWriteCommand(TFT_COMMAND_RASET);
		// Start point of y
		TFT_voidWriteData(0);
		TFT_voidWriteData(Y1);
		// End point of y
		TFT_voidWriteData(0);
		TFT_voidWriteData(Y2);

		/* RAM Write */
		TFT_voidWriteCommand(TFT_COMMAND_RAMWR);
	}
}

/**-------------------------------------------------------------------------------------------------------**/
static void TFT_voidSetColor(u16 copy_u16Color)
{
	/* Write pixel */
	TFT_voidWriteData(copy_u16Color >> 8);  // high byte
	TFT_voidWriteData(copy_u16Color & 0xff);  // low byte

}

/**-------------------------------------------------------------------------------------------------------**/

static void TFT_voidDrawPixel (u8 copy_u8X , u8 copy_u8Y , u16 copy_u16Colour)
{
	if ( (copy_u8X < TFT_MAX_X ) && (copy_u8Y < TFT_MAX_Y )){

		/* Set address of the pixel */
		TFT_voidSetArea(copy_u8X  , copy_u8X+1 , copy_u8Y , copy_u8Y+1);

		/* Write pixel colour */
		TFT_voidSetColor(copy_u16Colour);
	}
}

/**-------------------------------------------------------------------------------------------------------**/

void TFT_voidWriteInteger(u16 Copy_u16Integer , u8 copy_u8X , u8 copy_u8Y, u8 copy_u8Size , u16 copy_u16Color, u16 copy_u16BackColor)
{
	u8 ArrayResult[5] = {0} ;
	vid_SeparateResult(Copy_u16Integer , ArrayResult) ;

	for ( u8 i=0; i <5 ; i++ )
	{
		TFT_voidWriteChar(ArrayResult[i] , copy_u8X ,copy_u8Y ,copy_u8Size ,copy_u16Color,copy_u16BackColor );
		copy_u8X += (copy_u8Size *TFT_CHARACTER_WIDTH)  ;
	}
}

void vid_SeparateResult(u16 u16Result , u8 * u8ArrayResult)
{

	u8ArrayResult[0]= ( (u16Result / 1000) % 10 ) + 48 ;
	u8ArrayResult[1]= ( (u16Result / 100) % 10 ) + 48 ;
	u8ArrayResult[2]= ( (u16Result / 10) % 10 ) + 48 ;
	u8ArrayResult[3]=   (u16Result  % 10 ) + 48 ;

}


