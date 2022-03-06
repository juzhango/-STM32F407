/*
 * @Author: luozw
 * @Date: 2022-01-05 13:50:59
 * @LastEditTime: 2022-01-07 10:48:30
 * @LastEditors: luozw
 * @Description:
 * @FilePath: \stm32-f407-explorer\2_fsms_sram_malloc\User\App\stm32f4xx_hal_msp.c
 * @version:
 * 可以输入预定的版权声明、个性签名、空行等
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "bsp.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Initializes the Global MSP.
 * @param  None
 * @retval None
 */
void HAL_MspInit(void)
{
}

/**
 * @brief  DeInitializes the Global MSP.
 * @param  None
 * @retval None
 */
void HAL_MspDeInit(void)
{
}

/**
 * @brief UART MSP Initialization
 *        This function configures the hardware resources used in this example:
 *           - Peripheral's clock enable
 *           - Peripheral's GPIO Configuration
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/*##-1- Enable peripherals and GPIO Clocks #################################*/
	/* Enable GPIO TX/RX clock */
	USARTx_TX_GPIO_CLK_ENABLE();
	USARTx_RX_GPIO_CLK_ENABLE();

	/* Enable USARTx clock */
	USARTx_CLK_ENABLE();

	/*##-2- Configure peripheral GPIO ##########################################*/
	/* UART TX GPIO pin configuration  */
	GPIO_InitStruct.Pin = USARTx_TX_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	GPIO_InitStruct.Alternate = USARTx_TX_AF;

	HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

	/* UART RX GPIO pin configuration  */
	GPIO_InitStruct.Pin = USARTx_RX_PIN;
	GPIO_InitStruct.Alternate = USARTx_RX_AF;

	HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);
}

/**
 * @brief UART MSP De-Initialization
 *        This function frees the hardware resources used in this example:
 *          - Disable the Peripheral's clock
 *          - Revert GPIO and NVIC configuration to their default state
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
	/*##-1- Reset peripherals ##################################################*/
	USARTx_FORCE_RESET();
	USARTx_RELEASE_RESET();

	/*##-2- Disable peripherals and GPIO Clocks #################################*/
	/* Configure UART Tx as alternate function  */
	HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT, USARTx_TX_PIN);
	/* Configure UART Rx as alternate function  */
	HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT, USARTx_RX_PIN);
}

/**
 * @brief TIM MSP Initialization
 *        This function configures the hardware resources used in this example:
 *           - Peripheral's clock enable
 *           - Peripheral's GPIO Configuration
 * @param htim: TIM handle pointer
 * @retval None
 */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM3)
	{
		/*##-1- Enable peripherals and GPIO Clocks #################################*/
		/* TIMx Peripheral clock enable */
		TIMx_CLK_ENABLE();

		/*##-2- Configure the NVIC for TIMx ########################################*/
		/* Set Interrupt Group Priority */
		HAL_NVIC_SetPriority(TIMx_IRQn, 4, 0);

		/* Enable the TIMx global Interrupt */
		HAL_NVIC_EnableIRQ(TIMx_IRQn);
	}
}

/**
 * @brief SRAM MSP Initialization
 *        This function configures the hardware resources used in this example:
 *           - Peripheral's clock enable
 *           - Peripheral's GPIO Configuration
 * @param hsram: SRAM handle pointer
 * @retval None
 */
void HAL_SRAM_MspInit(SRAM_HandleTypeDef *hsram)
{
	GPIO_InitTypeDef GPIO_Init_Structure;

	/* Enable FSMC clock */
	__HAL_RCC_FSMC_CLK_ENABLE();

	/* Enable GPIOs clock */
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

	/* Common GPIO configuration */
	GPIO_Init_Structure.Mode = GPIO_MODE_AF_PP;
	GPIO_Init_Structure.Pull = GPIO_NOPULL;
	GPIO_Init_Structure.Speed = GPIO_SPEED_HIGH;
	GPIO_Init_Structure.Alternate = GPIO_AF12_FSMC;

	/* GPIOD configuration */
	GPIO_Init_Structure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8 |
							  GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 |
							  GPIO_PIN_14 | GPIO_PIN_15;

	HAL_GPIO_Init(GPIOD, &GPIO_Init_Structure);

	/* GPIOE configuration */
	GPIO_Init_Structure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7 |
							  GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 |
							  GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	HAL_GPIO_Init(GPIOE, &GPIO_Init_Structure);

	/* GPIOF configuration */
	GPIO_Init_Structure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 |
							  GPIO_PIN_5 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	HAL_GPIO_Init(GPIOF, &GPIO_Init_Structure);

	/* GPIOG configuration */
	GPIO_Init_Structure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 |
							  GPIO_PIN_5 | GPIO_PIN_10 | GPIO_PIN_12;
	HAL_GPIO_Init(GPIOG, &GPIO_Init_Structure);
}

/**
 * @brief SRAM MSP De-Initialization
 *        This function frees the hardware resources used in this example:
 *          - Disable the Peripheral's clock
 *          - Revert GPIO configuration to their default state
 * @param hsram: SRAM handle pointer
 * @retval None
 */
