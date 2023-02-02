/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "app_threadx.h"
#include <stdint.h>
#include "main.h"
#include <stdbool.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
bool Green_flag = false;
bool Red_flag = false;
bool Blue_flag = false;
static uint8_t counter = 0;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
char comm[]="Hello how are you I am doing good. - My name is adarsh\r\n";
char comm1[]="Namaste this is Bengaluru.\r\n";
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
TX_THREAD ThreadOne;
TX_THREAD ThreadTwo;
TX_THREAD ThreadThree;
TX_THREAD ThreadFour;
TX_THREAD ThreadFive;
TX_THREAD ThreadSix;

TX_SEMAPHORE SEMA_One;

extern UART_HandleTypeDef huart1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void ThreadOne_Entry(ULONG thread_input);
void ThreadTwo_Entry(ULONG thread_input);
void ThreadThree_Entry(ULONG thread_input);
void ThreadFour_Entry(ULONG thread_input);
void ThreadFive_Entry(ULONG thread_input);
void ThreadSix_Entry(ULONG thread_input);
void App_Delay(uint32_t Delay);
/* USER CODE END PFP */

/**
  * @brief  Application ThreadX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT App_ThreadX_Init(VOID *memory_ptr)
{
  UINT ret = TX_SUCCESS;
  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;

   /* USER CODE BEGIN App_ThreadX_MEM_POOL */

  /* USER CODE END App_ThreadX_MEM_POOL */

  /* USER CODE BEGIN App_ThreadX_Init */
  CHAR *pointer;

  /* Allocate the stack for ThreadOne.  */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer,APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
    ret = TX_POOL_ERROR;
  }

  /* Create ThreadOne.  */
  if (tx_thread_create(&ThreadOne, "Thread One", ThreadOne_Entry, 0,
                       pointer, APP_STACK_SIZE,
                       THREAD_ONE_PRIO, THREAD_ONE_PREEMPTION_THRESHOLD,
					   10, TX_AUTO_START) != TX_SUCCESS)
	  //TX_NO_TIME_SLICE
  {
    ret = TX_THREAD_ERROR;
  }

  /* Allocate the stack for ThreadTwo.  */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                        APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
   {
     ret = TX_POOL_ERROR;
   }



   /* Create ThreadTwo.  */
   if (tx_thread_create(&ThreadTwo, "Thread Two", ThreadTwo_Entry, 0,
                        pointer, APP_STACK_SIZE,
                        THREAD_TWO_PRIO, THREAD_TWO_PREEMPTION_THRESHOLD,
						10, TX_AUTO_START) != TX_SUCCESS)
	   //TX_NO_TIME_SLICE
   {
     ret = TX_THREAD_ERROR;
   }

   /* Allocate the stack for ThreadThree.  */
   if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                         APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
    {
      ret = TX_POOL_ERROR;
    }
      /* Create ThreadThree.  */
   if (tx_thread_create(&ThreadThree, "Thread Three", ThreadThree_Entry, 0,
                        pointer, APP_STACK_SIZE,
                        THREAD_THREE_PRIO, THREAD_THREE_PREEMPTION_THRESHOLD,
						10, TX_AUTO_START) != TX_SUCCESS)
	   //TX_NO_TIME_SLICE
   {
     ret = TX_THREAD_ERROR;
   }

   /* Allocate the stack for ThreadFour.  */
   if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                         APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
    {
      ret = TX_POOL_ERROR;
    }
      /* Create ThreadFour.  */
   if (tx_thread_create(&ThreadFour, "Thread Four", ThreadFour_Entry, 0,
                        pointer, APP_STACK_SIZE,
                        THREAD_FOUR_PRIO, THREAD_FOUR_PREEMPTION_THRESHOLD,
						10, TX_AUTO_START) != TX_SUCCESS)
	   //TX_NO_TIME_SLICE
   {
     ret = TX_THREAD_ERROR;
   }

   /* Allocate the stack for ThreadFive.  */
   if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                         APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
    {
      ret = TX_POOL_ERROR;
    }
      /* Create ThreadFive.  */
   if (tx_thread_create(&ThreadFive, "Thread Five", ThreadFive_Entry, 0,
                        pointer, APP_STACK_SIZE,
                        THREAD_FIVE_PRIO, THREAD_FIVE_PREEMPTION_THRESHOLD,
						10, TX_AUTO_START) != TX_SUCCESS)
	   //TX_NO_TIME_SLICE
   {
     ret = TX_THREAD_ERROR;
   }

   /* Allocate the stack for ThreadSix.  */
   if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                         APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
    {
      ret = TX_POOL_ERROR;
    }
      /* Create ThreadSix.  */
   if (tx_thread_create(&ThreadSix, "Thread Six", ThreadSix_Entry, 0,
                        pointer, APP_STACK_SIZE,
                        THREAD_SIX_PRIO, THREAD_SIX_PREEMPTION_THRESHOLD,
						10, TX_AUTO_START) != TX_SUCCESS)
	   //TX_NO_TIME_SLICE
   {
     ret = TX_THREAD_ERROR;
   }

   if(tx_semaphore_create(&SEMA_One,"Sema_one",3)!= TX_SUCCESS)
   {
	   ret = TX_SEMAPHORE_ERROR;
   }


  /* USER CODE END App_ThreadX_Init */

  return ret;
}

  /**
  * @brief  MX_ThreadX_Init
  * @param  None
  * @retval None
  */
