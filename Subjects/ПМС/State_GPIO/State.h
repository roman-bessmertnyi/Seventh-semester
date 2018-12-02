#ifndef STATE_H
#define STATE_H

class IState {
	public:
		virtual void Execute() const = 0;
};

class StateInit: public IState {
	public:
		virtual void Execute() const;
};

class StateTim2: public IState {
	public:
		virtual void Execute() const;
};

class Context {
	private: IState * _state;

	public: 
		explicit Context(IState *initialState);
			
		void SetState(IState *state);
			
		void Execute() const;
};
#endif
