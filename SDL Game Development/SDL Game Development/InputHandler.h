#ifndef __INPUT_HANDLER__
#define __INPUT_HANDLER__

#include <SDL.h>
#include <vector>
#include "Vector2D.h"

enum mouseButtons
{
	LEFT = 0, 
	MIDDLE = 1,
	RIGHT = 2
};

const int joystickDeadZone = 10000;

class InputHandler
{
public:

	// Create Instance for InputHandler
	static InputHandler *GetInstance() {
		if (!instance) {
			instance = new InputHandler();
		}
		return instance;
	}

	void Update();
	void Clean();
	void InitJoysticks();
	bool JoystickInitialised() { return _mJoystickInitialised; }

	// X and Y on joystick
	int XValue(int joy, int stick);
	int YValue(int joy, int stick);

	// Gamepad Buttons
	bool GetButtonState(int joy, int buttonNumber);

	// Get Mouse button and position
	bool GetMouseButtonState(int buttonNumber);
	Vector2D* GetMousePosition();

	// Keyboard Input
	bool IsKeyDown(SDL_Scancode key);
	
private:
	static InputHandler *instance;

	InputHandler();
	~InputHandler() {};

	// Handle Keyboard Events
	void OnKeyDown();
	void OnKeyUp();

	// Handle Mouse Events
	void OnMouseMove(SDL_Event &evnt);
	void OnMouseButtonDown(SDL_Event &evnt);
	void OnMouseButtonUp(SDL_Event &evnt);

	// Handle Joysticks Events
	void OnJoystickAxisMove(SDL_Event &evnt);
	void OnJoystickButtonDown(SDL_Event &evnt);
	void OnJoystickButtonUp(SDL_Event &evnt);

private:
	std::vector<SDL_Joystick*> _mJoysticks;
	std::vector<std::pair<Vector2D*, Vector2D*>> _mJoystickValues;
	std::vector<std::vector<bool>> _mButtonStates;

	// As there will only be one mouse
	std::vector<bool>_mMouseButtonStates;
	Vector2D* _mMousePosition;

	// Keyboard 
	Uint8 *_mKeyStates;

private:
	bool _mJoystickInitialised;
};

typedef InputHandler TheInputHandler;

#endif