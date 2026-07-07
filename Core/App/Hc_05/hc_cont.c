#include "hc_cont.h"

extern uint8_t wheel_PWM_A;
extern uint8_t wheel_PWM_B;
extern uint8_t mode_flag;
extern uint8_t UART_recv_idle[UART_recv_idle_Size];
extern _Bool OLED_refresh_flag;
extern _Bool mpu_flag;
extern _Bool mpu_Refresh;

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if(huart==&huart1)
	{
		if(strcmp((char *)UART_recv_idle,"front")==0)
		{
			mode_flag=1;
			wheel_PWM_A=50;
			wheel_PWM_B=50;
			memset(UART_recv_idle,'\0',Size);
			OLED_refresh_flag=1;
		}

		if(strcmp((char *)UART_recv_idle,"left")==0)
		{
			mode_flag=1;
			wheel_PWM_A=50;
			wheel_PWM_B=10;
			memset(UART_recv_idle,'\0',Size);
			OLED_refresh_flag=1;
		}

		if(strcmp((char *)UART_recv_idle,"right")==0)
		{
			mode_flag=1;
			wheel_PWM_A=10;
			wheel_PWM_B=50;
			memset(UART_recv_idle,'\0',Size);
			OLED_refresh_flag=1;
		}

		if(strcmp((char *)UART_recv_idle,"stop")==0)
		{
			mode_flag=1;
			wheel_PWM_A=0;
			wheel_PWM_B=0;
			memset(UART_recv_idle,'\0',Size);
			OLED_refresh_flag=1;
		}

		if(strcmp((char *)UART_recv_idle,"back")==0)
		{
			mode_flag=2;
			wheel_PWM_A=30;
			wheel_PWM_B=30;
			memset(UART_recv_idle,'\0',Size);
			OLED_refresh_flag=1;
		}

		if(strcmp((char *)UART_recv_idle,"rightB")==0)
		{
			mode_flag=2;
			wheel_PWM_A=5;
			wheel_PWM_B=30;
			memset(UART_recv_idle,'\0',Size);
			OLED_refresh_flag=1;
		}

		if(strcmp((char *)UART_recv_idle,"leftB")==0)
		{
			mode_flag=2;
			wheel_PWM_A=30;
			wheel_PWM_B=5;
			memset(UART_recv_idle,'\0',Size);
			OLED_refresh_flag=1;
		}

//		if(strcmp((char *)UART_recv_idle,"MPUON")==0)
//		{
//			mpu_flag=1;
//			memset(UART_recv_idle,'\0',Size);
//			mpu_Refresh=1;
//		}
//
//		if(strcmp((char *)UART_recv_idle,"MPUOFF")==0)
//		{
//			mpu_flag=0;
//			memset(UART_recv_idle,'\0',Size);
//			mpu_Refresh=1;
//		}

	}

	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, UART_recv_idle, UART_recv_idle_Size);
}
