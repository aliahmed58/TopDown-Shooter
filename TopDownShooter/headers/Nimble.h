#pragma once
#include "Enemy.h"

class Nimble : public Enemy {
public:
	Nimble();
	Nimble(double x, double y, SDL_Renderer* renderer);

	void power(vector<GameObject*> &objects, double deltaTime);
	void registerHit();
	void fire(vector<GameObject*>& objs, double time);

private:
	unsigned int fireLimit;
	
};