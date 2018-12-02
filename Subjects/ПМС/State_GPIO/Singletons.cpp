//TODO: remove this

#include "Singletons.h"

GPIO B3Led(GPIOB,3,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);

StateInit stateInit;
StateTim2 stateTim2;
Context stateContext(&stateInit);
