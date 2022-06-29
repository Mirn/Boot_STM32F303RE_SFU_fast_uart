/*
 * hw_init.c
 *
 *  Created on: Sep 20, 2018
 *      Author: sj21d
 */

#include "stm32kiss.h"
#ifdef STM32F303xE
#include "usart_mini.h"

void Error_Handler(void);

CRC_HandleTypeDef hcrc;

/* CRC init function */
void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
  hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
  hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
  hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
  hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_WORDS;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

void HAL_CRC_MspInit(CRC_HandleTypeDef* crcHandle)
{

  if(crcHandle->Instance==CRC)
  {
  /* USER CODE BEGIN CRC_MspInit 0 */

  /* USER CODE END CRC_MspInit 0 */
    /* CRC clock enable */
    __HAL_RCC_CRC_CLK_ENABLE();
  /* USER CODE BEGIN CRC_MspInit 1 */

  /* USER CODE END CRC_MspInit 1 */
  }
}

void HAL_CRC_MspDeInit(CRC_HandleTypeDef* crcHandle)
{

  if(crcHandle->Instance==CRC)
  {
  /* USER CODE BEGIN CRC_MspDeInit 0 */

  /* USER CODE END CRC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CRC_CLK_DISABLE();
  /* USER CODE BEGIN CRC_MspDeInit 1 */

  /* USER CODE END CRC_MspDeInit 1 */
  }
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_TIM1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLK_HCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

void HAL_MspInit(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
}

extern const uint8_t _siccmram;
extern const uint8_t _sccmram;
extern const uint8_t _eccmram;

void hw_init_all()
{
	HAL_Init();
	SystemClock_Config();

    SystemCoreClockUpdate();
    ticks_init();

    uint32_t *src = (uint32_t *)(&_siccmram);
    uint32_t *dst = (uint32_t *)(&_sccmram);
    while (((uint32_t)dst) < (uint32_t)(&_eccmram))
        *(dst++) = *(src++);

    usart_init();
    MX_CRC_Init();
}

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

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
void NMI_Handler(void) { while (1) {  } };
void HardFault_Handler(void) { while (1) {  } };
void MemManage_Handler(void) { while (1) {  } };
void BusFault_Handler(void) { while (1) {  } };
void UsageFault_Handler(void) { while (1) {  } };
void SVC_Handler(void) {}
void DebugMon_Handler(void) {}
void PendSV_Handler(void) {}

#else
CRC_HandleTypeDef hcrc;

__attribute__((weak)) void __libc_init_array() {};

void HAL_CRC_MspInit(CRC_HandleTypeDef* hcrc1)
{
	if(hcrc1->Instance !=CRC) return;
	__HAL_RCC_CRC_CLK_ENABLE();
}

void MX_CRC_Init(void)
{
	hcrc.Instance = CRC;
	hcrc.Init.DefaultPolynomialUse    = DEFAULT_POLYNOMIAL_ENABLE;
	hcrc.Init.DefaultInitValueUse     = DEFAULT_INIT_VALUE_ENABLE;
	hcrc.Init.InputDataInversionMode  = CRC_INPUTDATA_INVERSION_NONE;
	hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
	hcrc.InputDataFormat              = CRC_INPUTDATA_FORMAT_WORDS;

	HAL_CRC_Init(&hcrc);
}

extern const int _itcm_sidata;
extern const int _itcm_sdata;
extern const int _itcm_edata;

extern const int _sidata;
extern const int _sdata;
extern const int _edata;
extern const int _isr_vector_addr;

void __BeforeInitCallback()
{
	SCB->VTOR = (uint32_t)(&_isr_vector_addr);
	SCB_EnableICache();
	SCB_EnableDCache();

	uint32_t *src = (uint32_t *)(&_itcm_sidata);
	uint32_t *dst = (uint32_t *)(&_itcm_sdata);
	while (((uint32_t)dst) < (uint32_t)(&_itcm_edata))
		*(dst++) = *(src++);
	//memcpy((void*)(&_itcm_sdata), (void *)(&_itcm_sidata), ((uint32_t)(&_itcm_edata) - (uint32_t)(&_itcm_sdata)));
}

void hw_printf_sections()
{
	printf("_isr_vector_addr\t%08lX\n", (uint32_t)(&_isr_vector_addr));
	printf("SCB->VTOR\t%08lX\r", SCB->VTOR);
	printf("\n");

	printf("\n");
	printf("_sidata\t%08lX\n", (uint32_t)(&_sidata));
	printf("_sdata \t%08lX\n", (uint32_t)(&_sdata));
	printf("_edata \t%08lX\n", (uint32_t)(&_edata));
	printf("\n");
	printf("_itcm_sidata\t%08lX\n", (uint32_t)(&_itcm_sidata));
	printf("_itcm_sdata \t%08lX\n", (uint32_t)(&_itcm_sdata));
	printf("_itcm_edata \t%08lX\n", (uint32_t)(&_itcm_edata));
	printf("\n");
}

void hw_init_all()
{
	SystemCoreClockUpdate();
	HAL_Init();

	MX_CRC_Init();

	SystemCoreClockUpdate();

	ticks_init();
	//delay_ms(1000);
	usart_init();
}
#endif
