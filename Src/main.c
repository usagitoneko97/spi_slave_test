/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l0xx_hal.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint8_t tempBuffer;
uint8_t dataRead[3] = {0};
uint8_t NEED_WIFI = 0x2;
uint8_t WIFI_DATA = 0x3;
uint8_t* Wifissid;
uint8_t* WifiPw;
const uint8_t ANDROID_THERE = 0x1f;
const uint8_t NEED = 1;
const uint8_t XNEED = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
uint8_t readAndroidThereNFC();
void needWifiSPI();
uint8_t* receiveWifiSSID();
uint8_t* receiveWifiPw();
void WriteSsidToEEPROM(uint8_t* Ssid);
void WritePwToEEPROM(uint8_t* Pw);
void WriteAndroidConfirmationToEEPROM();
int isAndroidThere();
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();

  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	  /*if(HAL_GPIO_ReadPin(CS_GPIO_Port, CS_Pin) == GPIO_PIN_RESET){
	 		  //HAL_Delay(50);
	 		status =  HAL_SPI_Receive(&hspi1, (uint8_t*)data, 1, 5000);
	 		 HAL_Delay(50);
	 	  }*/
 			/*do
	 	    {
	 	      if (HAL_SPI_TransmitReceive(&hspi1, (uint8_t *)&txackbyte, (uint8_t *)&rxackbyte, 1, 1000) != HAL_OK)
	 	      {
	 	        Error_Handler();
	 	      }
	 	    }*/
	 	    //while (rxackbyte != 0x73);

//
	  	  	while(1) {
	  	  		/*while(readAndroidThereNFC() != ANDROID_THERE){
	  	  			HAL_Delay(50);	//a small delay
	  	  		}*/
	  	  		//send confirmation to spi
	  	  		//receive ssid and pw from spi
	  	  		//write ssid and pw to eeprom
	  	  		//write confirmation byte to eeprom

	  	  		/*SPI teritory*/
	  	  		//NOTE: default ssid and pw to 8 bytes for simplicity
	  	  		while(__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_RXNE) == RESET);
	  	  		HAL_SPI_Receive(&hspi1, &tempBuffer, 1, 5000);
	  	  		if(tempBuffer == NEED_WIFI){
	  	  			if(isAndroidThere()==0){
	  	  				needWifiSPI();
	  	  			}
	  	  			else{
	  	  				xneedWifiSPI();
	  	  			}
	  	  		}
	  	  		else if(tempBuffer == WIFI_DATA){

	  	  		}
	  	  		/*Wifissid = receiveWifiSSID();
	  	  		WifiPw = receiveWifiPw();*/

	  	  		/*NFC teritory*/
	  	  		/*WriteSsidToEEPROM(Wifissid);
	  	  		WritePwToEEPROM(WifiPw);
	  	  		WriteAndroidConfirmationToEEPROM();*/

	  	  	}

	 	    //HAL_Delay(50);
	 	    //HAL_SPI_Transmit(&hspi1, &data1, 1, 1000);//overwrite any previous data
	 	    //if(dataRead!=0xfd)
	 	    	//HAL_Delay(50);
	 	   // while(1){
	 	    //	volatile i =0;
	 	    	//i++;
	 	   // }

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* SPI1 init function */
static void MX_SPI1_Init(void)
{

  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_SLAVE;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin : PushButton_Pin */
  GPIO_InitStruct.Pin = PushButton_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(PushButton_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi){
	volatile int i;
	i++;
}
uint8_t readAndroidThereNFC(){
	return 0xf;
}

int isAndroidThere(){
	/*using push button to stimulate the response*/
	return (HAL_GPIO_ReadPin(PushButton_GPIO_Port, PushButton_Pin));
}
void needWifiSPI(){
	HAL_SPI_Transmit(&hspi1, &NEED, 1, 500);
}
void xneedWifiSPI(){
	HAL_SPI_Transmit(&hspi1, &XNEED, 1, 500);
}
uint8_t* receiveWifiSSID(){
	uint8_t Wifissid [8] = {0};
	int i;
	for(i = 0;i<8;i++){
		while(__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_RXNE) == RESET);
		HAL_SPI_Receive(&hspi1, Wifissid+i, 1, 5000);
	}
	return Wifissid;
}
uint8_t* receiveWifiPw(){
	uint8_t WifiPw[8] = {0};
	int i;
	for(i = 0;i<8;i++){
		while(__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_RXNE) == RESET);
		HAL_SPI_Receive(&hspi1, WifiPw+i, 1, 5000);
	}
	return WifiPw;
}
void WriteSsidToEEPROM(uint8_t* Ssid){
}
void WritePwToEEPROM(uint8_t* Pw){
}
void WriteAndroidConfirmationToEEPROM(){
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
