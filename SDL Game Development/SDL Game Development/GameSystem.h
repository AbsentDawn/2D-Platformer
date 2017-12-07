#ifndef __GameSystem__
#define __GameSystem__

#include <SDL.h>
#include <vector>

#include "GameObject.h"
#include "GameStateMachine.h"

class GameSystem
{
public:

	static GameSystem *GetInstance() {
		if (!instance) {
			instance = new GameSystem();
		}
		return instance;
	}

	bool Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	bool Running() { return _mRunning; }

	SDL_Renderer *GetRenderer() const { return _mRenderer; }
	GameStateMachine *GetStateMachine() { return _mGameStateMachine; }

private:
	GameSystem() {};
	~GameSystem() {};

	static GameSystem *instance;

private:
	bool _mRunning;

private:
	SDL_Window*_mWindow;
	SDL_Renderer* _mRenderer;
	GameStateMachine* _mGameStateMachine;

private:
	std::vector<GameObject*> _mGameObjects;
	int _mCurrentFrame;
};

typedef GameSystem TheGame;

#endif // !__GameSystem__
