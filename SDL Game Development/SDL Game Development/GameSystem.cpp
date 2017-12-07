#include "GameSystem.h"
#include "Player.h"
#include "Enemy.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "PlayState.h"
#include <iostream>

GameSystem* GameSystem::instance = 0;

bool GameSystem::Init(const char * title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	int flags = SDL_WINDOW_SHOWN;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	_mWindow = SDL_CreateWindow(title, xPos, yPos, width, height, flags);

	if (_mWindow == nullptr) {
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return false;
	}

	_mRenderer = SDL_CreateRenderer(_mWindow, -1, 0);

	if (_mRenderer == nullptr) {
		return false;
	}

	TheGameObjectFactory::GetInstance()->RegisterType("MenuButton", new
		MenuButtonCreator());

	_mGameStateMachine = new GameStateMachine();
	_mGameStateMachine->ChangeState(new MainMenuState());

	SDL_SetRenderDrawColor(_mRenderer, 0, 0, 0, 255);

	TheInputHandler::GetInstance()->InitJoysticks();
	//TheTextureManager::GetInstance()->Load("assets/animate-alpha.png", "animate", _mRenderer);

	//_mGameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 82, "animate")));
	//_mGameObjects.push_back(new Enemy(new LoaderParams(300, 300, 128, 82, "animate")));



	_mRunning = true;

	return nullptr;
}

void GameSystem::HandleEvents()
{
	TheInputHandler::GetInstance()->Update();
	
	// When pressing playing return change state
	if (TheInputHandler::GetInstance()->IsKeyDown(SDL_SCANCODE_RETURN)) {
		_mGameStateMachine->ChangeState(new PlayState());
	}
}

void GameSystem::Update()
{
	for (std::vector<GameObject*>::size_type i = 0; i !=
		_mGameObjects.size(); i++) {
		_mGameObjects[i]->Update();
	}

	_mGameStateMachine->Update();

	_mCurrentFrame = int(((SDL_GetTicks() / 100) % 6));

	SDL_Delay(10);
}

void GameSystem::Render()
{
	SDL_RenderClear(_mRenderer); // Clear the renderer to the draw colour

	// Loop through our objects and draw them
	for (std::vector<GameObject*>::size_type i = 0; i !=
		_mGameObjects.size(); i++) {
		_mGameObjects[i]->Draw();
	}

	_mGameStateMachine->Render();

	SDL_RenderPresent(_mRenderer); // Draw to the screen
}

void GameSystem::Clean()
{
	std::cout << "Cleaning Input\n";
	TheInputHandler::GetInstance()->Clean();

	std::cout << "Cleaning game\n";
	SDL_DestroyWindow(_mWindow);
	SDL_DestroyRenderer(_mRenderer);
	SDL_Quit();
}
