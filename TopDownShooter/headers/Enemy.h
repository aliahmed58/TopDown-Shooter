#pragma once
#include "GameObject.h"

class Enemy : public GameObject {
public:
	Enemy();
	Enemy(double x, double y,string path, SDL_Renderer* renderer);

	virtual void registerHit();

	virtual void kill();
	void move(double x_val, double y_val, double deltaTime);
	void translate(double x_val, double y_val);
	void render();

protected:
	int health;
	double tx;
	double ty;
};