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
	void setAlive(bool alive);
	GameTexture* getTexture();
	int get_x();
	int get_y();
	
	virtual void power(vector<GameObject*> &list, Uint32 time);
	virtual void render();
	virtual void registerHit();
	virtual void move(double x, double y) = 0;

	string get_type();

protected:
	double x;
	double y;
	double friction;
	bool alive;
	GameTexture* sprite;
	SDL_Rect render_rect;
	SDL_Renderer* renderer;
	string type;

};