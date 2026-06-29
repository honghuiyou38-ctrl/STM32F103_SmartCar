#include "motor.h"


/*-------------方向direction----------------------- 方向direction ----------------------*/

void direction_Forward(void)  //控制反向前进
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 0);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
}

void direction_Stop(void) //停止
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 0);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
}

void direction_back(void)  //方向后退
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 1);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);

}
/*------------------------方向direction------------------方向direction---------------*/


/*-------------速度speed-----------------------速度speed----------------------*/
void motor_PWM(uint8_t PWMA , uint8_t PWMB)
{
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, PWMA);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, PWMB);
}
/*-------------速度speed-----------------------速度speed----------------------*/

