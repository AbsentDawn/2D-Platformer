#include "GameSystem.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char **args)
{
	Uint32 frameStart, frameTime;

	// Init Game
	std::cout << "Game init Attempt...\n";
	TheGame::GetInstance()->Init("Chapter 1", 100, 100, 640, 480, false);

	// If all when successful
	std::cout << "Game init success\n";
	while (TheGame::GetInstance()->Running()) {

		// Get frame time
		frameStart = SDL_GetTicks();

		// Main Game Loop
		TheGame::GetInstance()->HandleEvents();
		TheGame::GetInstance()->Update();
		TheGame::GetInstance()->Render();

		// Frame Time subtracts current time from start time
		frameTime = SDL_GetTicks() - frameStart;

		if(frameTime < DELAY_TIME)
			SDL_Delay((int) (DELAY_TIME - frameTime));
	}
	
	// Clean game
	std::cout << "Game closing...\n";
	TheGame::GetInstance()->Clean();
	return 0;
}