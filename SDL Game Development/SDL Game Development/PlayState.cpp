#include "PlayState.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "GameSystem.h"
#include "Enemy.h"
#include "Player.h"

const std::string PlayState::_mPlayID = "PLAY";

void PlayState::Update()
{
	// When Escape is pressed go to pause state
	if (TheInputHandler::GetInstance()->IsKeyDown(SDL_SCANCODE_ESCAPE)) {
		TheGame::GetInstance()->GetStateMachine()->PushState(new PauseState());
	}


	for (int i = 0; i < _mGameObjects.size(); i++) {
		_mGameObjects[i]->Update();
	}

	if (CheckCollision(dynamic_cast<SDLGameObject*>
		(_mGameObjects[0]), dynamic_cast<SDLGameObject*>
		(_mGameObjects[1]))) {
		TheGame::GetInstance()->GetStateMachine()->PushState(new GameOverState());
	}
}

void PlayState::Render()
{
	for (int i = 0; i < _mGameObjects.size(); i++) {
		_mGameObjects[i]->Draw();
	}
}

bool PlayState::OnEnter()
{

	// if its not the helicopter return false
	if (!TheTextureManager::GetInstance()->Load("assets/helicopter.png",
		"helicopter", TheGame::GetInstance()->GetRenderer())) {
		return false;
	}

	// if its not the helicopter return false
	if (!TheTextureManager::GetInstance()->Load("assets/helicopter2.png",
		"helicopter2", TheGame::GetInstance()->GetRenderer())) {
		return false;
	}

	//GameObject* player = new Player(new LoaderParams(500, 100, 128, 55, "helicopter"));
	//GameObject* enemy = new Enemy(new LoaderParams(100, 100, 128, 55, "helicopter2"));

	//_mGameObjects.push_back(player);
	//_mGameObjects.push_back(enemy);

	std::cout << "Entering PlayState\n";
	return true;
}

bool PlayState::OnExit()
{
	for (int i = 0; i < _mGameObjects.size(); i++) {
		_mGameObjects[i]->Clean();
	}

	_mGameObjects.clear();
	TheTextureManager::GetInstance()->ClearFromTextureMap("helicopter");

	std::cout << "Entering PlayState\n";
	return true;
}

bool PlayState::CheckCollision(SDLGameObject * p1, SDLGameObject * p2)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	// Calculate the sides of rect A 
	leftA = p1->GetPosition().GetX();
	rightA = p1->GetPosition().GetX() + p1->GetWidth();
	topA = p1->GetPosition().GetY();
	bottomA = p1->GetPosition().GetY() + p1->GetHeight();

	// Calculate the sides of rect B
	leftB = p2->GetPosition().GetX();
	rightB = p2->GetPosition().GetX() + p2->GetWidth();
	topB = p2->GetPosition().GetY();
	bottomB = p2->GetPosition().GetY() + p2->GetHeight();

	// If any of the sides from A are outside of B
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }

	return true;
}
