/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define GPIO_Pump_4_Pin GPIO_PIN_13
#define GPIO_Pump_4_GPIO_Port GPIOC
#define GPIO_Pump_3_Pin GPIO_PIN_14
#define GPIO_Pump_3_GPIO_Port GPIOC
#define heater_EN_Pin GPIO_PIN_0
#define heater_EN_GPIO_Port GPIOF
#define heater_DIR_Pin GPIO_PIN_1
#define heater_DIR_GPIO_Port GPIOF
#define LED_externe_PWM_Pin GPIO_PIN_0
#define LED_externe_PWM_GPIO_Port GPIOC
#define LED_interne_PWM_Pin GPIO_PIN_1
#define LED_interne_PWM_GPIO_Port GPIOC
#define food_PWM_3_Pin GPIO_PIN_2
#define food_PWM_3_GPIO_Port GPIOC
#define food_PWM_2_Pin GPIO_PIN_3
#define food_PWM_2_GPIO_Port GPIOC
#define food_PWM_1_Pin GPIO_PIN_0
#define food_PWM_1_GPIO_Port GPIOA
#define UART_DEBUG_TX_Pin GPIO_PIN_2
#define UART_DEBUG_TX_GPIO_Port GPIOA
#define UART_DEBUG_RX_Pin GPIO_PIN_3
#define UART_DEBUG_RX_GPIO_Port GPIOA
#define heater_STEP_Pin GPIO_PIN_4
#define heater_STEP_GPIO_Port GPIOA
#define heater_SLEEP_Pin GPIO_PIN_5
#define heater_SLEEP_GPIO_Port GPIOA
#define heater_RESET_Pin GPIO_PIN_6
#define heater_RESET_GPIO_Port GPIOA
#define ADC_pH_input_Pin GPIO_PIN_2
#define ADC_pH_input_GPIO_Port GPIOB
#define UART_Raspi_TX_Pin GPIO_PIN_10
#define UART_Raspi_TX_GPIO_Port GPIOB
#define UART_Raspi_RX_Pin GPIO_PIN_11
#define UART_Raspi_RX_GPIO_Port GPIOB
#define Water_int_1_Pin GPIO_PIN_12
#define Water_int_1_GPIO_Port GPIOB
#define Water_int_2_Pin GPIO_PIN_13
#define Water_int_2_GPIO_Port GPIOB
#define Water_int_3_Pin GPIO_PIN_14
#define Water_int_3_GPIO_Port GPIOB
#define gear_PWM_4_Pin GPIO_PIN_15
#define gear_PWM_4_GPIO_Port GPIOB
#define hatchway_PWM_2_Pin GPIO_PIN_6
#define hatchway_PWM_2_GPIO_Port GPIOC
#define gear_PWM_2_Pin GPIO_PIN_7
#define gear_PWM_2_GPIO_Port GPIOC
#define hatchway_PWM_3_Pin GPIO_PIN_8
#define hatchway_PWM_3_GPIO_Port GPIOC
#define gear_PWM_5_Pin GPIO_PIN_9
#define gear_PWM_5_GPIO_Port GPIOC
#define Screen_SDA_Pin GPIO_PIN_8
#define Screen_SDA_GPIO_Port GPIOA
#define Screen_SCL_Pin GPIO_PIN_9
#define Screen_SCL_GPIO_Port GPIOA
#define Screen_RESET_Pin GPIO_PIN_10
#define Screen_RESET_GPIO_Port GPIOA
#define GPIO_Pump_1_Pin GPIO_PIN_11
#define GPIO_Pump_1_GPIO_Port GPIOA
#define GPIO_Pump_2_Pin GPIO_PIN_12
#define GPIO_Pump_2_GPIO_Port GPIOA
#define hatchway_PWM_1_Pin GPIO_PIN_15
#define hatchway_PWM_1_GPIO_Port GPIOA
#define gear_PWM_1N_Pin GPIO_PIN_10
#define gear_PWM_1N_GPIO_Port GPIOC
#define Reverse_PWM_1_Pin GPIO_PIN_4
#define Reverse_PWM_1_GPIO_Port GPIOB
#define gear_PWM_3_Pin GPIO_PIN_5
#define gear_PWM_3_GPIO_Port GPIOB
#define Reverse_PWM_3N_Pin GPIO_PIN_6
#define Reverse_PWM_3N_GPIO_Port GPIOB
#define gear_PWM_6_Pin GPIO_PIN_7
#define gear_PWM_6_GPIO_Port GPIOB
#define Reverse_PWM_2_Pin GPIO_PIN_9
#define Reverse_PWM_2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
