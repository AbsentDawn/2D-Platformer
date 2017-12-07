#include "SDLGameObject.h"
#include "GameSystem.h"
#include "TextureManager.h"


SDLGameObject::SDLGameObject() : GameObject(), 
_mPosition(0, 0), _mVelocity(0, 0), _mAcceleration(0, 0)
{
	//_mWidth = params->GetWidth();
	//_mHeight = params->GetHeight();
	//_mTextureID = params->GetTextureID();

	_mCurrentRow = 1;
	_mCurrentFrame = 1;
}


SDLGameObject::~SDLGameObject()
{
}

void SDLGameObject::Draw()
{

	if (_mVelocity.GetX() > 0) {
		TheTextureManager::GetInstance()->DrawFrame(_mTextureID, (Uint32)_mPosition.GetX()
			, (Uint32)_mPosition.GetY(), _mWidth,
			_mHeight, _mCurrentRow, _mCurrentFrame,
			TheGame::GetInstance()->GetRenderer(), SDL_FLIP_HORIZONTAL);
	}
	else {
		TheTextureManager::GetInstance()->DrawFrame(_mTextureID, (Uint32)_mPosition.GetX()
			, (Uint32)_mPosition.GetY(), _mWidth,
			_mHeight, _mCurrentRow, _mCurrentFrame,
			TheGame::GetInstance()->GetRenderer());
	}
}

void SDLGameObject::Update()
{
	_mVelocity += _mAcceleration;
	_mPosition += _mVelocity;
}

void SDLGameObject::Clean()
{
}

void SDLGameObject::Load(const LoaderParams * pParams)
{
	_mPosition = Vector2D(pParams->GetX(), pParams->GetY());
	_mVelocity = Vector2D(0, 0);
	_mAcceleration = Vector2D(0, 0);
	_mWidth = pParams->GetWidth();
	_mHeight = pParams->GetHeight();
	_mTextureID = pParams->GetTextureID();
	_mNumFrames = pParams->GetNumFrames();

	_mCurrentRow = 1;
	_mCurrentFrame = 1;
}
