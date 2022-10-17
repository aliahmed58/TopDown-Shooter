#pragma once
#include "GameObject.h"

class Bullet : public GameObject {
public:
	Bullet();
	Bullet(double x, double y, SDL_Renderer* renderer, string path, bool isPlayer);
	
	void move(double x, double y);
	void render();

private:
	unsigned int frame;
	SDL_Rect rects[4];
	// to know if enemy is firing or player;
	bool isPlayer;

};