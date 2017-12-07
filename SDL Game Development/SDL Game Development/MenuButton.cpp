#include "MenuButton.h"
#include "InputHandler.h"


MenuButton::MenuButton() : SDLGameObject()
{
	// start at frame 0
	_mCurrentFrame = MOUSE_OUT; 

}

void MenuButton::Draw()
{
	// Use the base class drawing
	SDLGameObject::Draw(); 
}

void MenuButton::Update()
{
	// Start off with getting mouse position
	Vector2D* mousePos = TheInputHandler::GetInstance()->GetMousePosition();

	if (mousePos->GetX() < (_mPosition.GetX() + _mWidth) &&
		mousePos->GetX() > _mPosition.GetX() &&
		mousePos->GetY() < (_mPosition.GetY() + _mHeight) &&
		mousePos->GetY() > _mPosition.GetY()) {

		if (TheInputHandler::GetInstance()->GetMouseButtonState(LEFT) && _mReleased) {
			_mCurrentFrame = CLICKED;

			// Call our callback function
			_mCallBack(); 

			_mReleased = false;
		}
		else if (!TheInputHandler::GetInstance()->GetMouseButtonState(LEFT)) {

			_mReleased = true;
			// current frame mouse over button
			_mCurrentFrame = MOUSE_OVER;
		}
	}
	else {
		_mCurrentFrame = MOUSE_OUT;
	}
}

void MenuButton::Clean()
{	
	SDLGameObject::Clean();
}

void MenuButton::Load(const LoaderParams * pParams)
{
	SDLGameObject::Load(pParams);
	_mCallBackID = pParams->GetCallbackID();
	_mCurrentFrame = MOUSE_OUT;
}
