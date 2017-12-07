#pragma once
#include "MenuState.h"
#include "GameObject.h"
class MainMenuState :
	public MenuState
{
public:
	
	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual std::string GetStateID() const { return _mMenuID; }

private:
	static const std::string _mMenuID;
	virtual void SetCallbacks(const std::vector<Callback>& callbacks);
	
	// Call back functions for menu  items
	static void _sMenuToPlay();
	static void _sExitFromMenu();

private:
	std::vector<GameObject*> _mGameObjects;


};

