#pragma once
#include "GameObject.h"

class Smoke : public GameObject {
public:
	Smoke();
	Smoke(double x, double y,double angle, SDL_Renderer* renderer);

	void render();
	void move(double x_val, double y_val, double deltaTime);

private:
	int alpha = 255;
	double angle;
};