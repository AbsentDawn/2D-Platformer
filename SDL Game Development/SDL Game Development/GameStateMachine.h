#ifndef __GAMESTATEMACHINE_H__
#define __GAMESTATEMACHINE_H__

#include "GameState.h"
#include <vector>

class GameStateMachine
{
public:
	void PushState(GameState* pState);
	void ChangeState(GameState* pState);
	void PopState();

	void Update();
	void Render();

private:
	std::vector<GameState*> _mGameStates;
};

#endif