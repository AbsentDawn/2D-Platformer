#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <iostream>

#include "SDLGameObject.h"
#include "LoaderParams.h"
class Enemy :
	public SDLGameObject
{
public:
	Enemy();

	virtual void Draw();
	virtual void Update();
	virtual void Clean() {};

};

#endif