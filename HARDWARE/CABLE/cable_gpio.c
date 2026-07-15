#include "cable_gpio.h"
#include "main.h"

static GPIO_TypeDef *const cable_output_ports[CABLE_GPIO_OUTPUT_COUNT] =
{
  OUT1_GPIO_Port, OUT2_GPIO_Port
};

static const uint16_t cable_output_pins[CABLE_GPIO_OUTPUT_COUNT] =
{
  OUT1_Pin, OUT2_Pin
};

static GPIO_TypeDef *const cable_input_ports[CABLE_GPIO_INPUT_COUNT] =
{
  IN1_GPIO_Port, IN2_GPIO_Port, IN3_GPIO_Port, IN6_GPIO_Port
};

static const uint16_t cable_input_pins[CABLE_GPIO_INPUT_COUNT] =
{
  IN1_Pin, IN2_Pin, IN3_Pin, IN6_Pin
};

void CableGpio_SetOutputsHighImpedance(void)
{
  GPIO_InitTypeDef gpio_init = {0};

  gpio_init.Mode = GPIO_MODE_INPUT;
  gpio_init.Pull = GPIO_NOPULL;
  gpio_init.Speed = GPIO_SPEED_FREQ_LOW;

  for (uint8_t i = 0U; i < CABLE_GPIO_OUTPUT_COUNT; ++i)
  {
    gpio_init.Pin = cable_output_pins[i];
    HAL_GPIO_Init(cable_output_ports[i], &gpio_init);
  }
}

void CableGpio_EnableOutput(uint8_t index)
{
  GPIO_InitTypeDef gpio_init = {0};

  if (index >= CABLE_GPIO_OUTPUT_COUNT)
  {
    return;
  }

  /* 先置高输出锁存器，再切成推挽输出，避免模式切换时出现低脉冲。 */
  HAL_GPIO_WritePin(cable_output_ports[index], cable_output_pins[index], GPIO_PIN_SET);
  gpio_init.Pin = cable_output_pins[index];
  gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
  gpio_init.Pull = GPIO_NOPULL;
  gpio_init.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(cable_output_ports[index], &gpio_init);
}

void CableGpio_RestoreOutputsLow(void)
{
  GPIO_InitTypeDef gpio_init = {0};

  gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
  gpio_init.Pull = GPIO_NOPULL;
  gpio_init.Speed = GPIO_SPEED_FREQ_LOW;

  for (uint8_t i = 0U; i < CABLE_GPIO_OUTPUT_COUNT; ++i)
  {
    HAL_GPIO_WritePin(cable_output_ports[i], cable_output_pins[i], GPIO_PIN_RESET);
    gpio_init.Pin = cable_output_pins[i];
    HAL_GPIO_Init(cable_output_ports[i], &gpio_init);
  }
}

uint8_t CableGpio_IsOutputHigh(uint8_t index)
{
  if (index >= CABLE_GPIO_OUTPUT_COUNT)
  {
    return 0U;
  }

  return (HAL_GPIO_ReadPin(cable_output_ports[index], cable_output_pins[index]) == GPIO_PIN_SET) ? 1U : 0U;
}

uint8_t CableGpio_ReadInputMask(void)
{
  uint8_t input_mask = 0U;

  for (uint8_t input = 0U; input < CABLE_GPIO_INPUT_COUNT; ++input)
  {
    if (HAL_GPIO_ReadPin(cable_input_ports[input], cable_input_pins[input]) == GPIO_PIN_SET)
    {
      input_mask |= (uint8_t)(1U << input);
    }
  }

  return input_mask;
}

uint8_t CableGpio_ReadShield(void)
{
  return (HAL_GPIO_ReadPin(IN_GND_GPIO_Port, IN_GND_Pin) == GPIO_PIN_SET) ? 1U : 0U;
}