void MX_ThreadX_Init(void)
{
  /* USER CODE BEGIN  Before_Kernel_Start */

  /* USER CODE END  Before_Kernel_Start */

  tx_kernel_enter();

  /* USER CODE BEGIN  Kernel_Start_Error */

  /* USER CODE END  Kernel_Start_Error */
}

/* USER CODE BEGIN 1 */

void ThreadOne_Entry(ULONG thread_input)
{
  uint8_t t1_count=0;
  uint8_t i = 0;
  bool flag_1 = false;
  bool flag_2 = false;
  bool flag_3 = false;



  while(1)                                    /* Infinite loop */
  {
	  if(tx_semaphore_get(&SEMA_One,TX_WAIT_FOREVER) == TX_SUCCESS)
	  {
		  HAL_UART_Transmit(&huart1, "\n\r++++++ Thread 1 acquired Semaphore ++++++", 40, 100);
		  if(Green_flag == false)
		  {
			  Green_flag = true;
			  flag_1 = true;
			  for(i=0;i<20;i++)
			  {
				  HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin);    /* Toggle Green LED */
				  App_Delay(10);
			  }
		  }
		  else if(Red_flag == false)
		  {
			  Red_flag = true;
			  flag_2 = true;
			  for(i=0;i<20;i++)
			  {
				  HAL_GPIO_TogglePin(LED_RED_GPIO_Port,LED_RED_Pin);    /* Toggle Green LED */
				  App_Delay(10);
			  }
		  }
		  else if(Blue_flag == false)
		  {
			  Blue_flag = true;
			  flag_3 = true;
			  for(i=0;i<20;i++)
			  {
				  HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port,LED_BLUE_Pin);    /* Toggle Green LED */
				  App_Delay(10);
			  }
		  }

	  }
	  if(flag_1 == true)
	  {
		  Green_flag = false;
	  }
	  else if (flag_2 == true)
	  {
		  Red_flag = false;
	  }
	  else if (flag_3 == true)
	  {
		  Blue_flag = false;
	  }

	  HAL_UART_Transmit(&huart1, "\n\r++++++ Thread 1 released Semaphore ++++++", 40, 100);
	  counter++;
	  tx_semaphore_put(&SEMA_One);

  }
}



void ThreadTwo_Entry(ULONG thread_input)
{
  uint8_t t1_count=0;
  uint8_t i = 0;
  bool flag_1 = false;
  bool flag_2 = false;
  bool flag_3 = false;
  while(1)                                    /* Infinite loop */
  {
	  if(tx_semaphore_get(&SEMA_One,TX_WAIT_FOREVER) == TX_SUCCESS)
	  {
		  if(counter == 5)
		  {
			  counter = 0;
			  tx_thread_terminate(&ThreadOne);
			  tx_thread_delete(&ThreadOne);
			  HAL_UART_Transmit(&huart1, "\n\r++++++ Thread 1 Deleted ++++++", 40, 100);
		  }
		  HAL_UART_Transmit(&huart1, "\n\r++++++ Thread 2 acquired Semaphore ++++++", 40, 100);
		  if(Green_flag == false)
		  {
			  Green_flag = true;
			  flag_1 = true;
			  for(i=0;i<9;i++)
			  {
				  HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin);    /* Toggle Green LED */
				  App_Delay(100);
			  }
		  }
		  else if(Red_flag == false)
		  {
			  Red_flag = true;
			  flag_2 = true;
			  for(i=0;i<9;i++)
			  {
				  HAL_GPIO_TogglePin(LED_RED_GPIO_Port,LED_RED_Pin);    /* Toggle Green LED */
				  App_Delay(100);
			  }
		  }
		  else if(Blue_flag == false)
		  {
			  Blue_flag = true;
			  flag_3 = true;
			  for(i=0;i<9;i++)
			  {
				  HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port,LED_BLUE_Pin);    /* Toggle Green LED */
				  App_Delay(100);
			  }
		  }
	  }
	  if(flag_1 == true)
	  {
		  Green_flag = false;
	  }
	  else if (flag_2 == true)
	  {
		  Red_flag = false;
	  }
	  	  else if (flag_3 == true)
	  {
		  Blue_flag = false;
	  }

	  HAL_UART_Transmit(&huart1, "\n\r++++++ Thread 2 released Semaphore ++++++", 40, 100);
	  tx_semaphore_put(&SEMA_One);

  }
}



