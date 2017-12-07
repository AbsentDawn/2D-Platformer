#ifndef __GAMEOVERSTATE_H__
#define __GAMEOVERSTATE_H__

#include <vector>

#include "GameState.h"
#include "GameObject.h"
#include "LoaderParams.h"

class GameOverState :
	public GameState
{
public:
	virtual void Update();
	virtual void Render();
	
	virtual bool OnEnter();
	virtual bool OnExit();

	virtual std::string GetStateID() const { return _mGameOverID; }

private:
	static const std::string _mGameOverID;

	static void _sGameOverToMain();
	static void _sRestartPlay();

private:
	std::vector<GameObject*> _mGameObjects;
};

#endif