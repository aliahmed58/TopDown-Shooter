#pragma once
#include "Enemy.h"

class Nimble : public Enemy {
public:
	Nimble();
	Nimble(double x, double y, SDL_Renderer* renderer);

	void power(vector<GameObject*> &objects, Uint32 time, double deltaTime);
	void registerHit();

private:
	unsigned int fireLimit;
	
};