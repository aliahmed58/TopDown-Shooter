#pragma once
#include "GameObject.h"
#include "../headers/Player.h"

class Bullet : public GameObject {
public:
	Bullet();
	Bullet(double x, double y, SDL_Renderer* renderer, string path, 
		string type, Player* player = nullptr);
	
	void move(double x, double y, double deltaTime);
	void render();

private:
	unsigned int frame;
	// frames of bullets
	SDL_Rect rects[4];
	// to know if enemy is firing or player;
	double angle;
	double unit_x;
	double unit_y;

	Player* player;
	void calc_vector();

};