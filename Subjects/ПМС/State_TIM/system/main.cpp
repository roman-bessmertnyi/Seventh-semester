#include "Singletons.h"
#include "Timer.h"


Timer tim(TIM2,0,100,0);

int main()
{
	tim.OnOrOffIrq(true);
	tim.Start();
	
	B3Led.DisableSWJTAG(false,true);
	
	while(1){
		stateContext.Execute();
	}
}
