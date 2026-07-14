#include "delay.h"

static uint32_t us_factor = 0;

void DWT_Init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;   // 使能DWT
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;              // 开启计数器
    DWT->CYCCNT = 0;

    us_factor = HAL_RCC_GetHCLKFreq() / 1000000;
}

void delay_us(uint32_t us)
{
    uint32_t start = DWT->CYCCNT;
    uint32_t ticks = us * us_factor;

    while ((DWT->CYCCNT - start) < ticks);
}