void HAL_SRAM_MspDeInit(SRAM_HandleTypeDef *hsram)
{
	/*## Disable peripherals and GPIO Clocks ###################################*/
	/* Configure FSMC as alternate function  */
	HAL_GPIO_DeInit(GPIOD, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 |
							   GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 |
							   GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);

	HAL_GPIO_DeInit(GPIOE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7 |
							   GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 |
							   GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);

	HAL_GPIO_DeInit(GPIOF, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 |
							   GPIO_PIN_5 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);

	HAL_GPIO_DeInit(GPIOG, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 |
							   GPIO_PIN_5 | GPIO_PIN_10 | GPIO_PIN_12);
}


/**
 * @brief  Initializes the SD MSP.
 * @param  hsd: SD handle
 * @param  Params : pointer on additional configuration parameters, can be NULL.
 */
void HAL_SD_MspInit(SD_HandleTypeDef *hsd)
{
    DMA_HandleTypeDef dmaRxHandle;
    DMA_HandleTypeDef dmaTxHandle;
    GPIO_InitTypeDef GPIO_Init_Structure;

    /* Enable SDIO clock */
    __HAL_RCC_SDIO_CLK_ENABLE();

    /* Enable DMA2 clocks */
    __DMAx_TxRx_CLK_ENABLE();

    /* Enable GPIOs clock */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    /* Common GPIO configuration */
    GPIO_Init_Structure.Mode = GPIO_MODE_AF_PP;
    GPIO_Init_Structure.Pull = GPIO_PULLUP;
    GPIO_Init_Structure.Speed = GPIO_SPEED_HIGH;
    GPIO_Init_Structure.Alternate = GPIO_AF12_SDIO;

    /* GPIOC configuration */
    GPIO_Init_Structure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
    HAL_GPIO_Init(GPIOC, &GPIO_Init_Structure);

    /* GPIOD configuration */
    GPIO_Init_Structure.Pin = GPIO_PIN_2;
    HAL_GPIO_Init(GPIOD, &GPIO_Init_Structure);

#if (SD_DMA_MODE==1) 
    /* NVIC configuration for SDIO interrupts */
    HAL_NVIC_SetPriority(SDIO_IRQn, 0x0E, 0);
    HAL_NVIC_EnableIRQ(SDIO_IRQn);

    /* Configure DMA Rx parameters */
    dmaRxHandle.Init.Channel = SD_DMAx_Rx_CHANNEL;
    dmaRxHandle.Init.Direction = DMA_PERIPH_TO_MEMORY;
    dmaRxHandle.Init.PeriphInc = DMA_PINC_DISABLE;
    dmaRxHandle.Init.MemInc = DMA_MINC_ENABLE;
    dmaRxHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    dmaRxHandle.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    dmaRxHandle.Init.Mode = DMA_PFCTRL;
    dmaRxHandle.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    dmaRxHandle.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
    dmaRxHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    dmaRxHandle.Init.MemBurst = DMA_MBURST_INC4;
    dmaRxHandle.Init.PeriphBurst = DMA_PBURST_INC4;

    dmaRxHandle.Instance = SD_DMAx_Rx_STREAM;

    /* Associate the DMA handle */
    __HAL_LINKDMA(hsd, hdmarx, dmaRxHandle);

    /* Deinitialize the stream for new transfer */
    HAL_DMA_DeInit(&dmaRxHandle);

    /* Configure the DMA stream */
    HAL_DMA_Init(&dmaRxHandle);

    /* Configure DMA Tx parameters */
    dmaTxHandle.Init.Channel = SD_DMAx_Tx_CHANNEL;
    dmaTxHandle.Init.Direction = DMA_MEMORY_TO_PERIPH;
    dmaTxHandle.Init.PeriphInc = DMA_PINC_DISABLE;
    dmaTxHandle.Init.MemInc = DMA_MINC_ENABLE;
    dmaTxHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    dmaTxHandle.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    dmaTxHandle.Init.Mode = DMA_PFCTRL;
    dmaTxHandle.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    dmaTxHandle.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
    dmaTxHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    dmaTxHandle.Init.MemBurst = DMA_MBURST_INC4;
    dmaTxHandle.Init.PeriphBurst = DMA_PBURST_INC4;

    dmaTxHandle.Instance = SD_DMAx_Tx_STREAM;
	
    /* Associate the DMA handle */
    __HAL_LINKDMA(hsd, hdmatx, dmaTxHandle);

    /* Deinitialize the stream for new transfer */
    HAL_DMA_DeInit(&dmaTxHandle);

    /* Configure the DMA stream */
    HAL_DMA_Init(&dmaTxHandle);

    /* NVIC configuration for DMA transfer complete interrupt */
    HAL_NVIC_SetPriority(SD_DMAx_Rx_IRQn, 0x0F, 0);
    HAL_NVIC_EnableIRQ(SD_DMAx_Rx_IRQn);

    /* NVIC configuration for DMA transfer complete interrupt */
    HAL_NVIC_SetPriority(SD_DMAx_Tx_IRQn, 0x0F, 0);
    HAL_NVIC_EnableIRQ(SD_DMAx_Tx_IRQn);
#endif	
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