void ThreadThree_Entry(ULONG thread_input)
{
  uint8_t t1_count=0;
  uint8_t i = 0;
  bool flag_1 = false;
  bool flag_2 = false;
  bool flag_3 = false;
  while(1)                                    /* Infinite loop */
  {
	  if(tx_semaphore_get(&SEMA_One,TX_WAIT_FOREVER) == TX_SUCCESS)
	  {
		  HAL_UART_Transmit(&huart1, "\n\r++++++ Thread 3 acquired Semaphore ++++++", 40, 100);
		  if(Green_flag == false)
		  {
			  Green_flag = true;
			  flag_1 = true;
			  for(i=0;i<5;i++)
			  {
				  HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin);    /* Toggle Green LED */
				  App_Delay(300);
			  }
		  }
		  else if(Red_flag == false)
		  {
			  Red_flag = true;
			  flag_2 = true;
			  for(i=0;i<5;i++)
			  {
				  HAL_GPIO_TogglePin(LED_RED_GPIO_Port,LED_RED_Pin);    /* Toggle Green LED */
				  App_Delay(300);
			  }
		  }
		  else if(Blue_flag == false)
		  {
			  Blue_flag = true;
			  flag_3 = true;
			  for(i=0;i<5;i++)
			  {
				  HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port,LED_BLUE_Pin);    /* Toggle Green LED */
				  App_Delay(300);
			  }
		  }
	  }
	  if(flag_1 == true)
	  {
		  Green_flag = false;
	  }
	  else if (flag_2 == true)
	  {
		  Red_flag = false;
	  }
	  else if (flag_3 == true)
	  {
		  Blue_flag = false;
	  }
	  HAL_UART_Transmit(&huart1, "\n\r++++++ Thread 3 released Semaphore ++++++", 40, 100);
	  tx_semaphore_put(&SEMA_One);
  }
}


void ThreadFour_Entry(ULONG thread_input)
{
  uint8_t t1_count=0;
  uint8_t i = 0;
  bool flag_1 = false;
  bool flag_2 = false;
  bool flag_3 = false;
  while(1)                                    /* Infinite loop */
  {
	  if(tx_semaphore_get(&SEMA_One,TX_WAIT_FOREVER) == TX_SUCCESS)
	  {
		  HAL_UART_Transmit(&huart1, "\n\r++++++ Thread 4 acquired Semaphore ++++++", 40, 100);
		  if(Green_flag == false)
		  {
			  Green_flag = true;
			  flag_1 = true;
			  for(i=0;i<3;i++)
			  {
				  HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin);    /* Toggle Green LED */
				  App_Delay(600);
			  }
		  }
		  else if(Red_flag == false)
		  {
			  Red_flag = true;
			  flag_2 = true;
			  for(i=0;i<3;i++)
			  {
				  HAL_GPIO_TogglePin(LED_RED_GPIO_Port,LED_RED_Pin);    /* Toggle Green LED */
				  App_Delay(600);
			  }
		  }
		  else if(Blue_flag == false)
		  {
			  Blue_flag = true;
			  flag_3 = true;
			  for(i=0;i<3;i++)
			  {
				  HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port,LED_BLUE_Pin);    /* Toggle Green LED */
				  App_Delay(600);
			  }
		  }
	  }
	  if(flag_1 == true)
	  {
		  Green_flag = false;
	  }
	  else if (flag_2 == true)
	  {
		  Red_flag = false;
	  }
	  else if (flag_3 == true)
	  {
		  Blue_flag = false;
	  }
	  HAL_UART_Transmit(&huart1, "\n\r++++++ Thread 4 released Semaphore ++++++", 40, 100);
	  tx_semaphore_put(&SEMA_One);
  }
}





