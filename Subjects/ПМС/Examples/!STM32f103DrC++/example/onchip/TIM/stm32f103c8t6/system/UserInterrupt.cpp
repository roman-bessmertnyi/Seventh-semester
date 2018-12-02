#include "UserInterrupt.h"

u8 cnt=0;

/*************************TIM_USER_IRQ***********************************/
#ifdef USE_TIMER1
void Timer1_IRQ()
{
	
}
#endif


#ifdef USE_TIMER2

void Timer2_IRQ()
{
	if (cnt) cnt = 0;
	else cnt = 1;
}
#endif

#ifdef USE_TIMER3
void Timer3_IRQ()
{
	
}
#endif

#ifdef USE_TIMER4
void Timer4_IRQ()
{
	
}
#endif

