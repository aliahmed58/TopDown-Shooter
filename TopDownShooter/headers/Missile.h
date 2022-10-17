#pragma once
#include "GameObject.h"

class Missile : public GameObject {
public:
	Missile();
	Missile(double x, double y, SDL_Renderer* renderer);

	void move(double x_val, double y_val);
	void fire(vector<GameObject*> objects);

private:
	GameObject* target;
};