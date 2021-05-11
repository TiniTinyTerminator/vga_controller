/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  **
  ****************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "graphics.h"
#include "extra.h"
#include "fonts.h"
#include "EE_FrontLayer/FL_Helper.h"
#include "EE_FrontLayer/FL_interpreter.h"

//stdc
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

//data
#include "imgs/angry_smiley.h"
#include "imgs/happy_smiley.h"
#include "imgs/me.h"

// #include "fonts/aria_font_data.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAX_INPUT_LEN 255
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
char input_buff[MAX_INPUT_LEN] = {};
// char interpreter_data[MAX_INPUT_LEN] = {};

uint32_t wait_time = 0;
uint32_t start_time = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */
void UART_Check_for_string(int8_t *output_string, uint32_t * len);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */

  //init function list
  API_Init_function_list();

  //initialize uart receieve
  HAL_UART_Receive_DMA(&huart2, (uint8_t *)input_buff, MAX_INPUT_LEN);
  
  // Init VGA-Screen
  UB_VGA_Screen_Init(); 

  //init helperfunctions
  API_Init_function_list();

  printf("\rstarted display\r\n");

  API_Set_resolution(VGA_DISPLAY_X, VGA_DISPLAY_Y);
  API_Bind_set_pixel_callback((SetPixelCallback_t)UB_VGA_SetPixel);
  API_Bind_fill_screen_callback((SetFillScreenCallback_t)UB_VGA_FillScreen);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    uint32_t str_len = 0;
    int8_t * string_data = NULL;

    UART_Check_for_string(string_data, str_len);

//    printf("Str_len: %i\r\n",str_len);
    if(str_len > 0)
    {
//       printf("%s\n\r", interpreter_data);
      // HAL_UART_AbortReceive_IT(&huart2);
      // char *data = malloc(str_len + 1);
      // strcpy(data, string_data);

      Parser_err_t err = fl_parser(string_data, str_len);
      // if(err)
      //   printf("ERROR: %d\r\n", err);
      

      // HAL_UART_Receive_IT(&huart2, input_buff, 1);
    }
  
    if((HAL_GetTick() - start_time) > wait_time) {
      wait_time = 0;
      start_time = 0;

      API_Next_Q();
    }
    /* USER CODE END WHILE */
    
    /* USER CODE BEGIN 3 */

    memset(string_data, 0, str_len);
    free(string_data);
    HAL_Delay(50);
  }
  /* USER CODE END 3 */
}



/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* TIM2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
  /* USART2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART2_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* DMA2_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream5_IRQn);
}

/* USER CODE BEGIN 4 */
void UART_Check_for_string(int8_t *output_string, uint32_t * len)
{
  static uint32_t i = 0;
 
  HAL_UART_DMAPause(&huart2);

  if(i > __HAL_DMA_GET_COUNTER(huart2.hdmarx)) {
    i = 0;
    output_string = NULL;
    *len = 0;

    HAL_UART_DMAStop(&huart2);
    HAL_UART_Receive_DMA(&huart2, (uint8_t *)input_buff, MAX_INPUT_LEN);
  }
  else {
    for(; i < __HAL_DMA_GET_COUNTER(huart2.hdmarx); i++)
    {
      putchar(input_buff[i]);

      if(input_buff[i] == '\n' || input_buff[i] == '\r' || strstr(input_buff, "\r\n"))
      {
        // puts("");

        output_string = (int8_t *)malloc(i);
        memcpy(output_string, input_buff, i);

        HAL_UART_DMAStop(&huart2);
        HAL_UART_Receive_DMA(&huart2, (uint8_t *)input_buff, MAX_INPUT_LEN);

        return;
      }
    }

    HAL_UART_DMAResume(&huart2);
  }

  return;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart != &huart2) return;

  puts("BUFFER OVERLOADED!!");
//   putchar(input_buff[i]);

//   //received enter
//   if((input_buff[i] == '\n') || (input_buff[i] == '\r'))
//   {
// 	// puts(input_buff);
//     puts("");

// //TODO FL INTERPRETER IMPLEMENTATION
//     memcpy(interpreter_data, input_buff, i);

//     i = 0;
//   }
//   else
//   {
//     i++;

//     //buffer full
//     if (i >= MAX_INPUT_LEN)
//     {
//       i = 0;
//       printf("\r\nBUFFER OVERLOAD, RESETTING!!\r\n");
//     }

//   }

  HAL_UART_Receive_DMA(&huart2, (uint8_t *)input_buff, MAX_INPUT_LEN);
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
