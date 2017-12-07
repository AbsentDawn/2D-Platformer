#ifndef __LOADERPARAMS_H__
#define __LOADERPARAMS_H__


#include <iostream>
class LoaderParams
{
public:
	LoaderParams(int x, int y, int width, int height, std::string textureID, int numFrames,
	int callbackID = 0, int animSpeed = 0) :
		_x(x), _y(y), _mWidth(width), _mHeight(height), _mTextureID(textureID),
		_mNumFrames(numFrames), _mCallbackID(callbackID), _mAnimSpeed(animSpeed) {}

	int GetX() const { return _x; }
	int GetY() const { return _y; }
	int GetWidth() const { return _mWidth; }
	int GetHeight() const { return _mHeight; }
	int GetNumFrames() const { return _mNumFrames; }
	int GetAnimSpeed() const { return _mAnimSpeed; }
	int GetCallbackID() const { return _mCallbackID; }
	std::string GetTextureID() const { return _mTextureID; }

private:
	int _x;
	int _y;
	int _mWidth;
	int _mHeight;
	int _mNumFrames;
	int _mAnimSpeed;
	int _mCallbackID;
	std::string _mTextureID;
};
#endif