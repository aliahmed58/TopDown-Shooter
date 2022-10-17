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
	alive = true;
	sprite = new GameTexture(renderer, file_path);
	sprite->getRect().x = x;
	sprite->getRect().y = y;
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

void GameObject::power(vector<GameObject*> &list, Uint32 time) {

}

void GameObject::registerHit() {

}