#ifndef __HC_SR04_H
#define __HC_SR04_H

#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "delay.h"
#include "motor.h"

float HCSR04_GetDistance(void);
void avoid_obstacles_task(void);

#endif
