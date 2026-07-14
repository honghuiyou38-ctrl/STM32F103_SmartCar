#include "hc_sr04.h"

float Distance;
float last_Distance=0;

float HCSR04_GetDistance(void)
{
    uint32_t Time;
    uint32_t Timeout;


    /*---------------发送Trig---------------*/

    HAL_GPIO_WritePin(Trig_GPIO_Port,Trig_Pin,GPIO_PIN_RESET);
    delay_us(2);

    HAL_GPIO_WritePin(Trig_GPIO_Port,Trig_Pin,GPIO_PIN_SET);
    delay_us(10);

    HAL_GPIO_WritePin(Trig_GPIO_Port,Trig_Pin,GPIO_PIN_RESET);

    /*-----------等待Echo变高--------------*/

    Timeout = 30000;

    while(HAL_GPIO_ReadPin(Echo_GPIO_Port,Echo_Pin)==GPIO_PIN_RESET)
    {
        Timeout--;

        if(Timeout==0)
        {
            return -1;
        }
    }

    /*-------------开始计时----------------*/

    __HAL_TIM_SET_COUNTER(&htim2,0);

    /*-----------等待Echo变低--------------*/

    Timeout = 30000;

    while(HAL_GPIO_ReadPin(Echo_GPIO_Port,Echo_Pin)==GPIO_PIN_SET)
    {
        Timeout--;

        if(Timeout==0)
        {
            return -1;
        }
    }

    /*-------------读取时间----------------*/

    Time = __HAL_TIM_GET_COUNTER(&htim2);

    /*------------计算距离(cm)-------------*/


    return Time * 0.0343f / 2.0f;;

}


void avoid_obstacles_task(void)
{
	OLED_ShowString(0,0,"Avoid_ob MODE",16);
	Distance = HCSR04_GetDistance();

	if(Distance != -1)
	{
	    last_Distance = Distance;
	}
	else
	{
	    Distance = last_Distance;
	}

	direction_Forward();

	if(Distance>=25)
	{
		motor_PWM(35 , 35);
	}
	else
	{
		motor_PWM(0 , 0);
		HAL_Delay(200);

		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 25);
		HAL_Delay(700);
		float dis_left=HCSR04_GetDistance();

		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 5);
		HAL_Delay(700);
		float dis_right=HCSR04_GetDistance();

		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 15);
		HAL_Delay(300);

			// 对比左右距离，往空旷一侧原地转弯
		if(dis_left > dis_right)
		{
				// 左边更远，原地左转（左轮负、右轮正）
			motor_PWM(30, 0);
			HAL_Delay(650);  // 转弯时长，地面滑缩短，摩擦力大拉长
		}
		else
		{
				// 右边更远，原地右转
			motor_PWM(0, 30);
			HAL_Delay(650);
		}

			// 转弯完成，恢复直行等待下一轮检测
		motor_PWM(35, 35);
		HAL_Delay(100);
	}

}





