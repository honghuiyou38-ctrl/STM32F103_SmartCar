#include "motor.h"

extern unsigned char buf[60];

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


//void Turn_Left_90(void)
//{
//    float start_yaw;
//
//    MPU6050_Read_Result();
//
// sprintf(buf,"pitch:%.2f roll:%.2f yaw:%.2f",pitch,roll,yaw);
//	     			  OLED_ShowString(0,0,buf,8);

//    start_yaw = yaw;
//
//    direction_Forward();
//
//    // 左轮停，右轮转
//    motor_PWM(0,35);
//
//    while(1)
//    {
//        MPU6050_Read_Result();
//
//
//        if((yaw - start_yaw) >= 85)
//        {
//            break;
//        }
//    }
//
//    motor_PWM(0,0);
//
//    HAL_Delay(100);
//}
//


