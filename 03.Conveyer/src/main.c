/*
 * main.c
 *
 *  Created on: Jan 10, 2021
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



GPIO_Handle_t Forward_IN ;
GPIO_Handle_t Reverse_IN ;
GPIO_Handle_t Stop_IN ;

GPIO_Handle_t Forward_OUT ;
GPIO_Handle_t Reverse_OUT ;
GPIO_Handle_t Stop_OUT ;



int main(void)
{

	u32 AnalogValue =0 ;

	RCC_voidInitSysClock() ;         // 16MHZ

	// configure ADC input pin
	GPIO_Handle_t POT;
	POT.pGPIOx = GPIOB;
	POT.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0 ;
	POT.GPIO_PinConfig.GPIO_PinMode   = INPUT_ANLOG   ;
	GPIO_vidInit(&POT);

	// ADC configurations
	ADC_Handle_t Potentiometer ;
	Potentiometer.pADCx = ADC1 ;
	Potentiometer.ADC_Config.Channel        = ADC_CHANNEL_NUM ;
	Potentiometer.ADC_Config.DataAlign      = ADC_ALIGNMENT ;
	Potentiometer.ADC_Config.SampleTime     = ADC_SAMPLE_TIME ;
	Potentiometer.ADC_Config.ConversionMode = ADC_CONVERSION_MODE ;
	Potentiometer.ADC_Config.ConversionNum  = ADC_CONVERSION_NUM  ;
	ADC_vidInit(&Potentiometer) ;

	Conveyer_voidInit ();



	Timer_voidGPIOInit(TIMER4_CH4);
	Timer_voidInit    (TIMER_NO_4,CHANNEL_NO_4);


	Conveyer_voidStop();

	while(1)
	{



	AnalogValue = ADC_u16ReadBlocking(&Potentiometer) ;
	AnalogValue/=52 ;          // to handle duty cycle of pwm for ARR = 79
	Conveyer_voidSetSpeed(AnalogValue);

	if (!GPIO_ReadFromInputPin(CONVEYER_IN_FORWARD_PORT,CONVEYER_IN_FORWARD_PIN))
	{
		Conveyer_voidForward((u8)AnalogValue);
	}
	else if(!GPIO_ReadFromInputPin(CONVEYER_IN_REVERSE_PORT,CONVEYER_IN_REVERSE_PIN))
	{
		Conveyer_voidReverse((u8)AnalogValue);
	}
	else if(!GPIO_ReadFromInputPin(CONVEYER_IN_STOP_PORT,CONVEYER_IN_STOP_PIN))
	{
		Conveyer_voidStop();
	}
	else
	{

	}




	}

	return 0;
}







