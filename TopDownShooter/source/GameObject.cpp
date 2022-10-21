#include "../headers/GameObject.h"

GameObject::GameObject() {
	x = y = 0;
	alive = true;
}

GameObject::GameObject(SDL_Renderer* renderer, string path) {
	x = 0;
	y = 0;
	alive = true;
	this->renderer = renderer;
	sprite = new GameTexture(renderer, path);
}

GameObject::GameObject(double x, double y, string file_path, SDL_Renderer* renderer) {
	this->x = x;
	this->y = y;
	this->renderer = renderer;
	type = "object";
	alive = true;
	sprite = new GameTexture(renderer, file_path);

	RenderHeight = sprite->getHeight();
	RenderWidth = sprite->getWidth();

	angle = 0;

	sprite->getRect().x = x;
	sprite->getRect().y = y;

	collision_rect.x = sprite->getRect().x + 16;
	collision_rect.y = y;
	collision_rect.w = 32;
	collision_rect.h = 64;
}

GameObject::~GameObject() {
	sprite->free();
	delete sprite;
}

bool GameObject::isAlive() {
	return alive;
}

GameTexture* GameObject::getTexture() {
	return sprite;
}

void GameObject::render() {

	SDL_Rect srcRect = { 0, 0,  sprite->getWidth(),sprite->getHeight() };
	
	render_rect = { (int) x, (int) y, sprite->getWidth(), sprite->getHeight() };
	sprite->render(&srcRect, &render_rect, NULL);
}

void GameObject::power(vector<GameObject*> &list, double deltaTime) {}

void GameObject::registerHit() {}

int GameObject::get_x() {
	return x;
}

int GameObject::get_y() {
	return y;
}

string GameObject::get_type() {
	return type;
}

void GameObject::kill(double x, double y, vector<GameObject*>& objs) {
	this->alive = false;
}

SDL_Rect& GameObject::getCollisionRect() {
	return collision_rect;
}

void GameObject::fire(vector<GameObject*> &objects, double time) {

}