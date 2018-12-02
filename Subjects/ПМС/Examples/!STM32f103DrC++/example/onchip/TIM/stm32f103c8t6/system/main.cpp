#include "USART.h"
#include "GPIO.h"
#include "Timer.h"
#include "Delay.h"
#include "UserInterrupt.h"

//USART usart(1,115200,false);
Timer tim(TIM2,1,0,0);
GPIO B3Led(GPIOB,3,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);

int main()
{
	tim.OnOrOffIrq(true);
	tim.Start();
	
	B3Led.DisableSWJTAG(false,true);
	
	while(1)
	{
		//usart<<cnt<<"\n";
		if (cnt) B3Led.Toggle();
		Delay::Ms(100);
	}
}

