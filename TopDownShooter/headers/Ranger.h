#pragma once
#include "Enemy.h"
#include "Player.h"

class Ranger : public Enemy {
public:
	Ranger();
	Ranger(double x, double y, SDL_Renderer* renderer, Player* player);

	void power(vector<GameObject*> &objects, double deltaTime);

private:
	unsigned int fireLimit;
	Player* player;
}; 
