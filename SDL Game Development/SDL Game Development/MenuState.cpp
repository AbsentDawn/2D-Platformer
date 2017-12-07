#include "MenuState.h"
#include "TextureManager.h"
#include "GameSystem.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "PlayState.h"
#include <iostream>

const std::string MenuState::_mMenuID = "MENU";


void MenuState::Update()
{
	for (int i = 0; i < _mGameObjects.size(); i++) {
		_mGameObjects[i]->Update();
	}
}

void MenuState::Render()
{
	for (int i = 0; i < _mGameObjects.size(); i++) {
		_mGameObjects[i]->Draw();
	}
}

bool MenuState::OnEnter()
{
	// if its not the play button return false
	if (!TheTextureManager::GetInstance()->Load("assets/playbutton.png",
		"playbutton", TheGame::GetInstance()->GetRenderer())) {
		return false;
	}

	// if its not the exit button return false
	if (!TheTextureManager::GetInstance()->Load("assets/exit.png",
		"exitbutton", TheGame::GetInstance()->GetRenderer())) {
		return false;
	}

	// Load Buttons 
	//GameObject* button1 = new MenuButton(new LoaderParams(100, 100,
		//400, 100, "playbutton"), _sMenuToPlay);
	//GameObject* button2 = new MenuButton(new LoaderParams(100, 300,
		//400, 100, "exitbutton"), _sExitFromMenu);

	// Push buttons onto the vector
	//_mGameObjects.push_back(button1);
	//_mGameObjects.push_back(button2);
	
	std::cout << "Entering MenuState\n";
	return true;
}

bool MenuState::OnExit()
{
	for (int i = 0; i < _mGameObjects.size(); i++) {
		_mGameObjects[i]->Clean();
	}

	_mGameObjects.clear();
	TheTextureManager::GetInstance()->ClearFromTextureMap("playbutton");
	TheTextureManager::GetInstance()->ClearFromTextureMap("exitbutton");


	std::cout << "Exiting MenuState\n";
	return true;
}

void MenuState::_sMenuToPlay()
{
	TheGame::GetInstance()->GetStateMachine()->ChangeState(new PlayState());
	std::cout << "Play button clicked\n";
}

void MenuState::_sExitFromMenu()
{
	TheGame::GetInstance()->Clean();
	std::cout << "Exit button clicked\n";
}
