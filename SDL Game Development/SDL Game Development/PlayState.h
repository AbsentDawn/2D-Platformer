#ifndef __PLAYSTATE_H__
#define __PLAYSTATE_H__

#include <iostream>
#include <vector>
#include "GameState.h"
#include "GameObject.h"
#include "SDLGameObject.h"
class PlayState :
	public GameState
{
public:
	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual std::string GetStateID() const { return _mPlayID; }

private:
	static const std::string _mPlayID;

private:
	std::vector<GameObject*> _mGameObjects;
	bool CheckCollision(SDLGameObject* p1, SDLGameObject* p2);
};

#endif