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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <fonts.h>

#include "happy_smiley.h"
#include "me.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAX_INPUT_LEN 255
#define MAX_COMMAND_BUFFERING 40

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t input_buff[MAX_INPUT_LEN] = {};
uint8_t * command_buff[MAX_COMMAND_BUFFERING] = {};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void append_command(const char *, ssize_t len);


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
  /* USER CODE BEGIN 2 */

  HAL_UART_Receive_DMA(&huart2, input_buff, 1);

  UB_VGA_Screen_Init(); // Init VGA-Screen

  API_Set_resolution(VGA_DISPLAY_X, VGA_DISPLAY_Y);
  API_Bind_set_pixel_callback((SetPixelCallback_t)UB_VGA_SetPixel);
  API_Bind_fill_screen_callback((SetFillScreenCallback_t)UB_VGA_FillScreen);

  API_Fill_screen(VGA_COL_WHITE);

  // API_Draw_square(50, 50, 1, 1, VGA_COL_RED);
  // API_Draw_line(10, 10, 20, 20, VGA_COL_MAGENTA);

  uint32_t posX[] = {20, 50, 80, 150};
  uint32_t posY[] = {30, 50, 20, 10};

   API_Draw_line(posX[0], posY[0], posX[1], posY[1], VGA_COL_BLUE);
   API_Draw_line(posX[1], posY[1], posX[2], posY[2], VGA_COL_BLUE);
   API_Draw_line(posX[2], posY[2], posX[3], posY[3], VGA_COL_BLUE);
   API_Draw_line(posX[3], posY[3], posX[0], posY[0], VGA_COL_BLUE);

  // API_Draw_line(100, 100, 50, 50, VGA_COL_BLACK);
  API_Draw_polygon(posX, posY, 4, VGA_COL_CYAN);


  // madelbrot(VGA_DISPLAY_X, VGA_DISPLAY_Y, 100, -1.5,1,-1,1);

  // API_Fill_screen(VGA_COL_GREEN);

  
  // API_Load_bitmap(200, 50, HAPPY_SMILEY_WIDTH, HAPPY_SMILEY_HEIGHT, happy_smiley_map);
  // // API_Load_bitmap(0, 0, ME_WIDTH, ME_HEIGHT, me_map);
  // API_Fill_circle(100, 100, 30, VGA_COL_RED);
  // API_Fill_square(30, 30, 30, 30, VGA_COL_BLUE);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    for(int i = 0; i < MAX_COMMAND_BUFFERING; i++)
      if(command_buff[i] != NULL) {
        // HAL_UART_Transmit(&huart2, command_buff[i], strlen(command_buff[i]), HAL_MAX_DELAY);
        
        free(command_buff[i]);
        command_buff[i] = NULL;
      }
    /* USER CODE BEGIN 3 */
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

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  static uint32_t i = 0;

  if(huart != &huart2) return;

  HAL_UART_Transmit(&huart2, input_buff + i, 1, HAL_MAX_DELAY);

  //received enter
  if(input_buff[i] == '\n' || input_buff[i] == '\r')
  {
    //do stuff
    char enter[] = "\r\n";

    HAL_UART_Transmit(&huart2, enter, strlen(enter), HAL_MAX_DELAY);

    append_command(input_buff, i);

    memset(input_buff, 0, MAX_INPUT_LEN);
    i = 0;
  }
  else i++;

  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);

  //buffer full
  if (i >= MAX_INPUT_LEN)
  {
    i = 0;
    char overload_string[] = "BUFFER OVERLOAD, RESETTING!!\r\n";
    HAL_UART_Transmit(&huart2, overload_string, strlen(overload_string), HAL_MAX_DELAY);

    memset(input_buff, 0, MAX_INPUT_LEN);
  }

  HAL_UART_Receive_DMA(&huart2, input_buff + i, 1);

}

void append_command(const char * str, ssize_t len)
{

  for(int i = 0; i < MAX_COMMAND_BUFFERING; i++)
    if(command_buff[i] == NULL)
    {
      command_buff[i] = calloc(len + 2, (sizeof(uint8_t)));
      
      if(command_buff[i] != NULL)
      {
        strcpy(command_buff[i], str);
        command_buff[i][len - 1] = '\r';
        command_buff[i][len] = '\n';

        return;
      }
      else
      {
        char NO_MEM[] = "Not enough memory...\r\n";
        HAL_UART_Transmit(&huart2, NO_MEM, strlen(NO_MEM), HAL_MAX_DELAY);
      }

    }
  char buffer_overload_string[] = "too many commands buffered, discarding...\r\n";
  HAL_UART_Transmit(&huart2, buffer_overload_string, strlen(buffer_overload_string), HAL_MAX_DELAY);
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
