#include "Enemy.h"
#include <SDL.h>


Enemy::Enemy() : SDLGameObject()
{
	_mVelocity.SetY(2);
	_mVelocity.SetX(0.001);
}

void Enemy::Draw()
{
	SDLGameObject::Draw();
}

void Enemy::Update()
{

	_mCurrentFrame = int(((SDL_GetTicks() / 100) % 6));

	if (_mPosition.GetY() < 0) {
		_mVelocity.SetY(2);
	}
	else if(_mPosition.GetY() > 400) {
		_mVelocity.SetY(-2);
	}

	SDLGameObject::Update();
}
