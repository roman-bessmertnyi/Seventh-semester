// StateCppGlobal.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
using namespace std;


class IState {
public:
	virtual void Execute(Context *context) const = 0;
};
class Context {
private: IState * _state;

public: 
	explicit Context(IState *initialState):_state(initialState) {	
	}
	void SetState(IState *state){
		_state = state;
	}
	void Execute() const {
		_state -> Execute(this);
	}
};

class StateA: public IState {
public: void Execute(Context *context) const override {
			cout << "State A called method excute" << endl;
			context->SetState(new StateB());
			delete this;
		}
};

class StateB: public IState {
public: void Execute(Context *context) const override {
			cout << "State B called method excute" << endl;
		}
};



int stop = 0;
int _tmain(int argc, _TCHAR* argv[])
{
	StateA state1;
	StateB state2;

	state1.Execute();
	state2.Execute();
	Context contextA(&state1);
	Context contextB(&state2);

	contextA.Execute();
	contextA.SetState(&state2);
	contextA.Execute();

	cin >> stop;
	return 0;
}
