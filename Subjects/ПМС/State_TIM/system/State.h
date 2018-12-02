#ifndef STATE_H
#define STATE_H

class IState {
	public:
		virtual void Execute() = 0;
		virtual IState * GetNextState() const = 0;
};

class StateInit: public IState {
	public:
		virtual void Execute();
		virtual IState * GetNextState() const;
};

class StateTim2: public IState {
	public:
		virtual void Execute();
		virtual IState * GetNextState() const;
};

class Context {
	private: IState * _state;

	public: 
		explicit Context(IState *initialState);
			
		void SetState(IState *state);
	
		IState * GetState(void) const;
			
		void Execute() const;
};
#endif