void ThreadFive_Entry(ULONG thread_input)
{
  uint8_t t1_count=0;
  uint8_t i = 0;
  bool flag_1 = false;
  bool flag_2 = false;
  bool flag_3 = false;
  while(1)                                    /* Infinite loop */
  {
	  if(tx_semaphore_get(&SEMA_One,TX_WAIT_FOREVER) == TX_SUCCESS)
	  {
		  HAL_UART_Transmit(&huart1, "\n\r++++++ Thread 5 acquired Semaphore ++++++", 40, 100);
		  if(Green_flag == false)
		  {
			  Green_flag = true;
			  flag_1 = true;
			  for(i=0;i<2;i++)
			  {
				  HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin);    /* Toggle Green LED */
				  App_Delay(800);
			  }
		  }
		  else if(Red_flag == false)
		  {
			  Red_flag = true;
			  flag_2 = true;
			  for(i=0;i<2;i++)
			  {
				  HAL_GPIO_TogglePin(LED_RED_GPIO_Port,LED_RED_Pin);    /* Toggle Green LED */
				  App_Delay(800);
			  }
		  }
		  else if(Blue_flag == false)
		  {
			  Blue_flag = true;
			  flag_3 = true;
			  for(i=0;i<2;i++)
			  {
				  HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port,LED_BLUE_Pin);    /* Toggle Green LED */
				  App_Delay(800);
			  }
		  }
	  }
	  if(flag_1 == true)
	  {
		  Green_flag = false;
	  }
	  else if (flag_2 == true)
	  {
		  Red_flag = false;
	  }
	  else if (flag_3 == true)
	  {
		  Blue_flag = false;
	  }
	  HAL_UART_Transmit(&huart1, "\n\r++++++ Thread 5 released Semaphore ++++++", 40, 100);
	  tx_semaphore_put(&SEMA_One);
  }
}




void ThreadSix_Entry(ULONG thread_input)
{
  uint8_t t1_count=0;
  uint8_t i = 0;
  bool flag_1 = false;
  bool flag_2 = false;
  bool flag_3 = false;
  while(1)                                    /* Infinite loop */
  {
	  if(tx_semaphore_get(&SEMA_One,TX_WAIT_FOREVER) == TX_SUCCESS)
	  {
		  HAL_UART_Transmit(&huart1, "\n\r++++++ Thread 6 acquired Semaphore ++++++", 40, 100);
		  if(Green_flag == false)
		  {
			  Green_flag = true;
			  flag_1 = true;
			  for(i=0;i<1;i++)
			  {
				  HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin);    /* Toggle Green LED */
				  App_Delay(1000);
			  }
		  }
		  else if(Red_flag == false)
		  {
			  Red_flag = true;
			  flag_2 = true;
			  for(i=0;i<1;i++)
			  {
				  HAL_GPIO_TogglePin(LED_RED_GPIO_Port,LED_RED_Pin);    /* Toggle Green LED */
				  App_Delay(1000);
			  }
		  }
		  else if(Blue_flag == false)
		  {
			  Blue_flag = true;
			  flag_3 = true;
			  for(i=0;i<1;i++)
			  {
				  HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port,LED_BLUE_Pin);    /* Toggle Green LED */
				  App_Delay(1000);
			  }
		  }
	  }
	  if(flag_1 == true)
	  {
		  Green_flag = false;
	  }
	  else if (flag_2 == true)
	  {
		  Red_flag = false;
	  }
	  else if (flag_3 == true)
	  {
		  Blue_flag = false;
	  }
	  HAL_UART_Transmit(&huart1, "\n\r++++++ Thread 6 released Semaphore ++++++", 40, 100);
	  tx_semaphore_put(&SEMA_One);
  }
}




/**
  * @brief  Application Delay function.
  * @param  Delay : number of ticks to wait
  * @retval None
  */
void App_Delay(uint32_t Delay)
{
  UINT initial_time = tx_time_get();
  while ((tx_time_get() - initial_time) < Delay);
}

/* USER CODE END 1 */
