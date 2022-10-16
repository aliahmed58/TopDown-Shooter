#pragma once
#include "GameTexture.h"

class GameObject {

public:
	GameObject();
	GameObject(SDL_Renderer* renderer, string path);
	GameObject(int x, int y, string path, SDL_Renderer* renderer);
	~GameObject();

	bool isAlive();
	GameTexture& getTexture();
	void render();

protected:
	int x;
	int y;
	double friction;
	bool alive;
	GameTexture sprite;

};