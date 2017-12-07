#pragma once
#include <vector>
#include "GameState.h"
#include "GameObject.h"
class PauseState :
	public GameState
{
public:
	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual std::string GetStateID() const { return _mPauseID; }

private:

	static const std::string _mPauseID;

	static void _sPauseToMain();
	static void _sResumePlay();

private:
	std::vector<GameObject*> _mGameObjects;
};

