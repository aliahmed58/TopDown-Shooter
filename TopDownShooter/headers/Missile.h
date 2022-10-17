#pragma once
#include "GameObject.h"
#include "Player.h"

class Missile : public GameObject {
public:
	Missile();
	Missile(double x, double y, SDL_Renderer* renderer, GameObject *target, Player *player);

	void move(double x_val, double y_val, double deltaTime);
	void calc_vector();
	void render();

private:
	Player* player;
	GameObject* target;
	double unit_x;
	double unit_y;
	double angle;
};