#include "key.h"

extern uint8_t OLED_refresh_flag;
extern _Bool LED1_State;
extern uint8_t mode_flag;
extern _Bool mpu_Refresh;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin)==0)
	{
		OLED_refresh_flag=2;
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		LED1_State=!LED1_State;
	}

}
