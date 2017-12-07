#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include <string>
#include <map>
#include "GameObject.h"

class BaseCreator
{
public:

	virtual GameObject* CreateGameObject() const = 0;
	virtual ~BaseCreator(){}
};

class GameObjectFactory
{
public:

	// Our Instance
	static GameObjectFactory *GetInstance() {
		if (!instance) {
			instance = new GameObjectFactory();
		}
		return instance;
	}

	bool RegisterType(std::string typeID, BaseCreator* pCreator);
	GameObject* Create(std::string typeID);

private:
	GameObjectFactory() {};

	static GameObjectFactory *instance;
	std::map<std::string, BaseCreator*> _mCreators;
};

typedef GameObjectFactory TheGameObjectFactory;

#endif