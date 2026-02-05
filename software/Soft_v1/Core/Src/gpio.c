/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins
     PA0   ------> S_TIM2_CH1
     PB2   ------> ADC2_IN12
     PB15   ------> S_TIM15_CH2
     PA15   ------> S_TIM8_CH1
     PC10   ------> TIM8_CH1N
     PB4   ------> S_TIM16_CH1
     PB5   ------> S_TIM17_CH1
     PB6   ------> TIM16_CH1N
     PB7   ------> S_TIM4_CH2
     PB9   ------> S_TIM4_CH4
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_Pump_4_Pin|GPIO_Pump_3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, heater_EN_Pin|heater_DIR_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, heater_STEP_Pin|heater_SLEEP_Pin|heater_RESET_Pin|Screen_RESET_Pin
                          |GPIO_Pump_1_Pin|GPIO_Pump_2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : GPIO_Pump_4_Pin GPIO_Pump_3_Pin */
  GPIO_InitStruct.Pin = GPIO_Pump_4_Pin|GPIO_Pump_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : heater_EN_Pin heater_DIR_Pin */
  GPIO_InitStruct.Pin = heater_EN_Pin|heater_DIR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : PG10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : food_PWM_1_Pin */
  GPIO_InitStruct.Pin = food_PWM_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
  HAL_GPIO_Init(food_PWM_1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : heater_STEP_Pin heater_SLEEP_Pin heater_RESET_Pin Screen_RESET_Pin
                           GPIO_Pump_1_Pin GPIO_Pump_2_Pin */
  GPIO_InitStruct.Pin = heater_STEP_Pin|heater_SLEEP_Pin|heater_RESET_Pin|Screen_RESET_Pin
                          |GPIO_Pump_1_Pin|GPIO_Pump_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : ADC_pH_input_Pin */
  GPIO_InitStruct.Pin = ADC_pH_input_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ADC_pH_input_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Water_int_1_Pin Water_int_2_Pin Water_int_3_Pin */
  GPIO_InitStruct.Pin = Water_int_1_Pin|Water_int_2_Pin|Water_int_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : gear_PWM_4_Pin */
  GPIO_InitStruct.Pin = gear_PWM_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM15;
  HAL_GPIO_Init(gear_PWM_4_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : hatchway_PWM_1_Pin */
  GPIO_InitStruct.Pin = hatchway_PWM_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM8;
  HAL_GPIO_Init(hatchway_PWM_1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : gear_PWM_1N_Pin */
  GPIO_InitStruct.Pin = gear_PWM_1N_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_TIM8;
  HAL_GPIO_Init(gear_PWM_1N_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Reverse_PWM_1_Pin Reverse_PWM_3N_Pin */
  GPIO_InitStruct.Pin = Reverse_PWM_1_Pin|Reverse_PWM_3N_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM16;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : gear_PWM_3_Pin */
  GPIO_InitStruct.Pin = gear_PWM_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF10_TIM17;
  HAL_GPIO_Init(gear_PWM_3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : gear_PWM_6_Pin Reverse_PWM_2_Pin */
  GPIO_InitStruct.Pin = gear_PWM_6_Pin|Reverse_PWM_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
