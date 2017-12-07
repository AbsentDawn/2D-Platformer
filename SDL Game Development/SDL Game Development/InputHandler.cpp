#include "InputHandler.h"
#include "GameSystem.h"
#include <iostream>

InputHandler *InputHandler::instance = 0;

InputHandler::InputHandler()
{
	_mMousePosition = new Vector2D(0, 0);

	// Takes in 3 buttons
	for (int i = 0; i < 3; i++) {
		_mMouseButtonStates.push_back(false);
	}
}

void InputHandler::OnKeyDown()
{
	_mKeyStates = (Uint8*)SDL_GetKeyboardState(0);
}

void InputHandler::OnKeyUp()
{
	_mKeyStates = (Uint8*)SDL_GetKeyboardState(0);
}

void InputHandler::OnMouseMove(SDL_Event & evnt)
{
	// Mouse Motion
	if (evnt.type == SDL_MOUSEMOTION) {
		_mMousePosition->SetX(evnt.motion.x);
		_mMousePosition->SetY(evnt.motion.y);
	}
}

void InputHandler::OnMouseButtonDown(SDL_Event & evnt)
{
	// If Button is pressed
	if (evnt.type == SDL_MOUSEBUTTONDOWN) {
		if (evnt.button.button == SDL_BUTTON_LEFT) {
			_mMouseButtonStates[LEFT] = true;
		}

		if (evnt.button.button == SDL_BUTTON_MIDDLE) {
			_mMouseButtonStates[MIDDLE] = true;
		}

		if (evnt.button.button == SDL_BUTTON_RIGHT) {
			_mMouseButtonStates[RIGHT] = true;
		}
	}
}

void InputHandler::OnMouseButtonUp(SDL_Event & evnt)
{

	// If button is released
	if (evnt.type == SDL_MOUSEBUTTONUP) {
		if (evnt.button.button == SDL_BUTTON_LEFT) {
			_mMouseButtonStates[LEFT] = false;
		}

		if (evnt.button.button == SDL_BUTTON_MIDDLE) {
			_mMouseButtonStates[MIDDLE] = false;
		}

		if (evnt.button.button == SDL_BUTTON_RIGHT) {
			_mMouseButtonStates[RIGHT] = false;
		}
	}
}

void InputHandler::OnJoystickAxisMove(SDL_Event & evnt)
{
	// Handle Joystick events
	if (evnt.type == SDL_JOYAXISMOTION) {
		int whichOne = evnt.jaxis.which;

		// Left stick move left or right
		if (evnt.jaxis.axis == 0) {
			if (evnt.jaxis.value > joystickDeadZone) {
				_mJoystickValues[whichOne].first->SetX(1);
			}
			else if (evnt.jaxis.value < -joystickDeadZone) {
				_mJoystickValues[whichOne].first->SetX(-1);
			}
			else {
				_mJoystickValues[whichOne].first->SetX(0);
			}
		}

		// left stick move up or down
		if (evnt.jaxis.axis == 1) {
			if (evnt.jaxis.value > joystickDeadZone) {
				_mJoystickValues[whichOne].first->SetY(1);
			}
			else if (evnt.jaxis.value < -joystickDeadZone) {
				_mJoystickValues[whichOne].first->SetY(-1);
			}
			else {
				_mJoystickValues[whichOne].first->SetY(0);
			}
		}

		// Right stick move left or right
		if (evnt.jaxis.axis == 3) {
			if (evnt.jaxis.value > joystickDeadZone) {
				_mJoystickValues[whichOne].second->SetX(1);
			}
			else if (evnt.jaxis.value < -joystickDeadZone) {
				_mJoystickValues[whichOne].second->SetX(-1);
			}
			else {
				_mJoystickValues[whichOne].second->SetX(0);
			}
		}

		// Right stick move left or right
		if (evnt.jaxis.axis == 4) {
			if (evnt.jaxis.value > joystickDeadZone) {
				_mJoystickValues[whichOne].second->SetY(1);
			}
			else if (evnt.jaxis.value < -joystickDeadZone) {
				_mJoystickValues[whichOne].second->SetY(-1);
			}
			else {
				_mJoystickValues[whichOne].second->SetY(0);
			}
		}
	}
}

