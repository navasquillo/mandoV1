/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "cmsis_os.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
    #include "mcalm_api.h"
    #include "ecualm_api.h"
    #include "ver_api.h"
    //
    #include "TaskFreeRtosMonitor_api.h"
    #include "TaskParams_api.h"
    #include "TaskMesurarAdc_api.h"
    #include "TaskPantalla_api.h"
    #include "TaskFlash_api.h"
    #include "FLASH_SECTOR_F4.h"
    #include "rtwtypes.h"

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
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

I2C_HandleTypeDef hi2c1;
DMA_HandleTypeDef hdma_i2c1_tx;
DMA_HandleTypeDef hdma_i2c1_rx;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim5;

osThreadId MesurarAdcHandle;
osThreadId PantallaHandle;
osThreadId ParamsHandle;
osThreadId FreeRtosMonitorHandle;
osThreadId FlashHandle;
osMessageQId PotenciaParamFHandle;
osMessageQId CorbaParamFHandle;
osMessageQId FrenoAdcHandle;
osMessageQId PotenciaAdcHandle;
osMessageQId CorbaAdcHandle;
osMessageQId GatellAdcHandle;
osMessageQId PotenciaAdcFiltratHandle;
osMessageQId CorbaAdcFiltratHandle;
osMessageQId MapaFrenoHandle;
osMessageQId PotenciaDinHandle;
osMessageQId MensajePantallaHandle;
osMessageQId PosFrenoFlashHandle;
osMessageQId ValorInicial1FlashHandle;
osMessageQId ValorFinal1FlashHandle;
osMessageQId PosFondoFlashHandle;
osMessageQId DiffGatellFlashHandle;
osMessageQId ExtraPWMFlashHandle;
osMessageQId MapaFrenoPantallaHandle;
osMessageQId PotenciaDinPantallaHandle;
osMessageQId ValorInicial2FlashHandle;
osMessageQId ValorFinal2FlashHandle;
osMessageQId ValorInicial1PantallaHandle;
osMessageQId ValorFinal1PantallaHandle;
osMessageQId ValorInicial2PantallaHandle;
osMessageQId ValorFinal2PantallaHandle;
osMessageQId PosFrenoMapa2FlashHandle;
osMessageQId VoltatgeAdcHandle;
osMessageQId VoltatgeAdcFiltratHandle;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM5_Init(void);
void TaskMesurarAdc(void const * argument);
void TaskPantalla(void const * argument);
void TaskParams(void const * argument);
void TaskFreeRtosMonitor(void const * argument);
void TaskFlash(void const * argument);

