#pragma once
#include "GameObject.h"

class Explosion : public GameObject {
public:
	Explosion();
	Explosion(double x, double y, SDL_Renderer* renderer);
	Explosion(double x, double y, int size, SDL_Renderer* renderer);

	void render();
	void move(double x_val, double y_val, double deltaTime);

private:
	int alpha = 255;
	int size;
};