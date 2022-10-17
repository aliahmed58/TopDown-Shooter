#pragma once
#include "GameObject.h"
#include "consts.h"

class Player : public GameObject {
public:
	Player();
	Player(double x, double y, SDL_Renderer* renderer);

	void translate(double x_val, double y_val);
	void move(double x, double y);
	void power(vector<GameObject*> &list, Uint32 time);

private:
	double tx;
	double ty;

};