/* USER CODE BEGIN PFP */

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
  // IMPORTANT: A small Delay must be used for the HSE Clock stabilization before the SystemClock_Config().
  //            Otherwise, the HSE won't be ok and the MCU will freeze in a Cold Start-Up. At IDE v1.19.0 ST changed the internal function order of SystemClock_Config and now the issue is easier to see.
  HAL_Delay( mcalm_DELAY_ms_BEFORE_START_HSE );
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  // 1.1) Start-up Level 1  (first Init of MCAL)
  MCALM_PeripheralsInit();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_TIM5_Init();
  /* USER CODE BEGIN 2 */

  // 1.2) Start-up Level 2  (first Init of ECUAL+VER)
  ECUALM_Init();
  VER_Init();


  // 1.3) Start-up Level 3  (first Init of APP)
  /* Inicialitzar Monitor Stack FreeRtos */
  TASKFREERTOSMONITOR_Init();
  /* Carregar valors de la flash */
  TASKFLASH_Init();
  /* Inicialitzar parametres per representar la corba */
  TASKPARAMS_Init();
  /* Inicialitzar la tasca de la pantalla */
  TASKPANTALLA_Init();
  /* Despres cargar-los al model */
  TASKMESURAR_Init();


  // 1.4) Start-up Level 4  (PostInit of MCAL+ECUAL)
  /*I2CM_PostInit(); */  // Done at TaskPantalla.c

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of PotenciaParamF */
  osMessageQDef(PotenciaParamF, 1, float);
  PotenciaParamFHandle = osMessageCreate(osMessageQ(PotenciaParamF), NULL);

  /* definition and creation of CorbaParamF */
  osMessageQDef(CorbaParamF, 1, float);
  CorbaParamFHandle = osMessageCreate(osMessageQ(CorbaParamF), NULL);

  /* definition and creation of FrenoAdc */
  osMessageQDef(FrenoAdc, 1, uint16_t);
  FrenoAdcHandle = osMessageCreate(osMessageQ(FrenoAdc), NULL);

  /* definition and creation of PotenciaAdc */
  osMessageQDef(PotenciaAdc, 3, uint16_t);
  PotenciaAdcHandle = osMessageCreate(osMessageQ(PotenciaAdc), NULL);

  /* definition and creation of CorbaAdc */
  osMessageQDef(CorbaAdc, 3, uint16_t);
  CorbaAdcHandle = osMessageCreate(osMessageQ(CorbaAdc), NULL);

  /* definition and creation of GatellAdc */
  osMessageQDef(GatellAdc, 1, uint16_t);
  GatellAdcHandle = osMessageCreate(osMessageQ(GatellAdc), NULL);

  /* definition and creation of PotenciaAdcFiltrat */
  osMessageQDef(PotenciaAdcFiltrat, 1, uint16_t);
  PotenciaAdcFiltratHandle = osMessageCreate(osMessageQ(PotenciaAdcFiltrat), NULL);

  /* definition and creation of CorbaAdcFiltrat */
  osMessageQDef(CorbaAdcFiltrat, 1, uint16_t);
  CorbaAdcFiltratHandle = osMessageCreate(osMessageQ(CorbaAdcFiltrat), NULL);

  /* definition and creation of MapaFreno */
  osMessageQDef(MapaFreno, 1, uint32_t);
  MapaFrenoHandle = osMessageCreate(osMessageQ(MapaFreno), NULL);

  /* definition and creation of PotenciaDin */
  osMessageQDef(PotenciaDin, 1, uint32_t);
  PotenciaDinHandle = osMessageCreate(osMessageQ(PotenciaDin), NULL);

  /* definition and creation of MensajePantalla */
  osMessageQDef(MensajePantalla, 1, uint32_t);
  MensajePantallaHandle = osMessageCreate(osMessageQ(MensajePantalla), NULL);

  /* definition and creation of PosFrenoFlash */
  osMessageQDef(PosFrenoFlash, 1, uint32_t);
  PosFrenoFlashHandle = osMessageCreate(osMessageQ(PosFrenoFlash), NULL);

  /* definition and creation of ValorInicial1Flash */
  osMessageQDef(ValorInicial1Flash, 1, uint32_t);
  ValorInicial1FlashHandle = osMessageCreate(osMessageQ(ValorInicial1Flash), NULL);

  /* definition and creation of ValorFinal1Flash */
  osMessageQDef(ValorFinal1Flash, 1, uint32_t);
  ValorFinal1FlashHandle = osMessageCreate(osMessageQ(ValorFinal1Flash), NULL);

  /* definition and creation of PosFondoFlash */
  osMessageQDef(PosFondoFlash, 1, uint32_t);
  PosFondoFlashHandle = osMessageCreate(osMessageQ(PosFondoFlash), NULL);

  /* definition and creation of DiffGatellFlash */
  osMessageQDef(DiffGatellFlash, 1, uint32_t);
  DiffGatellFlashHandle = osMessageCreate(osMessageQ(DiffGatellFlash), NULL);

  /* definition and creation of ExtraPWMFlash */
  osMessageQDef(ExtraPWMFlash, 1, uint32_t);
  ExtraPWMFlashHandle = osMessageCreate(osMessageQ(ExtraPWMFlash), NULL);

  /* definition and creation of MapaFrenoPantalla */
  osMessageQDef(MapaFrenoPantalla, 1, uint32_t);
  MapaFrenoPantallaHandle = osMessageCreate(osMessageQ(MapaFrenoPantalla), NULL);

  /* definition and creation of PotenciaDinPantalla */
  osMessageQDef(PotenciaDinPantalla, 1, uint32_t);
  PotenciaDinPantallaHandle = osMessageCreate(osMessageQ(PotenciaDinPantalla), NULL);

  /* definition and creation of ValorInicial2Flash */
  osMessageQDef(ValorInicial2Flash, 1, uint32_t);
  ValorInicial2FlashHandle = osMessageCreate(osMessageQ(ValorInicial2Flash), NULL);

  /* definition and creation of ValorFinal2Flash */
  osMessageQDef(ValorFinal2Flash, 1, uint32_t);
  ValorFinal2FlashHandle = osMessageCreate(osMessageQ(ValorFinal2Flash), NULL);

  /* definition and creation of ValorInicial1Pantalla */
  osMessageQDef(ValorInicial1Pantalla, 1, uint32_t);
  ValorInicial1PantallaHandle = osMessageCreate(osMessageQ(ValorInicial1Pantalla), NULL);

  /* definition and creation of ValorFinal1Pantalla */
  osMessageQDef(ValorFinal1Pantalla, 1, uint32_t);
  ValorFinal1PantallaHandle = osMessageCreate(osMessageQ(ValorFinal1Pantalla), NULL);

  /* definition and creation of ValorInicial2Pantalla */
  osMessageQDef(ValorInicial2Pantalla, 1, uint32_t);
  ValorInicial2PantallaHandle = osMessageCreate(osMessageQ(ValorInicial2Pantalla), NULL);

  /* definition and creation of ValorFinal2Pantalla */
  osMessageQDef(ValorFinal2Pantalla, 1, uint32_t);
  ValorFinal2PantallaHandle = osMessageCreate(osMessageQ(ValorFinal2Pantalla), NULL);

  /* definition and creation of PosFrenoMapa2Flash */
  osMessageQDef(PosFrenoMapa2Flash, 1, uint32_t);
  PosFrenoMapa2FlashHandle = osMessageCreate(osMessageQ(PosFrenoMapa2Flash), NULL);

  /* definition and creation of VoltatgeAdc */
  osMessageQDef(VoltatgeAdc, 1, uint32_t);
  VoltatgeAdcHandle = osMessageCreate(osMessageQ(VoltatgeAdc), NULL);

  /* definition and creation of VoltatgeAdcFiltrat */
  osMessageQDef(VoltatgeAdcFiltrat, 16, uint16_t);
  VoltatgeAdcFiltratHandle = osMessageCreate(osMessageQ(VoltatgeAdcFiltrat), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of MesurarAdc */
  osThreadDef(MesurarAdc, TaskMesurarAdc, osPriorityLow, 0, 512);
  MesurarAdcHandle = osThreadCreate(osThread(MesurarAdc), NULL);

  /* definition and creation of Pantalla */
  osThreadDef(Pantalla, TaskPantalla, osPriorityAboveNormal, 0, 512);
  PantallaHandle = osThreadCreate(osThread(Pantalla), NULL);

  /* definition and creation of Params */
  osThreadDef(Params, TaskParams, osPriorityNormal, 0, 512);
  ParamsHandle = osThreadCreate(osThread(Params), NULL);

  /* definition and creation of FreeRtosMonitor */
  osThreadDef(FreeRtosMonitor, TaskFreeRtosMonitor, osPriorityHigh, 0, 512);
  FreeRtosMonitorHandle = osThreadCreate(osThread(FreeRtosMonitor), NULL);

  /* definition and creation of Flash */
  osThreadDef(Flash, TaskFlash, osPriorityNormal, 0, 512);
  FlashHandle = osThreadCreate(osThread(Flash), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

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
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enables the Clock Security System
  */
  HAL_RCC_EnableCSS();
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 6;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = 2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = 3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = 4;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_7;
  sConfig.Rank = 5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_VREFINT;
  sConfig.Rank = 6;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 20;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 1000;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 41;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 1000;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_PWM_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */
  HAL_TIM_MspPostInit(&htim5);

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
  /* DMA1_Stream7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream7_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream7_IRQn);
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(DO_PC13_LED_GPIO_Port, DO_PC13_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DO_ARC_CHANGE_Pin|DO_SW_TEST_01_Pin|DO_SW_TEST_02_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : DO_PC13_LED_Pin */
  GPIO_InitStruct.Pin = DO_PC13_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DO_PC13_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DI_BUTTON_1_Pin DI_BUTTON_2_Pin */
  GPIO_InitStruct.Pin = DI_BUTTON_1_Pin|DI_BUTTON_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : AI_RESERVED_1_Pin DIO_RESERVED_0_Pin DIO_RESERVED_1_Pin RESERVED__SPI_CLK_Pin
                           RESERVED__SPI_MISO_Pin RESERVED__SPI_MOSI_Pin PB6 PB7 */
  GPIO_InitStruct.Pin = AI_RESERVED_1_Pin|DIO_RESERVED_0_Pin|DIO_RESERVED_1_Pin|RESERVED__SPI_CLK_Pin
                          |RESERVED__SPI_MISO_Pin|RESERVED__SPI_MOSI_Pin|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : DI_SWITCH_1_Pin */
  GPIO_InitStruct.Pin = DI_SWITCH_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(DI_SWITCH_1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : DI_IS_ARC_DRIVER_Pin */
  GPIO_InitStruct.Pin = DI_IS_ARC_DRIVER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(DI_IS_ARC_DRIVER_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DO_ARC_CHANGE_Pin DO_SW_TEST_01_Pin DO_SW_TEST_02_Pin */
  GPIO_InitStruct.Pin = DO_ARC_CHANGE_Pin|DO_SW_TEST_01_Pin|DO_SW_TEST_02_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : RESERVED__SPI_CS_Pin */
  GPIO_InitStruct.Pin = RESERVED__SPI_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(RESERVED__SPI_CS_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_TaskMesurarAdc */
/**
  * @brief  Function implementing the MesurarAdc thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_TaskMesurarAdc */
void TaskMesurarAdc(void const * argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 5 */
    TASKMESURAR_MainTask();
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_TaskPantalla */
/**
* @brief Function implementing the Pantalla thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskPantalla */
void TaskPantalla(void const * argument)
{
  /* USER CODE BEGIN TaskPantalla */
    TASKPANTALLA_MainTask();
  /* USER CODE END TaskPantalla */
}

/* USER CODE BEGIN Header_TaskParams */
/**
* @brief Function implementing the Params thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskParams */
void TaskParams(void const * argument)
{
  /* USER CODE BEGIN TaskParams */
    TASKPARAMS_MainTask();
  /* USER CODE END TaskParams */
}

/* USER CODE BEGIN Header_TaskFreeRtosMonitor */
/**
* @brief Function implementing the FreeRtosMonitor thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskFreeRtosMonitor */
void TaskFreeRtosMonitor(void const * argument)
{
  /* USER CODE BEGIN TaskFreeRtosMonitor */
    TASKFREERTOSMONITOR_MainTask();
  /* USER CODE END TaskFreeRtosMonitor */
}

/* USER CODE BEGIN Header_TaskFlash */
/**
* @brief Function implementing the Flash thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskFlash */
void TaskFlash(void const * argument)
{
  /* USER CODE BEGIN TaskFlash */
    TASKFLASH_MainTask();
  /* USER CODE END TaskFlash */
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
#ifdef USE_FULL_ASSERT
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
