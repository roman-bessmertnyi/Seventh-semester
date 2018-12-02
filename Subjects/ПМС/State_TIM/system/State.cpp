#include "State.h"
#include "Singletons.h"

void StateInit::Execute(){
	B3Led.SetLevel(0);
};

IState * StateInit::GetNextState() const {
	return &stateTim2;
};

void StateTim2::Execute(){
	B3Led.SetLevel(1);
};

IState * StateTim2::GetNextState() const {
	return &stateInit;
};

Context::Context(IState *initialState):_state(initialState) {	
};

void Context::SetState(IState *state){
	_state = state;
};

void Context::Execute() const {
	_state -> Execute();
};


IState * Context::GetState(void) const{
	return _state;
};
