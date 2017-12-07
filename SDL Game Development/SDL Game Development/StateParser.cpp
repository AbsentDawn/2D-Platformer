#include "StateParser.h"
#include "TextureManager.h"
#include "GameSystem.h"
#include "GameObjectFactory.h"
#include <vector>

bool StateParser::ParseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects, 
	std::vector<std::string> *pTextureIDs)
{

	std::cout << "The ID you just passed in.. " + stateID << "\n";
	TiXmlDocument xmlDoc;

	if (!xmlDoc.LoadFile(stateFile)) {
		std::cerr << xmlDoc.ErrorDesc() << "\n";
		return false;
	}

	// Get the root element
	TiXmlElement* pRoot = xmlDoc.RootElement();

	TiXmlElement* pStateRoot = 0;

	std::cout << pRoot->NextSibling() << "\n";

	// Get this states root node and assign it to pStateRoot
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e =
		e->NextSiblingElement()) {
		if (e->Value() == stateID) {

			std::cout << stateID;
			pStateRoot = e;
		}
	}

	// Pre declare the texture root
	TiXmlElement* pTextureRoot = 0;

	// Get the root of the texture elements
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e !=
		NULL; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("TEXTURES")) {
			pTextureRoot = e;
		}
	}

	// Now parse the textures
	ParseTextures(pTextureRoot, pTextureIDs);

	// Pre declare the object root node
	TiXmlElement* pObjectRoot = 0;

	// Get the root node and assign it to pObjectRoot
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e !=
		NULL; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("OBJECTS")) {
			pObjectRoot = e;
		}
	}

	// Now parse the objects
	ParseObjects(pObjectRoot, pObjects);

	return true;
}

void StateParser::ParseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*>* pObjects)
{
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e !=
		NULL; e = e->NextSiblingElement()) {

		int x, y, width, height, numFrames, callbackID, animSpeed;
		std::string textureID;

		e->Attribute("x", &x);
		e->Attribute("y", &y);
		e->Attribute("width", &width);
		e->Attribute("height", &height);
		e->Attribute("numFrames", &numFrames);
		e->Attribute("callbackID", &callbackID);
		e->Attribute("animSpeed", &animSpeed);

		textureID = e->Attribute("textureID");

		std::cout << "Type Of Object " << e->Attribute("type");

		GameObject* pGameObject =
			TheGameObjectFactory::GetInstance()->Create(e->Attribute("type"));
		pGameObject->Load(new LoaderParams(x, y, width, height, textureID, numFrames,
			callbackID, animSpeed));

		pObjects->push_back(pGameObject);
	}
}

void StateParser::ParseTextures(TiXmlElement* pStateRoot, std::vector<std::string>* pTextureIDs)
{
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL;
		e = e->NextSiblingElement()) {
		std::string filenameAttribute = e->Attribute("filename");
		std::string idAttribute = e->Attribute("ID");
		pTextureIDs->push_back(idAttribute); // push into list

		TheTextureManager::GetInstance()->Load(filenameAttribute, idAttribute,
			TheGame::GetInstance()->GetRenderer());
	}
}
