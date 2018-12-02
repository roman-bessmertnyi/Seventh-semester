#include "State.h"
#include "Singletons.h"

void StateInit::Execute() const {
	B3Led.SetLevel(0);
	stateContext.SetState(&stateTim2);
};

void StateTim2::Execute() const {
	B3Led.SetLevel(1);
	stateContext.SetState(&stateInit);
};

Context::Context(IState *initialState):_state(initialState) {	
};

void Context::SetState(IState *state){
	_state = state;
};

void Context::Execute() const {
	_state -> Execute();
};
