#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

/*-------------方向direction----------------------- 方向direction ----------------------*/
void direction_Forward(void);
void direction_Stop(void);
void direction_back(void);
/*-------------方向direction----------------------- 方向direction ----------------------*/


/*-------------速度speed-----------------------速度speed----------------------*/
void motor_PWM(uint8_t PWMA , uint8_t PWMB);
/*-------------速度speed-----------------------速度speed----------------------*/

#endif
