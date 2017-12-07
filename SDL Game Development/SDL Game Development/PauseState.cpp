#include "PauseState.h"
#include "GameSystem.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "TextureManager.h"
#include "InputHandler.h"

const std::string PauseState::_mPauseID = "PAUSE";


void PauseState::Update()
{
	for (int i = 0; i < _mGameObjects.size(); i++) {
		_mGameObjects[i]->Update();
	}
}

void PauseState::Render()
{
	for (int i = 0; i < _mGameObjects.size(); i++) {
		_mGameObjects[i]->Draw();
	}
}

bool PauseState::OnEnter()
{
	if (!TheTextureManager::GetInstance()->Load("assets/resume.png", "resumebutton",
		TheGame::GetInstance()->GetRenderer())) {
		return false;
	}

	if (!TheTextureManager::GetInstance()->Load("assets/main.png", "mainbutton",
		TheGame::GetInstance()->GetRenderer())) {
		return false;
	}

	//GameObject* button1 = new MenuButton(new LoaderParams(200, 100,
		//200, 80, "resumebutton"), _sResumePlay);
	//GameObject* button2 = new MenuButton(new LoaderParams(200, 300,
		//200, 80, "mainbutton"), _sPauseToMain);

	//_mGameObjects.push_back(button1);
	//_mGameObjects.push_back(button2);

	std::cout << "Entering PauseState\n";
	return true;
}

bool PauseState::OnExit()
{
	for (int i = 0; i < _mGameObjects.size(); i++) {
		_mGameObjects[i]->Clean();
	}

	_mGameObjects.clear();

	TheTextureManager::GetInstance()->ClearFromTextureMap("resumebutton");
	TheTextureManager::GetInstance()->ClearFromTextureMap("mainbutton");

	std::cout << "Exiting PauseState\n";
	return true;
}

void PauseState::_sPauseToMain()
{
	TheGame::GetInstance()->GetStateMachine()->ChangeState(new MainMenuState());
}

void PauseState::_sResumePlay()
{
	TheGame::GetInstance()->GetStateMachine()->PopState();
}
