#include "GameStateMachine.h"


void GameStateMachine::PushState(GameState * pState)
{
	_mGameStates.push_back(pState);
	_mGameStates.back()->OnEnter();
}

void GameStateMachine::ChangeState(GameState * pState)
{
	if (!_mGameStates.empty()) {
		if (_mGameStates.back()->GetStateID() == pState->GetStateID()) {
			return; // do nothing
		}

		if (_mGameStates.back()->OnExit()) {
			delete _mGameStates.back();
			_mGameStates.pop_back();
		}
	}

	_mGameStates.push_back(pState);

	// Initialise it
	_mGameStates.back()->OnEnter();
}

void GameStateMachine::PopState()
{
	if (!_mGameStates.empty()) {
		if (_mGameStates.back()->OnExit()) {
			delete _mGameStates.back();
			_mGameStates.pop_back();
		}
	}
}

void GameStateMachine::Update()
{
	if (!_mGameStates.empty()) {
		_mGameStates.back()->Update();
	}
}

void GameStateMachine::Render()
{
	if (!_mGameStates.empty()) {
		_mGameStates.back()->Render();
	}
}
