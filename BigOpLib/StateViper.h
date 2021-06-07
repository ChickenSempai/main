#pragma once
#include "Drone.h"

class ActionState;

class StateViper : public Drone
{
public:
	StateViper();
	void setState(ActionState* state) {
		if (m_state != nullptr)
			delete m_state;
		m_state = state;
	}
	~StateViper() {
		delete m_state;
	}
	void act();
private:
	ActionState* m_state;
};

class ActionState
{
public:
	ActionState(StateViper* holder) : stateHolder(holder) {}
	virtual ~ActionState() = 0;
	virtual void act() = 0;

protected:
	StateViper* stateHolder;
};

ActionState::~ActionState() {}

void StateViper::act() {
	m_state->act();
}

class DreamState : public ActionState
{
public:
	DreamState(StateViper* holder) :ActionState(holder) {}
	void act() override;
	~DreamState() {}
};

StateViper::StateViper() {
	m_state = new DreamState(this);
}

class AngerState : public ActionState
{
public:
	AngerState(StateViper* holder) :ActionState(holder) {}
	void act() override;
	~AngerState() {}
};

class FearState :public ActionState
{
public:
	FearState(StateViper* holder) :ActionState(holder) {}
	void act() override;
	~FearState() {}
};

void DreamState::act(){
	stateHolder->setFatness(stateHolder->getFatness() + 5);
	if (stateHolder->getFatness() == 10) {
		stateHolder->setState(new AngerState(stateHolder));
	}
}

void AngerState::act() {
	stateHolder->setFatness(stateHolder->getFatness() - 5);
	if (stateHolder->getFatness() == 0) {
		stateHolder->setState(new FearState(stateHolder));
	}
	else if (stateHolder->getFatness() == 15) {
		stateHolder->setFatness(0);
		stateHolder->setState(new DreamState(stateHolder));
	}
}

void FearState::act() {
	stateHolder->setFatness(stateHolder->getFatness() + 3);
	if (stateHolder->getFatness() == 30) {
		stateHolder->setState(new AngerState(stateHolder));
	}
}

