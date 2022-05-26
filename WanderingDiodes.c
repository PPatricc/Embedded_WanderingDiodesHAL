
#include "main.h"

#define DELAY 30000
#define TOGGLE_DELAY 15000

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

typedef enum
{
    LEFT = 1,
    RIGHT = -1
}direction;

void MyToggle(int WhichToToggle){
    switch (WhichToToggle) {
        case 0:
            HAL_GPIO_TogglePin(GPIOC,Dioda0_Pin);
            for(int i=0;i<DELAY;i++)
            {
                if(i==TOGGLE_DELAY)
                {
                    HAL_GPIO_TogglePin(GPIOC,Dioda0_Pin);
                }
            }
            break;
        case 1:
            HAL_GPIO_TogglePin(GPIOC,Dioda1_Pin);
            for(int i=0;i<DELAY;i++)
            {
                if(i == TOGGLE_DELAY)
                {
                    HAL_GPIO_TogglePin(GPIOC,Dioda1_Pin);
                }
            }
            break;
        case 2:
            HAL_GPIO_TogglePin(GPIOC,Dioda2_Pin);
            for(int i=0;i<DELAY;i++)
			{
                if(i==TOGGLE_DELAY)
				{
                    HAL_GPIO_TogglePin(GPIOC,Dioda2_Pin);
                }
            }
            break;
        case 3:
            HAL_GPIO_TogglePin(GPIOC,Dioda3_Pin);
            for(int i=0;i<DELAY;i++)
			{
                if(i==TOGGLE_DELAY)
				{
                    HAL_GPIO_TogglePin(GPIOC,Dioda3_Pin);
                }
            }
            break;
        case 4:
            HAL_GPIO_TogglePin(GPIOE,Dioda4_Pin);
            for(int i=0;i<DELAY;i++)
			{
                if(i==TOGGLE_DELAY)
				{
                    HAL_GPIO_TogglePin(GPIOE,Dioda4_Pin);
                }
            }
            break;
        case 5:
            HAL_GPIO_TogglePin(GPIOD,Dioda5_Pin);
            for(int i=0;i<DELAY;i++)
			{
                if(i==TOGGLE_DELAY)
				{
                    HAL_GPIO_TogglePin(GPIOD,Dioda5_Pin);
                }
            }
            break;
        case 6:
            HAL_GPIO_TogglePin(GPIOE,Dioda6_Pin);
            for(int i=0;i<DELAY;i++)
			{
                if(i==TOGGLE_DELAY)
				{
                    HAL_GPIO_TogglePin(GPIOE,Dioda6_Pin);
                }
            }
            break;
        case 7:
            HAL_GPIO_TogglePin(GPIOE,Dioda7_Pin);
            for(int i=0;i<DELAY;i++)
			{
                if(i==TOGGLE_DELAY)
				{
                    HAL_GPIO_TogglePin(GPIOE,Dioda7_Pin);
                }
            }
            break;

    }

}

int main(void)
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();

    HAL_GPIO_WritePin(GPIOC,Dioda0_Pin | Dioda1_Pin | Dioda2_Pin | Dioda3_Pin | Dioda4_Pin | Dioda5_Pin | Dioda6_Pin | Dioda7_Pin,GPIO_PIN_RESET);


    uint16_t counter = 0;
    direction d = LEFT;
    uint8_t toggle=0;
    uint16_t counterOfDelay=0;

  while (1)
  {
   
	  MyToggle(counter);

	  if(toggle==0){
		  if(HAL_GPIO_ReadPin(GPIOE, DiodaOK_Pin)==GPIO_PIN_RESET){
			  if(d==LEFT){
				  d=RIGHT;
			  }
			  else{
				  d=LEFT;
			  }
			 toggle=1;
		  }
	  }

		  if(counterOfDelay>5){
			  toggle=0;
			  counterOfDelay=0;
		  }

		  if(counter >=7){
			  d=RIGHT;
		  }
		  if(counter <=0){
			  d=LEFT;
		  }

	  	  counter +=d;

    
		  counterOfDelay++;
  }
  
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};


  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

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
}


static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

 
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  
  HAL_GPIO_WritePin(GPIOE, Dioda4_Pin|Dioda6_Pin|Dioda7_Pin, GPIO_PIN_RESET);

  
  HAL_GPIO_WritePin(GPIOC, Dioda0_Pin|Dioda1_Pin|Dioda2_Pin|Dioda3_Pin, GPIO_PIN_RESET);

  
  HAL_GPIO_WritePin(Dioda5_GPIO_Port, Dioda5_Pin, GPIO_PIN_RESET);

  
  GPIO_InitStruct.Pin = Dioda4_Pin|Dioda6_Pin|Dioda7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  
  GPIO_InitStruct.Pin = DiodaOK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DiodaOK_GPIO_Port, &GPIO_InitStruct);

  
  GPIO_InitStruct.Pin = Dioda0_Pin|Dioda1_Pin|Dioda2_Pin|Dioda3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  
  GPIO_InitStruct.Pin = Dioda5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Dioda5_GPIO_Port, &GPIO_InitStruct);

}


void Error_Handler(void)
{

  __disable_irq();
  while (1)
  {
  }
  
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif /* USE_FULL_ASSERT */

