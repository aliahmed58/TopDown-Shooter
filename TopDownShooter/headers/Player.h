#pragma once
#include "GameObject.h"
#include "consts.h"

class Player : public GameObject {
public:
	Player();
	Player(int x, int y, SDL_Renderer* renderer);

	void move();
	void fire();

private:
};