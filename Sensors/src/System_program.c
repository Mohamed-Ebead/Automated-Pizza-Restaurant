/*
 *
 *  Created on: Dec 15, 2020
 *      Author: Mohamed  Ebead
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_private.h"

#include "RCC_interface.h"
#include "STK_interface.h"
#include "SPI_interface.h"
#include "TFT_interface.h"

#include "System_interface.h"
#include "System_config.h"
#include "System_private.h"





/**----------------------------------------------------------------------------------------------------*/


/**----------------------------------------------------------------------------------------------------*/
void TempSensor_voidGPIOInit    (void)
{
	// configure ADC input pin as A0
	GPIO_Handle_t TempSensor_GPIO;
	TempSensor_GPIO.pGPIOx = GPIOA;
	TempSensor_GPIO.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0 ;
	TempSensor_GPIO.GPIO_PinConfig.GPIO_PinMode   = INPUT_ANLOG   ;
	GPIO_vidInit(&TempSensor_GPIO);

}



/**----------------------------------------------------------------------------------------------------*/

void HumeditySensor_voidGPIOInit   (void)
{
	// configure ADC input pin as A1
	GPIO_Handle_t HumeditySensor_GPIO;
	HumeditySensor_GPIO.pGPIOx = GPIOA;
	HumeditySensor_GPIO.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
	HumeditySensor_GPIO.GPIO_PinConfig.GPIO_PinMode   = INPUT_ANLOG   ;
	GPIO_vidInit(&HumeditySensor_GPIO);

}

/**----------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------------*/


void TempSensor_Start    (void)
{
	// right alignment
	ADC1->CR2  &= ~(1<<CR2_ALIGN_BIT) ;
	ADC1->SMPR2 =  ( (ADC_SAMPLE_28_CYCLES) << 0 )   ;  // channel 0 ADC0 A0
	ADC1->SQR3  = 0 ; // channel number 0 for first conversion in regular sequence
	ADC1->CR2 &= ~(1<<CR2_CONT_BIT) ; // single mode

}

/*-------------------------------------------------------------------------------------------------*/

u32 TempSensor_GetValue (void)
{

	TempSensor_Start();

	return (u32)(ADC_u16ReadBlocking());

}

/*-------------------------------------------------------------------------------------------------*/

void HumeditySensor_Start    (void)
{
	// right alignment
	ADC1->CR2  &= ~(1<<CR2_ALIGN_BIT) ;
	ADC1->SMPR2 =  ( (ADC_SAMPLE_28_CYCLES) << 3 )   ;  // channel 1 ADC1 A1
	ADC1->SQR3  = 1 ; // channel number 1 for first conversion in regular sequence (Overwrite channel 0 for test)
	ADC1->CR2 &= ~(1<<CR2_CONT_BIT) ; // single mode
}

/*-------------------------------------------------------------------------------------------------*/

u32 HumeditySensor_GetValue (void)
{
	HumeditySensor_Start ();
	return (u32)(ADC_u16ReadBlocking());

}

/*-------------------------------------------------------------------------------------------------*/


/**----------------------------------------------------------------------------------------------------*/


