#pragma once
#include "GameTexture.h"
#include <vector>

class GameObject {

public:
	GameObject();
	GameObject(SDL_Renderer* renderer, string path);
	GameObject(double x, double y, string path, SDL_Renderer* renderer);
	~GameObject();

	bool isAlive();
	GameTexture* getTexture();
	
	virtual void fire(vector<GameObject*> &list);
	virtual void render();
	virtual void move(double x, double y) = 0;

protected:
	double x;
	double y;
	double friction;
	bool alive;
	GameTexture* sprite;
	SDL_Rect render_rect;
	SDL_Renderer* renderer;

};