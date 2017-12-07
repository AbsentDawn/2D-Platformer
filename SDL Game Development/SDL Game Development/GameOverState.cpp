#include "GameOverState.h"
#include "GameSystem.h"
#include "TextureManager.h"
#include "AnimatedGraphics.h"
#include "MenuButton.h"
#include "MainMenuState.h"
#include "PlayState.h"

const std::string GameOverState::_mGameOverID = "GAMEOVER";

void GameOverState::Update()
{
	for (int i = 0; i < _mGameObjects.size(); i++) {
		_mGameObjects[i]->Update();
	}
}

void GameOverState::Render()
{
	for (int i = 0; i < _mGameObjects.size(); i++) {
		_mGameObjects[i]->Draw();
	}
}

bool GameOverState::OnEnter()
{
	if (!TheTextureManager::GetInstance()->Load("assets/gameover.png", "gameovertext",
		TheGame::GetInstance()->GetRenderer())) {
		return false;
	}

	if (!TheTextureManager::GetInstance()->Load("assets/main.png", "mainbutton",
		TheGame::GetInstance()->GetRenderer())) {
		return false;
	}

	if (!TheTextureManager::GetInstance()->Load("assets/restart.png", "restartbutton",
		TheGame::GetInstance()->GetRenderer())) {
		return false;
	}

	//GameObject* gameOverText = new AnimatedGraphics(new LoaderParams(200, 100, 190, 30,
		//"gameovertext"), 2);
	//GameObject* button1 = new MenuButton(new LoaderParams(200, 200, 200, 80, "mainbutton"),
		//_sGameOverToMain);
	//GameObject* button2 = new MenuButton(new LoaderParams(200, 300, 200, 80, "restartbutton"),
		//_sRestartPlay);

	//_mGameObjects.push_back(gameOverText);
	//_mGameObjects.push_back(button1);
	//_mGameObjects.push_back(button2);

	std::cout << "Entering PauseState\n";
	return true;
}

bool GameOverState::OnExit()
{
	std::cout << "Exiting GameOverState\n";
	return true;
}

void GameOverState::_sGameOverToMain()
{
	TheGame::GetInstance()->GetStateMachine()->ChangeState(new MainMenuState());
}

void GameOverState::_sRestartPlay()
{
	TheGame::GetInstance()->GetStateMachine()->ChangeState(new PlayState());
}
