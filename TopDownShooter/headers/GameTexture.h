#pragma once
#include <SDL.h>
#include <iostream>
using namespace std;

class GameTexture {

public:
	GameTexture();
	GameTexture(SDL_Renderer* renderer, string path);
	~GameTexture();
	// load texture from file
	bool loadTexture(string path);
	// free textures when not used
	void free();
	// render a texture
	void render(SDL_Rect* clip, SDL_Rect* render_rect, double angle, SDL_RendererFlip flipType = SDL_FLIP_NONE);
	// get dimensions
	int getWidth();
	int getHeight();
	//get rect
	SDL_Rect& getRect();

private:
	//actual texture
	SDL_Texture* obj_texture;
	SDL_Renderer* renderer;
	SDL_Rect renderRect;

	// sprite dimensions
	int height;
	int width;
};