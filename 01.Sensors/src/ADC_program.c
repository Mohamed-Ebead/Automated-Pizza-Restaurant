/*
 *
 *  Created on: Dec 15, 2020
 *      Author: Mohamed  Ebead
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_private.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"




/*-------------------------------------------------------------------------------------------------*/
/**
 *
 * @param pADC_Handle
 */

void ADC_voidInit (void )
{

	RCC_voidEnableClock(RCC_ADC_BUS , RCC_ADC1) ;

	// Wake up the ADC from Power Down state
	ADC1->CR2 |= (1<<CR2_ADON_BIT) ;

	// reset calibration registers
	ADC1->CR2 |= (1<<CR2_RSTCAL_BIT) ;


	// wait for calibration register initialized
	while ( ( GET_BIT( (ADC1->CR2),CR2_RSTCAL_BIT ) ) ) ;

	 // enable calibration
	ADC1->CR2 |= (1<<CR2_CAL_BIT) ;

	// wait for calibration completed
	while ( ( GET_BIT( (ADC1->CR2),CR2_CAL_BIT ) ) ) ;
}




/*-------------------------------------------------------------------------------------------------*/
/**
 *
 * @param pADC_Handle
 * @return
 */
u32 ADC_u16ReadBlocking    ( void )
{

	u32 Local_u32Digital_Value  = 0 ;
	// Start conversion
	//pADC_Handle->pADCx->CR2 &= ~(1<<CR2_ADON_BIT) ;


	// Start conversion
	ADC1->CR2 |= (1<<CR2_ADON_BIT) ;
	// Start conversion
	ADC1->CR2 |= (1<<CR2_ADON_BIT) ;

	// wait for the End of conversion
	while ( !( GET_BIT( (ADC1->SR),SR_EOC_BIT ) ) ) ;

	// Store the value after conversion and clear EOC bit by software or by reading the ADC_DR.
	Local_u32Digital_Value = ADC1->DR ;

	ADC1->SR &= ~(1<<SR_EOC_BIT) ;

	// Clear Regular channel Start flag
	ADC1->SR &= ~(1<<SR_STRT_BIT) ;


	return Local_u32Digital_Value ;
}

/*-------------------------------------------------------------------------------------------------*/







