#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "timer_lib.h"
#include "tm1637.h"

#define STATE_GET_TIMER_INPUT 1
#define STATE_IDLE 0

#define TIMER_NO_INPUT 410 
#define TIMER_INPUT_IS_ZERO 404

#define PERIOD 2000 // probably miliseconds

volatile uint16_t PPMBuffer = 0x0000;
volatile uint16_t PPMValue_Prev, PPMValue;

volatile uint16_t finite_state = STATE_IDLE;

void TIM2_IRQHandler(void){
    volatile uint16_t PPM;
 
    if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)
      {
        /* Reset flag */
        TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);
 
        PPMValue_Prev = PPMValue;
        PPMValue = TIM_GetCapture2(TIM2);
        PPM = (PPMValue >= PPMValue_Prev) ? (PPMValue - PPMValue_Prev) : (UINT16_MAX - PPMValue_Prev + PPMValue);
        if (PPM < 10000) { // Pause
            PPMBuffer = PPM;
        }
				else PPMBuffer = 9999;
 
        /* over-capture */
        if (TIM_GetFlagStatus(TIM2, TIM_FLAG_CC2OF) != RESET)
        {
          TIM_ClearFlag(TIM2, TIM_FLAG_CC2OF);
          // ...
        }
      }
}

void TIM3_IRQHandler(void){
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		finite_state = STATE_GET_TIMER_INPUT;
	}
}

int main(void)
{
	SetSysClockTo72();
	TIMER2_input_init_A2(7200);
	TIMER4_PWM_init_B8(72, PERIOD);
	TIMER3_init(7200, 1000);
	
	double pulse_width = 0.01;
	TIM4->CCR3 = PERIOD * pulse_width;
	
	TM1637_init();	
	TM1637_brightness(BRIGHTEST);
	TM1637_display_all(TIMER_NO_INPUT);
	
	while(1)
	{
		switch(finite_state)
		{
			case STATE_GET_TIMER_INPUT:
				if (PPMBuffer != 0)
				{
					TM1637_display_all(PPMBuffer);
				}
				else
				{
					TM1637_display_all(TIMER_INPUT_IS_ZERO);
				}
			
				finite_state = STATE_IDLE;
				break;
		}
	}
}
