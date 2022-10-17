#pragma once
#include "GameObject.h"
#include "consts.h"

class Player : public GameObject {
public:
	Player();
	Player(double x, double y, SDL_Renderer* renderer);

	void translate(double x_val, double y_val);
	void move(double x, double y, double deltaTime);
	void power(vector<GameObject*> &list, Uint32 time, double deltaTime);
	void missile(vector<GameObject*> &objs, Uint32 time);
	void reset_player();

private:
	double tx;
	double ty;
	unsigned int shoot_time;
	unsigned int missile_time;
	short missile_count;
	bool missile_fired;
};