#include "trace.h"

extern TIM_HandleTypeDef htim3;

static int weight[8]={-14,-5,-3,-1,1,3,5,14};
uint8_t sensor[8];
int Error_trace=0;
int Last_Error_trace=0;
int Last_PWM_A;
int Last_PWM_B;

/*-----------获取循迹模块信息---------*/
void trace_get_value()
{
	sensor[0]=HAL_GPIO_ReadPin(X1_GPIO_Port, X1_Pin);
	sensor[1]=HAL_GPIO_ReadPin(X2_GPIO_Port, X2_Pin);
	sensor[2]=HAL_GPIO_ReadPin(X3_GPIO_Port, X3_Pin);
	sensor[3]=HAL_GPIO_ReadPin(X4_GPIO_Port, X4_Pin);
	sensor[4]=HAL_GPIO_ReadPin(X5_GPIO_Port, X5_Pin);
	sensor[5]=HAL_GPIO_ReadPin(X6_GPIO_Port, X6_Pin);
	sensor[6]=HAL_GPIO_ReadPin(X7_GPIO_Port, X7_Pin);
	sensor[7]=HAL_GPIO_ReadPin(X8_GPIO_Port, X8_Pin);
}
/*-----------获取循迹模块信息---------*/


/*--------------求偏差值------------*/
int trace_get_error()
{
	int sum_trace=0;
	int count_trace=0;
	int i;

	for(i=0;i<8;i++)
	{
		if(sensor[i]==0)
		{
			sum_trace+=weight[i];
			count_trace++;
		}
	}

	if(count_trace==0)
	{
		Error_trace=Last_Error_trace;
	}
	else
	{
		Error_trace=sum_trace/count_trace;
		Last_Error_trace=Error_trace;
	}

	return Error_trace;
}
/*--------------求偏差值------------*/


/*--------------任务逻辑------------*/
void trace_task()
{
	int PWM_base;
	if(abs(Error_trace)>=4)
	{
		PWM_base=15;
	}
	else
	{
		PWM_base=23;
	}
	int kp=5;

	int PWM_A;
	int PWM_B;

	trace_get_value();
	trace_get_error();
/*-------------------循迹logic----------------------------循迹logic-------------------循迹logic-------------------循迹logic--------------------------------------------------------*/


////*--------------特殊转弯处理-------------*//
//	///*----------------右转特殊---------------*///
//	if(sensor[0]==1 && sensor[1]==1 && sensor[2]==0 && sensor[3]==0 && sensor[4]==0 && sensor[5]==0 && sensor[6]==0 && sensor[7]==0)
//	{
//		PWM_A=0;
//		PWM_B=30;
//	}
//	 if(sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==0 && sensor[4]==0 && sensor[5]==0 && sensor[6]==0 && sensor[7]==0)
//	{
//		 PWM_A=0;
//		 PWM_B=0;
//		 HAL_Delay(300);
//		PWM_A=0;
//		PWM_B=40;
//
//	}
//	 if(sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==1 && sensor[4]==0 && sensor[5]==0 && sensor[6]==0 && sensor[7]==0)
//	{
//		PWM_A=0;
//		PWM_B=60;
//	}
//	else if(sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==1 && sensor[4]==1 && sensor[5]==0 && sensor[6]==0 && sensor[7]==0)
//	{
//		PWM_A=0;
//		PWM_B=45;
//	}
//
//	///*----------------右转特殊---------------*///
//
//	///*----------------左转特殊---------------*///
//
//	else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && sensor[3]==1 && sensor[4]==1 && sensor[5]==1 && sensor[6]==1 && sensor[7]==1)
//	{
//		PWM_A=45;
//		PWM_B=0;
//	}
//	else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && sensor[3]==0 && sensor[4]==1 && sensor[5]==1 && sensor[6]==1 && sensor[7]==1)
//	{
//		PWM_A=60;
//		PWM_B=0;
//	}
//	else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && sensor[3]==0 && sensor[4]==0 && sensor[5]==1 && sensor[6]==1 && sensor[7]==1)
//	{
//		PWM_A=0;
//		PWM_B=0;
//		HAL_Delay(300);
//		PWM_A=40;
//		PWM_B=0;
//	}
//	else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && sensor[3]==0 && sensor[4]==0 && sensor[5]==0 && sensor[6]==1 && sensor[7]==1)
//	{
//		PWM_A=30;
//		PWM_B=0;
//	}
//	///*----------------左转特殊----------------*///


	///*--------------丢线/大角度偏离-------------*///
	if(sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==1 && sensor[4]==1 && sensor[5]==1 && sensor[6]==1 && sensor[7]==1)
	{
		PWM_A=Last_PWM_A;
		PWM_B=Last_PWM_B;
	}
	else if(sensor[0]==0 && sensor[1]==0 && sensor[2]==0 && sensor[3]==0 && sensor[4]==0 && sensor[5]==0 && sensor[6]==0 && sensor[7]==0)
	{
		PWM_A=Last_PWM_A;
		PWM_B=Last_PWM_B;
	}
	else if(sensor[0]==1 && sensor[1]==0 && sensor[2]==0 && sensor[3]==0 && sensor[4]==0 && sensor[5]==0 && sensor[6]==0 && sensor[7]==1)
	{
		PWM_A=Last_PWM_A;
		PWM_B=Last_PWM_B;
	}
//	else if(sensor[0]==1 && sensor[1]==0 && sensor[2]==0 && sensor[3]==0 && sensor[4]==0 && sensor[5]==1 && sensor[6]==1 && sensor[7]==1)
//	{
//		PWM_A=50;
//		PWM_B=0;
//	}
//	else if(sensor[0]==1 && sensor[1]==1 && sensor[2]==1 && sensor[3]==0 && sensor[4]==0 && sensor[5]==0 && sensor[6]==0 && sensor[7]==1)
//	{
//		PWM_A=0;
//		PWM_B=50;
//	}
	///*---------------丢线/大角度偏离-------------*///

//*--------------特殊转弯处理-------------*//


//*--------------常规循迹计算-------------*//
	else
	{
		PWM_A=PWM_base-Error_trace*kp;
		PWM_B=PWM_base+Error_trace*kp;

		if(PWM_A>99){PWM_A=99;}
		if(PWM_A<0){PWM_A=0;}

		if(PWM_B>99){PWM_B=99;}
		if(PWM_B<0){PWM_B=0;}
	}
//*--------------常规循迹计算-------------*//

	Last_PWM_A=PWM_A;
	Last_PWM_B=PWM_B;

	motor_PWM(PWM_A , PWM_B);



/*-------------------循迹logic----------------------------循迹logic-------------------循迹logic-------------------循迹logic--------------------------------------------------------*/
}






