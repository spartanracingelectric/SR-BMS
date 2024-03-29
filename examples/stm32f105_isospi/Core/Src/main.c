/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "adc.h"
#include "can.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "ltc6813.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define NUM_DEVICES_DEFAULT					1	//2 slave boards
#define NUM_SERIES_GROUPS_PER_MOD_DEFAULT	12	//12 in series
#define NUM_SERIES_GROUPS_TOTAL_DEFAULT		(NUM_DEVICES_DEFAULT * NUM_SERIES_GROUPS_PER_MOD_DEFAULT) //24 series groups

#define LTC_DELAY_MS			500 //500ms update delay
#define LED_HEARTBEAT_DELAY_MS	500 //500ms update delay

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

typedef struct _TimerPacket {
	uint32_t 		ts_prev;	//Previous timestamp
	uint32_t 		ts_curr; 	//Current timestamp
	uint32_t		delay;		//Amount to delay
} TimerPacket;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void TimerPacket_Init(TimerPacket *tp, uint32_t delay);

//Returns 1 at every tp->delay interval
uint8_t TimerPacket_FixedPulse(TimerPacket *tp);

//Set Heartbeat LED to LOW
void LED_Heartbeat_Init(void);

//Toggle Heartbeat LED
void LED_Heartbeat_Toggle(void);

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
  TimerPacket tp_led_heartbeat;
  TimerPacket tp_ltc;

  uint16_t read_val[NUM_SERIES_GROUPS_TOTAL_DEFAULT]; //To hold all series groups' data

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
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_CAN1_Init();
  MX_CAN2_Init();
  MX_TIM7_Init();
  MX_SPI1_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */

  //Start timer
  TimerPacket_Init(&tp_led_heartbeat, LED_HEARTBEAT_DELAY_MS);
  TimerPacket_Init(&tp_ltc, LTC_DELAY_MS);

  //Set Heartbeat LED initial value to LOW
  LED_Heartbeat_Init();

  //Pull SPI1 nCS HIGH (deselect)
  LTC_SPI_nCS_High();

  LTC_Set_Num_Devices(NUM_DEVICES_DEFAULT);
  LTC_Set_Num_Series_Groups(NUM_SERIES_GROUPS_PER_MOD_DEFAULT);

  //Something with this implementation is wacky, keep out for now. WIP
  //LTC_InitCellMonitor();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  	//LED HEARTBEAT
		if (TimerPacket_FixedPulse(&tp_led_heartbeat)) { LED_Heartbeat_Toggle(); }

		//READ CELL VOLTAGE
		if (TimerPacket_FixedPulse(&tp_ltc)) {
			char buf[20];
			char out_buf[1024] = "";
			char char_to_str_pre[1];
			char char_to_str_post[3];

			LTC_ReadRawCellVoltages((uint16_t *)read_val);

			//Remeasure cell voltages
			LTC_WriteClearCellVoltageRegisters();
			LTC_WriteStartCellVoltageConversion(MD_FILTERED, DCP_DISABLED, CELL_CH_ALL);

			char_to_str_pre[0] = '$'; //Start delimiter for voltage
			strncat(out_buf, char_to_str_pre, 1);
			for (uint8_t i = 0; i < NUM_SERIES_GROUPS_TOTAL_DEFAULT; i++) {
				// sprintf(buf, "C%u:%u/1000 V", i+1, read_val[i]);
				sprintf(buf, "c%u=%u,", i+1, read_val[i]);
				strncat(out_buf, buf, 20);
			}
			char_to_str_post[0] = '@'; //End delimiter for voltage
			char_to_str_post[1] = '\n';
			char_to_str_post[2] = '\0';
			strncat(out_buf, char_to_str_post, 3);
			//strncat(out_buf, "@", 1);

			// strncat(out_buf, char_to_str, 3);

			USB_Transmit(out_buf, strlen(out_buf));
		}
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV5;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_PLL2;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL2_ON;
  RCC_OscInitStruct.PLL2.PLL2MUL = RCC_PLL2_MUL8;
  RCC_OscInitStruct.PLL2.HSEPrediv2Value = RCC_HSE_PREDIV2_DIV5;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC|RCC_PERIPHCLK_USB;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV3;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the Systick interrupt time
  */
  __HAL_RCC_PLLI2S_ENABLE();
}

/* USER CODE BEGIN 4 */

//Initialize struct values
void TimerPacket_Init(TimerPacket *tp, uint32_t delay)
{
	tp->ts_prev 	= 0;		//Init to 0
	tp->ts_curr 	= 0; 		//Init to 0
	tp->delay		= delay;	//Init to user value
}

//tp->delay = update after X ms
uint8_t TimerPacket_FixedPulse(TimerPacket *tp)
{
	tp->ts_curr = HAL_GetTick(); //Record current timestamp

	if (tp->ts_curr - tp->ts_prev > tp->delay) {
		tp->ts_prev = tp->ts_curr; //Update prev timestamp to current
		return 1; //Enact event (time interval is a go)
	}
	return 0; //Do not enact event
}

void LED_Heartbeat_Init(void) {
	HAL_GPIO_WritePin(MCU_HEARTBEAT_LED_GPIO_Port, MCU_HEARTBEAT_LED_Pin, GPIO_PIN_RESET); //Set GPIO LOW
}

void LED_Heartbeat_Toggle(void) {
	HAL_GPIO_TogglePin(MCU_HEARTBEAT_LED_GPIO_Port, MCU_HEARTBEAT_LED_Pin); //Set GPIO LOW
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
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
