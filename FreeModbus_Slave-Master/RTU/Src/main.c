/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
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
#include "sys.h"
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"



/* USER CODE BEGIN Includes */
#include "bsp.h"
#include "mb_m.h"
#include "user_mb_app.h"
/* USER CODE END Includes */

extern USHORT 	usMRegInBuf[];	//master
extern USHORT  	usSRegInBuf[];	//slave

extern USHORT   usMRegHoldBuf[];
/////////////////////////////////////////////////////////////////////////////////////

/* Private variables ---------------------------------------------------------*/
__IO eMBMasterReqErrCode err;
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);


/* Private function prototypes -----------------------------------------------*/
//void MX_GPIO_Init(void);
//	
void UART(void);

uint32_t DataIP = 0;
float FData = 100.5;

int main(void)
{
	HAL_Init();
	SystemClock_Config(); 
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
  //////////////////////////////////
	//MX_GPIO_Init();
//	GPIO_Set(GPIOC,GPIO_PIN_12|GPIO_PIN_13,GPIO_MODE_OUTPUT_PP,GPIO_PULLUP,GPIO_SPEED_FREQ_LOW);

//	GPIO_Set(GPIOD,GPIO_PIN_12|GPIO_PIN_13,GPIO_MODE_OUTPUT_PP,GPIO_PULLUP,GPIO_SPEED_FREQ_LOW);

//	HAL_Delay(2000);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
//	
//	EXTIx_Init(GPIOA,GPIO_PIN_0, Trigger_Rising);
	
	pinMode(PC13,OUTPUT);
	digitalWrite( PC13, LOW );	
	delay(2000);
	UART();//debug
	
	MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  bsp_init();
	//delay(500);
	
	#if MB_MASTER_RTU_ENABLED > 0 || MB_MASTER_ASCII_ENABLED > 0
		eMBMasterInit(MB_RTU,0,115200,MB_PAR_EVEN);
  eMBMasterEnable();
	#endif
	#if MB_SLAVE_RTU_ENABLED >0 || MB_SLAVE_ASCII_ENABLED > 0 
		eMBInit(MB_RTU, 0x01, 0, 115200,  MB_PAR_EVEN);//ID=0x01
	eMBEnable();
	#endif
	
	
					int count = 0;
	
  while (1)
  {
		
		
//  	err=eMBMasterReqReadInputRegister(0x01,0x0000,5,200);//ID-ADD-Qty-TIMEOUT
//		delay(200);
//		err=eMBMasterReqReadHoldingRegister(0x01,0x0000,5,200);
//		delay(200);
//		err=eMBMasterReqReadDiscreteInputs(0x01,0x0000,16,200);
//		err=eMBMasterReqReadCoils(0x01,0x0000,16,200);
		
//		err = eMBMasterReqReadDiscreteInputs(1,3,8,200);
//		err = eMBMasterReqWriteMultipleCoils(1,3,5,ucModbusUserData,200);
//		err = eMBMasterReqWriteCoil(1,8,0xFF00,200);
//		err = eMBMasterReqReadCoils(1,3,8,200);
//		err = eMBMasterReqReadInputRegister(1,0,2,200);
//		err = eMBMasterReqWriteHoldingRegister(1,0,30,200);delay(200);
//		err = eMBMasterReqWriteMultipleHoldingRegister(1,2,1,usMRegHoldBuf,200);delay(200);
//		err = eMBMasterReqReadHoldingRegister(1,3,2,200);
//		err = eMBMasterReqReadWriteMultipleHoldingRegister(1,3,2,usModbusUserData,5,2,200);

  		
//  		//if (err == 0x00&&usMRegInBuf[1]==0x01)
//  		{
  			digitalWrite( PC13, LOW );
				for(int i = 0; i<99; i++)
				{
					usSRegInBuf[i]= i + count;
					count ++;
				}
				delay(50);
				digitalWrite( PC13, HIGH );	
				delay(50);
//				
//				printf("Data = %f - %d\r\n", FData,DataIP);
//				 
//  		}			

//			err=eMBMasterReqReadInputRegister(0x01,0x0000,5,200);//ID-ADD-Qty-TIMEOUT
//			delay(200);
//			eMBAccessDataCode stt = M_MBGetFloatData(REG_INPUT,  2, &FData);//add=2
			//if (stt == ACCESS_NO_ERR)
//			{
//				 //printf("Data = %f \r\n", FData);
//				//digitalWrite( PC13, LOW );	
////				//		err = eMBMasterReqWriteHoldingRegister(1,0,30,200);delay(200);
////				M_MBSetData16Bits(REG_HOLDING,  0, 10);
////				M_MBSetFloatData(REG_HOLDING,  2, 9999.99);
////				M_MBSetData32Bits(REG_HOLDING,  4, 3555999);
////				err = eMBMasterReqWriteMultipleHoldingRegister(1,0,10,usMRegHoldBuf,200);//add tu 0 deen Nreg =10
//				delay(500);
//				digitalWrite( PC13, HIGH );	
//				//M_MBSetFloatData(REG_HOLDING,  2, FData);
//				delay(500);
//			}
			
//		digitalWrite( PC13, LOW );	
//		delay(500);
//		digitalWrite( PC13, HIGH );
			//delay(500);
		

		
		
  }
  

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct ;
  RCC_ClkInitTypeDef RCC_ClkInitStruct ;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    //Error_Handler();
  }
  /* Initializes the CPU, AHB and APB busses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    //Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC | RCC_PERIPHCLK_USB;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    //Error_Handler();
  }

	
}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
//void MX_GPIO_Init(void)
//{

//  GPIO_InitTypeDef GPIO_InitStruct;

//  /* GPIO Ports Clock Enable */
//  __HAL_RCC_GPIOC_CLK_ENABLE();

//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

//  /*Configure GPIO pins : PC13 */
//  GPIO_InitStruct.Pin = GPIO_PIN_13;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

//}



UART_HandleTypeDef UartHandle;
void UART(void){
	
	GPIO_InitTypeDef  GPIO_InitStruct;
  
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO TX/RX clock */
  USARTx_TX_GPIO_CLK_ENABLE();
  USARTx_RX_GPIO_CLK_ENABLE();
  /* Enable USART2 clock */
  USARTx_CLK_ENABLE(); 
  
  /*##-2- Configure peripheral GPIO ##########################################*/  
  /* UART TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = USARTx_TX_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_NOPULL;
  
  HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);
    
  /* UART RX GPIO pin configuration  */
  GPIO_InitStruct.Pin = USARTx_RX_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_INPUT;
    
  HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);
	
	
	/*##-1- Configure the UART peripheral ######################################*/
  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
  /* UART1 configured as follow:
      - Word Length = 8 Bits
      - Stop Bit = One Stop bit
      - Parity = None
      - BaudRate = 9600 baud
      - Hardware flow control disabled (RTS and CTS signals) */
  UartHandle.Instance          = USART1;
  
  UartHandle.Init.BaudRate     = 115200;
  UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits     = UART_STOPBITS_1;
  UartHandle.Init.Parity       = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode         = UART_MODE_TX_RX;
  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
    
  if(HAL_UART_Init(&UartHandle) != HAL_OK)
  {
    Error_Handler();
  }
	
}


/* Printf handler */
 int fputc(int ch, FILE* fil) {//std::
	/* Send over USART */
	//USART_Putc(USART1, ch);
	 
	while (!(USART1->SR & UART_FLAG_TXE));
	USART1->DR = ch;
	while (!(USART1->SR & UART_FLAG_TXE));
	
	/* Return character */
	return ch;
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
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
 

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
