#include "shape.h"
#include "math.h"

extern unsigned char buf[60];

// 单段直线前进（边前进边更新yaw）
void forward_with_mpu(uint16_t time_ms, uint8_t speed)
{
    direction_Forward();
    motor_PWM(speed, speed);

    // 拆分延时，每5ms更新一次角度
    for(uint16_t i = 0; i < time_ms / 5; i++)
    {
        MPU6050_Read_Result();
        // 可选：OLED实时显示
        sprintf(buf,"pitch:%.2f roll:%.2f yaw:%.2f",pitch,roll,yaw);
        OLED_ShowString(0,0,buf,8);
        HAL_Delay(5);
    }
    motor_PWM(0, 0);
}

// 原地转指定角度（正数顺时针，负数逆时针）
void turn_by_angle(float angle, uint8_t speed)
{
    float start_yaw = yaw;
    float target_yaw = start_yaw + angle;

    // 启动转弯：右差速（左轮转，右轮停）
    // 如果实际转向反了，就改成 motor_PWM(0, speed);
    direction_Forward();
    motor_PWM(speed, 0);

    while(1)
    {
        MPU6050_Read_Result();
        // OLED实时显示
        sprintf(buf,"pitch:%.2f roll:%.2f yaw:%.2f",pitch,roll,yaw);
        OLED_ShowString(0,0,buf,8);

        float diff = fabs(target_yaw - yaw);

        // 接近目标减速，防止过冲
        if(diff < 10.0f)
        {
            motor_PWM(speed/2, 0);
        }

        // 到达目标角度（误差1°内）就停车
        if(diff < 1.0f)
        {
            motor_PWM(0, 0);
            break;
        }

        HAL_Delay(5);
    }
}

// 循环走正方形
void Square_trace(void)
{
    // 循环4次 = 4条边
    for(uint8_t i = 0; i < 4; i++)
    {
        // 1. 前进1.8秒
        forward_with_mpu(1800, 25);
        HAL_Delay(200); // 停稳再转弯

        // 2. 右转90度
        turn_by_angle(90.0f, 25);
        HAL_Delay(200);
    }
    // 跑完一圈自动结束，想无限循环就在外面套while(1)
}
