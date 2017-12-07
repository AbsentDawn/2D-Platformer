#include "AnimatedGraphics.h"
#include <SDL.h>


AnimatedGraphics::AnimatedGraphics(LoaderParams* pParams, int animSpeed, int frameNum) 
	: SDLGameObject(), _mAnimateSpeed(animSpeed), _mNumFrames(frameNum)
{
}

void AnimatedGraphics::Draw()
{
	SDLGameObject::Draw();
}

void AnimatedGraphics::Update()
{
	_mCurrentFrame = int(((SDL_GetTicks() / (1000 / _mAnimateSpeed)) %
		2));
}