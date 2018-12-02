#include "brown_delay.h"

static __IO uint32_t TimingDelay;

void sys_tick_ini(void){
if (SysTick_Config(SystemCoreClock / 1000))
            while (1);
}
void delay_from_Brown(uint32_t nTime){
    TimingDelay = nTime;
    while(TimingDelay != 0);
}

void SysTick_Handler(void){
    if (TimingDelay != 0x00)
        TimingDelay --;
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file , uint32_t line)
{
/* Infinite loop */
/* Use GDB to find out why we're here */
while (1);
}
#endif