void InputHandler::OnJoystickButtonDown(SDL_Event & evnt)
{
	// Handle Button Events
	if (evnt.type == SDL_JOYBUTTONDOWN) {
		int whichOne = evnt.jaxis.which;

		_mButtonStates[whichOne][evnt.jbutton.button] = true;
	}
}

void InputHandler::OnJoystickButtonUp(SDL_Event & evnt)
{
	// If GamePad button is released
	if (evnt.type == SDL_JOYBUTTONUP) {
		int whichOne = evnt.jaxis.which;

		_mButtonStates[whichOne][evnt.jbutton.button] = false;
	}
}

void InputHandler::Update()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type)
		{
		case SDL_QUIT:
			TheGame::GetInstance()->Clean();
			break;
		case SDL_MOUSEMOTION:
			OnMouseMove(evnt);
			break;
		case SDL_MOUSEBUTTONDOWN:
			OnMouseButtonDown(evnt);
			break;
		case SDL_MOUSEBUTTONUP:
			OnMouseButtonUp(evnt);
			break;
		case SDL_JOYBUTTONDOWN:
			OnJoystickButtonDown(evnt);
			break;
		case SDL_JOYBUTTONUP:
			OnJoystickButtonUp(evnt);
			break;
		case SDL_JOYAXISMOTION:
			OnJoystickAxisMove(evnt);
			break;
		case SDL_KEYDOWN:
			OnKeyDown();
			break;
		case SDL_KEYUP:
			OnKeyUp();
			break;
		default:
			break;
		}
	}
}

void InputHandler::Clean()
{
	if (_mJoystickInitialised) {
		for (unsigned int i = 0; i < SDL_NumJoysticks(); i++) {
			SDL_JoystickClose(_mJoysticks[i]);
		}
	}
}

void InputHandler::InitJoysticks()
{

	// Initialise Jhoystick in case it wasnt initialised the first time
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	if (SDL_NumJoysticks() > 0) {
		for (int i = 0; i < SDL_NumJoysticks(); i++) {
			SDL_Joystick* joy = SDL_JoystickOpen(i);
			if (SDL_JoystickOpen(i)) {
				_mJoysticks.push_back(joy);
				_mJoystickValues.push_back(std::make_pair(new Vector2D(0, 0),
					new Vector2D(0, 0))); // Add our pair

				std::vector<bool> tempButtons;

				for (int j = 0; j < SDL_JoystickNumButtons(joy); j++) {
					tempButtons.push_back(false);
				}
				_mButtonStates.push_back(tempButtons);
			}
			else {
				std::cout << SDL_GetError();
			}
		}

		SDL_JoystickEventState(SDL_ENABLE);
		_mJoystickInitialised = true;

		std::cout << "initialised " << _mJoysticks.size() << " joystick(s)\n";
	}
	else {
		_mJoystickInitialised = false;
	}
}

int InputHandler::XValue(int joy, int stick)
{
	if (_mJoystickValues.size() > 0) {
		if (stick == 1) {
			return _mJoystickValues[joy].first->GetX();
		}
		else if (stick == 2) {
			return _mJoystickValues[joy].second->GetX();
		}
	}
	return 0;
}

int InputHandler::YValue(int joy, int stick)
{
	if (_mJoystickValues.size() > 0) {
		if (stick == 1) {
			return _mJoystickValues[joy].first->GetY();
		}
		else if (stick == 2) {
			return _mJoystickValues[joy].second->GetY();
		}
	}
	return 0;
}

bool InputHandler::GetButtonState(int joy, int buttonNumber)
{
	return _mButtonStates[joy][buttonNumber];
}

bool InputHandler::GetMouseButtonState(int buttonNumber)
{
	return _mMouseButtonStates[buttonNumber];
}

Vector2D * InputHandler::GetMousePosition()
{
	return _mMousePosition;
}

bool InputHandler::IsKeyDown(SDL_Scancode key)
{
	if (_mKeyStates != 0) {
		if (_mKeyStates[key] == 1) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}