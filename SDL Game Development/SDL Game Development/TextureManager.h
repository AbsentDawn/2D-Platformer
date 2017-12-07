#ifndef __TEXTURE_MANAGER__
#define __TEXTURE_MANAGER__

#include<iostream>
#include<map>
#include <SDL.h>
#include <SDL_image.h>

class TextureManager
{
public:
	bool Load(std::string fileName, std::string id, SDL_Renderer *renderer);
	void Draw(std::string id, int x, int y, int width, int height, SDL_Renderer *renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void ClearFromTextureMap(std::string ID);

	static TextureManager* GetInstance()
	{
		if (!instance) {
			instance = new TextureManager();
		}

		return instance;
	}

private:
	std::map<std::string, SDL_Texture*> textureMap;

	static TextureManager *instance;

	TextureManager() {};
};

typedef TextureManager TheTextureManager;

#endif