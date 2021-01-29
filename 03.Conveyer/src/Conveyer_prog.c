/*
 * Conveyer_prog.c
 *
 *  Created on: Jan 27, 2021
 *      Author: Mohamed  Ebead
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "Timer_interface.h"

#include "Timer_config.h"

#include "ADC_interface.h"
#include "ADC_config.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"

#include "Conveyer_interface.h"
#include "Conveyer_config.h"
#include "Conveyer_private.h"



extern GPIO_Handle_t Forward_IN ;
extern GPIO_Handle_t Reverse_IN ;
extern GPIO_Handle_t Stop_IN ;

extern GPIO_Handle_t Forward_OUT ;
extern GPIO_Handle_t Reverse_OUT ;
extern GPIO_Handle_t Stop_OUT ;

/*--------------------------------------------------------------------------------------------*/
/**
 *
 */
void Conveyer_voidInit      (void)
{
	// CONFIGURE PORT
	Forward_IN.pGPIOx=CONVEYER_IN_FORWARD_PORT;
	Reverse_IN.pGPIOx=CONVEYER_IN_REVERSE_PORT;
	Stop_IN.pGPIOx   =CONVEYER_IN_STOP_PORT;

	Forward_OUT.pGPIOx=CONVEYER_OUT_FORWARD_PORT;
	Reverse_OUT.pGPIOx=CONVEYER_OUT_REVERSE_PORT;
	Stop_OUT.pGPIOx   =CONVEYER_OUT_STOP_PORT;

	// CONFIGURE PIN
	Forward_IN.GPIO_PinConfig.GPIO_PinNumber=CONVEYER_IN_FORWARD_PIN;
	Reverse_IN.GPIO_PinConfig.GPIO_PinNumber=CONVEYER_IN_REVERSE_PIN;
	Stop_IN.GPIO_PinConfig.GPIO_PinNumber=CONVEYER_IN_STOP_PIN;

	Forward_OUT.GPIO_PinConfig.GPIO_PinNumber=CONVEYER_OUT_FORWARD_PIN;
	Reverse_OUT.GPIO_PinConfig.GPIO_PinNumber=CONVEYER_OUT_REVERSE_PIN;
	Stop_OUT.GPIO_PinConfig.GPIO_PinNumber=CONVEYER_OUT_STOP_PIN;


	// CONFIGURE MODE
	Forward_IN.GPIO_PinConfig.GPIO_PinMode=INPUT_PULLUP_PULLDOWN;
	Reverse_IN.GPIO_PinConfig.GPIO_PinMode=INPUT_PULLUP_PULLDOWN;
	Stop_IN.GPIO_PinConfig.GPIO_PinMode=INPUT_PULLUP_PULLDOWN;

	Forward_OUT.GPIO_PinConfig.GPIO_PinMode=OUTPUT_10MHZ_PP;
	Reverse_OUT.GPIO_PinConfig.GPIO_PinMode=OUTPUT_10MHZ_PP;
	Stop_OUT.GPIO_PinConfig.GPIO_PinMode=OUTPUT_10MHZ_PP;

	// PULLED UP INPUTS
	GPIO_vidInit(&Forward_IN);
	GPIO_WriteToOutputPin(CONVEYER_IN_FORWARD_PORT ,CONVEYER_IN_FORWARD_PIN ,GPIO_PIN_SET ); // PULL UP

	GPIO_vidInit(&Reverse_IN);
	GPIO_WriteToOutputPin(CONVEYER_IN_REVERSE_PORT ,CONVEYER_IN_REVERSE_PIN ,GPIO_PIN_SET ); // PULL UP

	GPIO_vidInit(&Stop_IN);
	GPIO_WriteToOutputPin(CONVEYER_IN_STOP_PORT ,CONVEYER_IN_STOP_PIN ,GPIO_PIN_SET ); // PULL UP


	// ACTIVE LOW OUTPUTS
	GPIO_vidInit(&Stop_OUT);
	GPIO_WriteToOutputPin(CONVEYER_OUT_STOP_PORT ,CONVEYER_OUT_STOP_PIN ,GPIO_PIN_RESET ); // ACTIVATE STOP

	GPIO_vidInit(&Forward_OUT);
	GPIO_WriteToOutputPin(CONVEYER_OUT_FORWARD_PORT ,CONVEYER_OUT_FORWARD_PIN ,GPIO_PIN_SET ); // DEACTIVATE FORWARD

	GPIO_vidInit(&Reverse_OUT);
	GPIO_WriteToOutputPin(CONVEYER_OUT_REVERSE_PORT ,CONVEYER_OUT_REVERSE_PIN ,GPIO_PIN_SET ); // DEACTIVATE REVERSE


}

/*--------------------------------------------------------------------------------------------*/
/**
 *
 */
void Conveyer_voidStop      (void)
{
	GPIO_WriteToOutputPin(CONVEYER_OUT_FORWARD_PORT ,CONVEYER_OUT_FORWARD_PIN ,GPIO_PIN_SET ); // DEACTIVATE FORWARD
	GPIO_WriteToOutputPin(CONVEYER_OUT_REVERSE_PORT ,CONVEYER_OUT_REVERSE_PIN ,GPIO_PIN_SET ); // DEACTIVATE REVERSE
	GPIO_WriteToOutputPin(CONVEYER_OUT_STOP_PORT ,CONVEYER_OUT_STOP_PIN ,GPIO_PIN_RESET ); // ACTIVATE STOP

}

/*--------------------------------------------------------------------------------------------*/
/**
 *
 */
void Conveyer_voidForward   (u8 Copy_u8Speed)
{
	GPIO_WriteToOutputPin(CONVEYER_OUT_REVERSE_PORT ,CONVEYER_OUT_REVERSE_PIN ,GPIO_PIN_SET ); // DEACTIVATE REVERSE
	GPIO_WriteToOutputPin(CONVEYER_OUT_STOP_PORT ,CONVEYER_OUT_STOP_PIN ,GPIO_PIN_SET ); // DEACTIVATE STOP

	Conveyer_voidSetSpeed(Copy_u8Speed);
	GPIO_WriteToOutputPin(CONVEYER_OUT_FORWARD_PORT ,CONVEYER_OUT_FORWARD_PIN ,GPIO_PIN_RESET ); // ACTIVATE FORWARD

}

/*--------------------------------------------------------------------------------------------*/
/**
 *
 */
void Conveyer_voidReverse   (u8 Copy_u8Speed)
{
	GPIO_WriteToOutputPin(CONVEYER_OUT_FORWARD_PORT ,CONVEYER_OUT_FORWARD_PIN ,GPIO_PIN_SET ); // DEACTIVATE FORWARD
	GPIO_WriteToOutputPin(CONVEYER_OUT_STOP_PORT ,CONVEYER_OUT_STOP_PIN ,GPIO_PIN_SET ); // DEACTIVATE STOP

	Conveyer_voidSetSpeed(Copy_u8Speed);
	GPIO_WriteToOutputPin(CONVEYER_OUT_REVERSE_PORT ,CONVEYER_OUT_REVERSE_PIN ,GPIO_PIN_RESET ); // ACTIVATE REVERSE

}

/*--------------------------------------------------------------------------------------------*/
/**
 *
 * @param Copy_u8Speed
 */
void Conveyer_voidSetSpeed  (u8 Copy_u8Speed)
{
	Timer_SetDutyCycle(TIMER4_CH4 , Copy_u8Speed) ;

}

/*--------------------------------------------------------------------------------------------*/












