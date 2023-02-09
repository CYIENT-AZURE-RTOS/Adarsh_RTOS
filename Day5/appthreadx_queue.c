/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX applicative file
  ******************************************************************************
    * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern UART_HandleTypeDef huart1;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//#define TX_NO_TIME_SLICE	10
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
TX_THREAD ThreadOne;
TX_THREAD ThreadTwo;
TX_QUEUE Myqueue;


//uint8_t task1[]="im in task one lkzslisnlknalksf aslkfnaksnfklasnf  ASDASDASFASFASFASFASF\r\n";
uint8_t task2[]="\r\n im in task two \n\r";

extern volatile uint8_t Ext1_Flag;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void ThreadOne_Entry(ULONG thread_input);
void ThreadTwo_Entry(ULONG thread_input);
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
  (void)byte_pool;
  /* USER CODE END App_ThreadX_MEM_POOL */

  /* USER CODE BEGIN App_ThreadX_Init */
  CHAR *pointer1,*pointer2, *Qpointer;

 // ret = tx_byte_allocate(byte_pool, (VOID **) &pointer1, APP_STACK_SIZE, TX_NO_WAIT);


   /* Allocate the stack for ThreadOne.  */
   if (tx_byte_allocate(byte_pool, (VOID **) &pointer1,
                        APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
   {
     ret = TX_POOL_ERROR;
   }

   /* Create ThreadOne.  */
   if (tx_thread_create(&ThreadOne, "Thread One", ThreadOne_Entry, 0,
                        pointer1, APP_STACK_SIZE,
                        THREAD_ONE_PRIO, THREAD_ONE_PREEMPTION_THRESHOLD,
						TX_8_ULONG, TX_AUTO_START) != TX_SUCCESS)
   {
     ret = TX_THREAD_ERROR;
   }

   //ret = tx_byte_allocate(byte_pool, (VOID **) &pointer2,APP_STACK_SIZE, TX_NO_WAIT);


   /* Allocate the stack for ThreadTwo.  */
    if (tx_byte_allocate(byte_pool, (VOID **) &pointer2,
                         APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
    {
      ret = TX_POOL_ERROR;
    }

    /* Create ThreadTwo.  */
    if (tx_thread_create(&ThreadTwo, "Thread Two", ThreadTwo_Entry, 0,
                         pointer2, APP_STACK_SIZE,
                         THREAD_TWO_PRIO, THREAD_TWO_PREEMPTION_THRESHOLD,
						 TX_8_ULONG, TX_AUTO_START) != TX_SUCCESS)
    {
      ret = TX_THREAD_ERROR;
    }


    /*Allocate the byte for message queue*/
    if (tx_byte_allocate(byte_pool, (VOID **) &Qpointer,
                           1024, TX_NO_WAIT) != TX_SUCCESS)
      {
        ret = TX_POOL_ERROR;
      }

    if(tx_queue_create(&Myqueue, "queue", 16, (VOID *) Qpointer, 1000) != TX_SUCCESS )
    {
          ret = TX_THREAD_ERROR;
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
  uint8_t status;
  uint8_t msg[20] = "Hello India";

  while(1)									/* Infinite loop */
  {
	  //HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_7);	/* Toggle Green LED */
	  HAL_UART_Transmit(&huart1, "\r\n Thread1 \n\r", 15, 200);
	  status = tx_queue_send(&Myqueue, msg, TX_WAIT_FOREVER);
	  if(TX_SUCCESS == status)
	  {
		  HAL_UART_Transmit(&huart1, "\r\n Queue send \n\r", 20, 200);
		  App_Delay(100);
	  }
	  else
	  {
		  HAL_UART_Transmit(&huart1, "\r\n Queue sending fail \n\r", 40, 200);
		  App_Delay(100);
	  }

//	  if(1 == Ext1_Flag)
//	  {
//		  //HAL_UART_Transmit(&huart1, "\r\n Odd entry\n\r", 15, 200);
//		  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_7, GPIO_PIN_SET);
//		  App_Delay(50);							/* Delay for 100=1000ms */
//		  Ext1_Flag =0;
//	  }
//	  else
//	  {
//		  //HAL_UART_Transmit(&huart1, "\r\n even entry\n\r", 15, 200);
//		  //HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_7);
//		  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_7, GPIO_PIN_RESET);
//		  App_Delay(50);
//	  }

  }

}

void ThreadTwo_Entry(ULONG thread_input)
{
  uint8_t status=0;
  uint8_t des[100]= "hai";
  while(1)									/* Infinite loop */
  {
//	HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_6);	/* Toggle Green LED */
//	HAL_UART_Transmit(&huart1, &task2, 50, 200);
//	App_Delay(50);							/* Delay for 100=1000ms */

	  HAL_UART_Transmit(&huart1, "\r\n Thread2 \n\r", 15, 200);
	  status = _tx_queue_receive(&Myqueue, des, TX_WAIT_FOREVER );
	  if(TX_SUCCESS == status)
	 	  {
	 		  HAL_UART_Transmit(&huart1, des , strlen(des), 200);
	 		 App_Delay(100);
	 	  }
	 	  else
	 	  {
	 		  HAL_UART_Transmit(&huart1, "\r\n Queue received fail \n\r", 40, 200);
	 		 App_Delay(100);
	 	  }

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
