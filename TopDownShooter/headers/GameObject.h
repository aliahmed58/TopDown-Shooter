#pragma once
#include "GameTexture.h"
#include <vector>

class GameObject {

public:
	GameObject();
	GameObject(SDL_Renderer* renderer, string path);
	GameObject(double x, double y, string path, SDL_Renderer* renderer);
	~GameObject();

	bool isAlive();
	virtual void kill(double x, double y, vector<GameObject*> &objs);
	GameTexture* getTexture();
	SDL_Rect& getCollisionRect();
	int get_x();
	int get_y();
	
	virtual double get_angle();
	virtual void power(vector<GameObject*> &list, double deltaTime);
	virtual void render();
	virtual void registerHit();
	virtual void move(double x, double y, double deltaTime) = 0;
	virtual void fire(vector<GameObject*>& objs, double deltaTime);

	string get_type();

protected:
	double x;
	double y;
	double friction;
	bool alive;
	GameTexture* sprite;
	SDL_Rect render_rect;
	SDL_Renderer* renderer;
	string type;
	SDL_Rect collision_rect;

	int RenderHeight;
	int RenderWidth;

	double angle;

};