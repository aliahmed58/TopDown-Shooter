#include "../headers/Enemy.h"
#include "../headers/consts.h"

Enemy::Enemy() {};

Enemy::Enemy(double x, double y, string path, SDL_Renderer* renderer) : GameObject(x, y, path, renderer) {
	friction = 0.99;

	collision_rect.x = sprite->getRect().x + 16;
	collision_rect.y = y;

}

void Enemy::move(double x_val, double y_val, double deltaTime) {
	translate(x_val, y_val);

	int temp_x = x - x_val;
	int temp_y = y - y_val;

	if (x < 0) x = 0;
	if (x > SCREEN_WIDTH ) alive = false;
	if (y > SCREEN_HEIGHT) alive = false;
	if (y < 0) y = 0;

	x += tx;
	y += ty * (deltaTime / 10);

	tx *= friction;
	ty *= friction;

	sprite->getRect().x = x;
	sprite->getRect().y = y;

	collision_rect.x = x + 16;
	collision_rect.y = y;
}

void Enemy::translate(double x_val, double y_val) {
	tx = x_val;
	ty = y_val;
}

void Enemy::registerHit() {

}

void Enemy::render() {
	SDL_RendererFlip flipType = SDL_FLIP_VERTICAL;
	SDL_Rect srcRect = { 0, 0,  sprite->getWidth(),sprite->getHeight() };

	render_rect = { (int)x, (int)y, sprite->getWidth(), sprite->getHeight() };
	sprite->render(&srcRect, &render_rect, NULL, flipType);
}


void Enemy::kill() {
	alive = false;
}