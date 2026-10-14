/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DO_PC13_LED_Pin GPIO_PIN_13
#define DO_PC13_LED_GPIO_Port GPIOC
#define DI_BUTTON_1_Pin GPIO_PIN_14
#define DI_BUTTON_1_GPIO_Port GPIOC
#define DI_BUTTON_2_Pin GPIO_PIN_15
#define DI_BUTTON_2_GPIO_Port GPIOC
#define PWM_RGB_R_Pin GPIO_PIN_0
#define PWM_RGB_R_GPIO_Port GPIOA
#define PWM_RGB_G_Pin GPIO_PIN_1
#define PWM_RGB_G_GPIO_Port GPIOA
#define PWM_RGB_B_Pin GPIO_PIN_2
#define PWM_RGB_B_GPIO_Port GPIOA
#define AI_POT_FRENO_Pin GPIO_PIN_3
#define AI_POT_FRENO_GPIO_Port GPIOA
#define AI_POT_POTENCIA_Pin GPIO_PIN_4
#define AI_POT_POTENCIA_GPIO_Port GPIOA
#define AI_POT_CURVA_Pin GPIO_PIN_5
#define AI_POT_CURVA_GPIO_Port GPIOA
#define AI_SENSOR_HALL_GATELL_Pin GPIO_PIN_6
#define AI_SENSOR_HALL_GATELL_GPIO_Port GPIOA
#define AI_12V_PROTECTED_Pin GPIO_PIN_7
#define AI_12V_PROTECTED_GPIO_Port GPIOA
#define AI_RESERVED_1_Pin GPIO_PIN_0
#define AI_RESERVED_1_GPIO_Port GPIOB
#define DIO_RESERVED_0_Pin GPIO_PIN_1
#define DIO_RESERVED_0_GPIO_Port GPIOB
#define DI_SWITCH_1_Pin GPIO_PIN_2
#define DI_SWITCH_1_GPIO_Port GPIOB
#define DI_IS_ARC_DRIVER_Pin GPIO_PIN_10
#define DI_IS_ARC_DRIVER_GPIO_Port GPIOB
#define DO_ARC_CHANGE_Pin GPIO_PIN_12
#define DO_ARC_CHANGE_GPIO_Port GPIOB
#define DIO_RESERVED_1_Pin GPIO_PIN_13
#define DIO_RESERVED_1_GPIO_Port GPIOB
#define DO_SW_TEST_01_Pin GPIO_PIN_14
#define DO_SW_TEST_01_GPIO_Port GPIOB
#define DO_SW_TEST_02_Pin GPIO_PIN_15
#define DO_SW_TEST_02_GPIO_Port GPIOB
#define PWM_MOTOR_GAS_Pin GPIO_PIN_8
#define PWM_MOTOR_GAS_GPIO_Port GPIOA
#define PWM_MOTOR_BRAKE_Pin GPIO_PIN_9
#define PWM_MOTOR_BRAKE_GPIO_Port GPIOA
#define PWM_ARC_BRAKE_Pin GPIO_PIN_10
#define PWM_ARC_BRAKE_GPIO_Port GPIOA
#define RESERVED__SPI_CS_Pin GPIO_PIN_15
#define RESERVED__SPI_CS_GPIO_Port GPIOA
#define RESERVED__SPI_CLK_Pin GPIO_PIN_3
#define RESERVED__SPI_CLK_GPIO_Port GPIOB
#define RESERVED__SPI_MISO_Pin GPIO_PIN_4
#define RESERVED__SPI_MISO_GPIO_Port GPIOB
#define RESERVED__SPI_MOSI_Pin GPIO_PIN_5
#define RESERVED__SPI_MOSI_GPIO_Port GPIOB
#define I2C_SDC__DISPLAY_Pin GPIO_PIN_8
#define I2C_SDC__DISPLAY_GPIO_Port GPIOB
#define I2C_SDA__DISPLAY_Pin GPIO_PIN_9
#define I2C_SDA__DISPLAY_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
