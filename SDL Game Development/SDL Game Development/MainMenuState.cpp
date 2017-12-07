#include "MainMenuState.h"
#include "MenuButton.h"
#include "StateParser.h"
#include "TextureManager.h"

const std::string MainMenuState::_mMenuID = "MENU";

void MainMenuState::Update()
{
	MenuState::Update();
}

void MainMenuState::Render()
{
	MenuState::Render();
}

bool MainMenuState::OnEnter()
{
	// Parse the state 
	StateParser stateParser;
	stateParser.ParseState("xml/test.txt", _mMenuID, &_mGameObjects,
		&_mTextureIdList);
	
	// Push back 0 callbackID start from 1
	_mCallbacks.push_back(0); 
	_mCallbacks.push_back(_sMenuToPlay);
	_mCallbacks.push_back(_sExitFromMenu);

	// Set the callbacks for menu items
	SetCallbacks(_mCallbacks);

	std::cout << "Entering MenuState\n";
	return true;
}

bool MainMenuState::OnExit()
{
	// clear the texture manager
	for (int i = 0; i < _mTextureIdList.size(); i++)
	{
		TextureManager::GetInstance()->ClearFromTextureMap(_mTextureIdList[i]);
	}
	return true;
}

void MainMenuState::SetCallbacks(const std::vector<Callback>& callbacks)
{
	// Go Through the game objects
	for (int i = 0; i < _mGameObjects.size(); i++) {
		// If they are type MenuButton then assign a callback
		// based on the id passed in from the file
		if (dynamic_cast<MenuButton*>(_mGameObjects[i])) {
			MenuButton* pButton =
				dynamic_cast<MenuButton*>(_mGameObjects[i]);
			pButton->SetCallback(callbacks[pButton->GetCallbackID()]);
		}
	}
}

void MainMenuState::_sMenuToPlay()
{}

void MainMenuState::_sExitFromMenu()
{}
