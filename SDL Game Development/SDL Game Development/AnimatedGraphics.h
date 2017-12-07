#ifndef __ANIMATEDGRAPHIC_H__
#define __ANIMATEDGRAPHIC_H__

#include "SDLGameObject.h"
#include "LoaderParams.h"

class AnimatedGraphics :
	public SDLGameObject
{
public:
	AnimatedGraphics(LoaderParams* pParams, int animSpeed, int frameNum);

	virtual void Draw();
	virtual void Update();
	virtual void Clean() {};

private:
	int _mAnimateSpeed;
	int _mNumFrames;
};

#endif