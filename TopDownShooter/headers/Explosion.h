#pragma once
#include "GameObject.h"

class Explosion : public GameObject {
public:
	Explosion();
	Explosion(double x, double y, SDL_Renderer* renderer);

	void move(double x_val, double y_val);

private:
	int alpha = 255;
};