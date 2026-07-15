/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
static volatile uint8_t appReady = 0U;

/* USER CODE END Variables */
/* Definitions for SamplingTask */
osThreadId_t SamplingTaskHandle;
const osThreadAttr_t SamplingTask_attributes = {
  .name = "SamplingTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for MeasurementTask */
osThreadId_t MeasurementTaskHandle;
const osThreadAttr_t MeasurementTask_attributes = {
  .name = "MeasurementTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for UiTask */
osThreadId_t UiTaskHandle;
const osThreadAttr_t UiTask_attributes = {
  .name = "UiTask",
  .stack_size = 768 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for VofaTask */
osThreadId_t VofaTaskHandle;
const osThreadAttr_t VofaTask_attributes = {
  .name = "VofaTask",
  .stack_size = 384 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for StorageTask */
osThreadId_t StorageTaskHandle;
const osThreadAttr_t StorageTask_attributes = {
  .name = "StorageTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
extern void App_Init(void);
extern void App_SamplingTaskStep(void);
extern void App_MeasurementTaskStep(void);
extern void App_UiTaskStep(void);
extern void App_VofaTaskStep(void);
extern void App_StorageTaskStep(void);

/* USER CODE END FunctionPrototypes */

void StartSamplingTask(void *argument);
void StartMeasurementTask(void *argument);
void StartUiTask(void *argument);
void StartVofaTask(void *argument);
void StartStorageTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of SamplingTask */
  SamplingTaskHandle = osThreadNew(StartSamplingTask, NULL, &SamplingTask_attributes);

  /* creation of MeasurementTask */
  MeasurementTaskHandle = osThreadNew(StartMeasurementTask, NULL, &MeasurementTask_attributes);

  /* creation of UiTask */
  UiTaskHandle = osThreadNew(StartUiTask, NULL, &UiTask_attributes);

  /* creation of VofaTask */
  VofaTaskHandle = osThreadNew(StartVofaTask, NULL, &VofaTask_attributes);

  /* creation of StorageTask */
  StorageTaskHandle = osThreadNew(StartStorageTask, NULL, &StorageTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartSamplingTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartSamplingTask */
void StartSamplingTask(void *argument)
{
  /* USER CODE BEGIN StartSamplingTask */
  /* 只在最高优先级采样任务中执行一次应用初始化，其他任务等待 appReady。 */
  App_Init();
  appReady = 1U;

  /* Infinite loop */
  for(;;)
  {
    App_SamplingTaskStep();
    osDelay(1);
  }
  /* USER CODE END StartSamplingTask */
}

/* USER CODE BEGIN Header_StartMeasurementTask */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMeasurementTask */
void StartMeasurementTask(void *argument)
{
  /* USER CODE BEGIN StartMeasurementTask */
  while (appReady == 0U)
  {
    osDelay(1);
  }

  /* Infinite loop */
  for(;;)
  {
    App_MeasurementTaskStep();
    osDelay(1);
  }
  /* USER CODE END StartMeasurementTask */
}

/* USER CODE BEGIN Header_StartUiTask */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartUiTask */
void StartUiTask(void *argument)
{
  /* USER CODE BEGIN StartUiTask */
  while (appReady == 0U)
  {
    osDelay(1);
  }

  /* Infinite loop */
  for(;;)
  {
    App_UiTaskStep();
    osDelay(20);
  }
  /* USER CODE END StartUiTask */
}

/* USER CODE BEGIN Header_StartVofaTask */
/**
* @brief Function implementing the myTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartVofaTask */
void StartVofaTask(void *argument)
{
  /* USER CODE BEGIN StartVofaTask */
  while (appReady == 0U)
  {
    osDelay(1);
  }

  /* Infinite loop */
  for(;;)
  {
    App_VofaTaskStep();
    osDelay(2);
  }
  /* USER CODE END StartVofaTask */
}

/* USER CODE BEGIN Header_StartStorageTask */
/**
* @brief Function implementing the myTask05 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartStorageTask */
void StartStorageTask(void *argument)
{
  /* USER CODE BEGIN StartStorageTask */
  while (appReady == 0U)
  {
    osDelay(1);
  }

  /* Infinite loop */
  for(;;)
  {
    App_StorageTaskStep();
    osDelay(10);
  }
  /* USER CODE END StartStorageTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

