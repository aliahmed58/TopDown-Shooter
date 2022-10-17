#pragma once
#include "Enemy.h"

class Ranger : public Enemy {
public:
	Ranger();
	Ranger(double x, double y, SDL_Renderer* renderer);

	void power(vector<GameObject*> objects, Uint32 time);
	void registerHit();
}; 
