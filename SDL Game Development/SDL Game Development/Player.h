#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "SDLGameObject.h"
#include "GameObjectFactory.h"
#include "LoaderParams.h"

class Player :
	public SDLGameObject
{
public:
	Player();

	virtual void Draw();
	virtual void Update();
	virtual void Clean() {};
	void Load(const LoaderParams* pParams);

private:
	void HandleInput();
};

class PlayerCreator : public BaseCreator
{
	GameObject* CreateGameObject() const
	{
		return new Player();
	}
};

#endif