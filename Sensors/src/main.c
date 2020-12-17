/*
 * main.c
 *
 *  Created on: Dec 15, 2020
 *      Author: Mohamed  Ebead
 */


/**
 *  This is a program is Developed by Mohamed Ebead on December 2020
 *  to read analog values of temperature sensor (connected to A0) and
 *  						  a Humedity Sensor (connected to A1)  ,
 *  then displays their digital values (0...2^12(4096)) on TFT screen
 *  just need to add equations for sensors digital values to get the actual physical value
 *  depending on the sensors' data sheet . to be continue ...
 *
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "ADC_interface.h"
#include "ADC_config.h"

#include "RCC_interface.h"
#include "STK_interface.h"

#include "SPI_interface.h"
#include "TFT_interface.h"


#include "System_interface.h"




int main (void)
{
	u16 Temperature = 0 ;
	u16 Humedity    = 0 ;

	RCC_voidInitSysClock() ;

	ADC_voidInit();

	TempSensor_voidGPIOInit();
	HumeditySensor_voidGPIOInit();


	SPI1_voidInit();

	TFT_voidInit() ;

	TFT_voidFillDisplay(TFT_COLOR_CYAN) ;


	while(1)
	{
		Temperature=TempSensor_GetValue();

		Humedity=HumeditySensor_GetValue();

		TFT_voidWriteString( "Welcome"      , 0 , 0  , 3  ,TFT_COLOR_BLUE , TFT_COLOR_CYAN);

		TFT_voidWriteString( "Temperature"  , 0 , 28 , 2  ,TFT_COLOR_BLUE , TFT_COLOR_CYAN);
		TFT_voidWriteInteger(Temperature    , 0 , 50 , 2  ,TFT_COLOR_BLUE , TFT_COLOR_CYAN);

		TFT_voidWriteString( "Humedity"     , 0 , 85 , 2  ,TFT_COLOR_BLUE , TFT_COLOR_CYAN);
		TFT_voidWriteInteger(  Humedity     , 0 , 110 , 2 ,TFT_COLOR_BLUE , TFT_COLOR_CYAN);

	}


	return 0 ;
}








