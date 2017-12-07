#include "GameObjectFactory.h"

GameObjectFactory* GameObjectFactory::instance = 0;

bool GameObjectFactory::RegisterType(std::string typeID, BaseCreator * pCreator)
{
	std::map<std::string, BaseCreator*>::iterator it = _mCreators.find(typeID);

	// If the type is already registered, do nothing
	if (it != _mCreators.end()) {
		delete pCreator;
		return false;
	}

	_mCreators[typeID] = pCreator;

	return true;
}

GameObject * GameObjectFactory::Create(std::string typeID)
{
	std::map<std::string, BaseCreator*>::iterator it = _mCreators.find(typeID);

	if (it != _mCreators.end()) {
		std::cout << "Could not find type: " << typeID << "\n";
		return NULL;
	}

	BaseCreator* pCreator = (*it).second;
	return pCreator->CreateGameObject();
}
