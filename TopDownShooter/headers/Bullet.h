#pragma once
#include "GameObject.h"

class Bullet : public GameObject {
public:
	Bullet();
	Bullet(double x, double y, SDL_Renderer* renderer, string path);
	
	void move(double x, double y);
	void render();

private:
	unsigned int frame;

};