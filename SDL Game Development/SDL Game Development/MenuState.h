#ifndef __MENUSTATE_H__
#define __MENUSTATE_H__

#include <iostream>
#include <vector>
#include "GameState.h"
#include "GameObject.h"

class MenuState :
	public GameState
{
public:
	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual std::string GetStateID() const { return _mMenuID; }


protected:
	typedef void(*Callback)();
	virtual void SetCallbacks(const std::vector<Callback>& callbacks) = 0;
	std::vector<Callback> _mCallbacks;


private:
	static const std::string _mMenuID;

	// call back our functions for menu items
	static void _sMenuToPlay();
	static void _sExitFromMenu();

private:
	std::vector<GameObject*> _mGameObjects;
};

#endif
