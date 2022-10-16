#include "../headers/GameObject.h"

GameObject::GameObject() {
	x = y = 0;
	alive = true;
}

GameObject::GameObject(SDL_Renderer* renderer, string path) {
	x = 0;
	y = 0;
	alive = true;
	GameTexture z(renderer, path);
	sprite = z;
}

GameObject::GameObject(int x, int y, string file_path, SDL_Renderer* renderer) {
	this->x = x;
	this->y = y;
	GameTexture z(renderer, file_path);
	sprite = z;
	sprite.getRect().x = x;
	sprite.getRect().y = y;
}

GameObject::~GameObject() {
	sprite.free();
}

bool GameObject::isAlive() {
	return alive;
}

GameTexture& GameObject::getTexture() {
	return sprite;
}

void GameObject::render() {
	SDL_Rect srcRect = { 0, 0, 64, 64 };
	sprite.render(x,y, &srcRect);
}
