#pragma once
#include "GameObject.h"

class Enemy : public GameObject {
public:
	Enemy();
	Enemy(double x, double y,string path, SDL_Renderer* renderer);

	virtual void kill(double x, double y, vector<GameObject*>& objs);
	void move(double x_val, double y_val, double deltaTime);
	void translate(double x_val, double y_val);
	void render();

protected:
	int health;
	double tx;
	double ty;
	bool fired;

private:
	bool explosion;
};