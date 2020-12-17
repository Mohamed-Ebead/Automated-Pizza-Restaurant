/*
 * TFT_config.h
 *
 *  Created on: Sep 22, 2020
 *      Author: Mohamed  Ebead
 */

#ifndef TFT_CONFIG_H_
#define TFT_CONFIG_H_




#define TFT_MAX_X        128
#define TFT_MAX_Y        160
#define TFT_MAX_AREA     (TFT_MAX_X*TFT_MAX_Y)

#define TFT_CHARACTER_WIDTH  6
#define TFT_CHARACTER_HIGHT  8


#define TFT_RST_PORT     GPIOA
#define TFT_RST_PIN      GPIO_PIN_NO_4


#define TFT_A0_PORT      GPIOA
#define TFT_A0_PIN		 GPIO_PIN_NO_6

#define TFT_SDA_PORT     GPIOA
#define TFT_SDA_PIN      GPIO_PIN_NO_7         //   MOSI1


#define TFT_SCK_PORT     GPIOA
#define TFT_SCK_PIN		 GPIO_PIN_NO_5         //   SCK1
















#endif /* TFT_CONFIG_H_ */
