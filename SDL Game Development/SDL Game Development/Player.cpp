#include "Player.h"
#include <SDL.h>
#include "InputHandler.h"

Player::Player() : SDLGameObject()
{
}


void Player::Draw()
{
	SDLGameObject::Draw();
}

void Player::Update()
{
	_mVelocity.SetX(0);
	_mVelocity.SetY(0);

	HandleInput();

	_mCurrentFrame = int(((SDL_GetTicks() / 100) % 6));
	
	SDLGameObject::Update();
}

void Player::Load(const LoaderParams * pParams)
{
	SDLGameObject::Load(pParams);
}

void Player::HandleInput()
{
	// Mouse Motion
	Vector2D* vec = TheInputHandler::GetInstance()->GetMousePosition();
	_mVelocity = (*vec - _mPosition) /= 50;

	if (TheInputHandler::GetInstance()->JoystickInitialised()) {
		if (TheInputHandler::GetInstance()->XValue(0, 1) > 0 ||
			TheInputHandler::GetInstance()->XValue(0, 1) < 0) {
			_mVelocity.SetX(1 * TheInputHandler::GetInstance()->XValue(0, 1));
		}

		if (TheInputHandler::GetInstance()->YValue(0, 1) > 0 ||
			TheInputHandler::GetInstance()->YValue(0, 1) < 0) {
			_mVelocity.SetY(1 * TheInputHandler::GetInstance()->YValue(0, 1));
		}

		if (TheInputHandler::GetInstance()->XValue(0, 2) > 0 ||
			TheInputHandler::GetInstance()->XValue(0, 2) < 0) {
			_mVelocity.SetX(1 * TheInputHandler::GetInstance()->XValue(0, 1));
		}

		if (TheInputHandler::GetInstance()->YValue(0, 2) > 0 ||
			TheInputHandler::GetInstance()->YValue(0, 2) < 0) {
			_mVelocity.SetY(1 * TheInputHandler::GetInstance()->YValue(0, 2));
		}

		// If Y/3/Traingle is pressed on the Controller
		if (TheInputHandler::GetInstance()->GetButtonState(0, 3)) {
			_mVelocity.SetX(1);
		}

		// if Left Mouse button is pressed
		if (TheInputHandler::GetInstance()->GetMouseButtonState(LEFT)) {
			_mVelocity.SetX(1);
		}

		// Keyboard Input
		if (TheInputHandler::GetInstance()->IsKeyDown(SDL_SCANCODE_RIGHT)) {
			_mVelocity.SetX(2);
		}
		if (TheInputHandler::GetInstance()->IsKeyDown(SDL_SCANCODE_LEFT)) {
			_mVelocity.SetX(-2);
		}
		if (TheInputHandler::GetInstance()->IsKeyDown(SDL_SCANCODE_UP)) {
			_mVelocity.SetY(-2);
		}
		if (TheInputHandler::GetInstance()->IsKeyDown(SDL_SCANCODE_DOWN)) {
			_mVelocity.SetY(2);
		}
	}
}
