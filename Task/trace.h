#ifndef __TRACE_H
#define __TRACE_H

#include "main.h"
#include "gpio.h"
#include "motor.h"
#include "stdint.h"
#include "stdlib.h"


/*-----------获取循迹模块信息---------*/
void trace_get_value();
/*-----------获取循迹模块信息---------*/

/*--------------求偏差值------------*/
int trace_get_error();
/*--------------求偏差值------------*/

/*--------------任务逻辑------------*/
void trace_task();
/*--------------任务逻辑------------*/


/*--------------电赛task------------*/
void task_01();

#endif
