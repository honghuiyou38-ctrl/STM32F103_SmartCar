#include "key.h"

extern uint8_t OLED_refresh_flag;
extern _Bool LED1_State;
extern _Bool LED2_State;
extern uint8_t mode_flag;
extern _Bool mpu_Refresh;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==KEY0_Pin)
	{
		OLED_refresh_flag=2;
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		LED1_State=!LED1_State;
	}

	if(GPIO_Pin==KEY1_Pin)
	{
		OLED_refresh_flag=2;
		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		LED2_State=!LED2_State;
	}
}
