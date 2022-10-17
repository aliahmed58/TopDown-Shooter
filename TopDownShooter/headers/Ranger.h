#pragma once
#include "Enemy.h"
#include "Player.h"

class Ranger : public Enemy {
public:
	Ranger();
	Ranger(double x, double y, SDL_Renderer* renderer, Player* player);

	void kill();
	void power(vector<GameObject*> &objects, Uint32 time, double deltaTime);
	void registerHit();

private:
	unsigned int fireLimit;
	Player* player;
}; 
