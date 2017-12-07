#pragma once
#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class MenuButton :
	public SDLGameObject
{
public:
	MenuButton();

	virtual void Draw();
	virtual void Update();
	virtual void Clean();
	virtual void Load(const LoaderParams* pParams);

	void SetCallback(void(*callback)()) { _mCallBack = callback; }
	int GetCallbackID() { return _mCallBackID; }


private:
	void(*_mCallBack)();
	bool _mReleased;
	int _mCallBackID;

};

enum buttonState {
	MOUSE_OUT = 0,
	MOUSE_OVER = 1,
	CLICKED = 2
};

class MenuButtonCreator : public BaseCreator
{
	GameObject* CreateGameObject() const
	{
		return new MenuButton();
	}
};