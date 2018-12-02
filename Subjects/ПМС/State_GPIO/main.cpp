#include "Singletons.h"
#include "timer_lib.h"

//TODO: use C++ timer libs
extern "C" void TIM3_IRQHandler(void){
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		stateContext.Execute(); //TODO: move to main
	}
}

int main()
{
	SetSysClockTo72(); //TODO: use C++ timer libs
	TIMER3_init(7200, 10000); // 1 second
	
	B3Led.DisableSWJTAG(false,true);
	while(1){}
}
