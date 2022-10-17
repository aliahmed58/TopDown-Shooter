#pragma once
#include "GameObject.h"

class Enemy : public GameObject {
public:
	Enemy();
	Enemy(double x, double y,string path, SDL_Renderer* renderer);

	virtual void power(vector<GameObject*> objects, Uint32 time) = 0;
	virtual void registerHit();

	void move(double x_val, double y_val);
	void translate(double x_val, double y_val);
	void render();

protected:
	int health;
	double tx;
	double ty;
};