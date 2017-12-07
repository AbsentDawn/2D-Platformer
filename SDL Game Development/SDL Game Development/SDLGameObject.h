#pragma once
#include "GameObject.h"
#include "Vector2D.h"
class SDLGameObject :
	public GameObject
{
public:
	
	SDLGameObject();

	virtual void Draw();
	virtual void Update();
	virtual void Clean();
	virtual void Load(const LoaderParams* pParams);

	Vector2D& GetPosition() { return _mPosition; }
	int GetWidth() { return _mWidth; }
	int GetHeight() { return _mHeight; }

	~SDLGameObject();

protected:
	Vector2D _mPosition;
	Vector2D _mVelocity;
	Vector2D _mAcceleration;

protected:

	int _mWidth;
	int _mHeight;

	int _mCurrentRow;
	int _mCurrentFrame;

	int _mNumFrames;

	std::string _mTextureID;
};

