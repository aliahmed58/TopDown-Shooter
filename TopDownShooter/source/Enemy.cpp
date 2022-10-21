#include "../headers/Enemy.h"
#include "../headers/consts.h"
#include "../headers/Explosion.h"

Enemy::Enemy() {};

Enemy::Enemy(double x, double y, string path, SDL_Renderer* renderer) : GameObject(x, y, path, renderer) {
	friction = 0.99;
	fired = false;
	collision_rect.x = sprite->getRect().x + 8;
	collision_rect.y = y;
	collision_rect.w = 48;
	collision_rect.h = 64;

}

void Enemy::move(double x_val, double y_val, double deltaTime) {
	translate(x_val, y_val);

	x -= tx * (deltaTime / 10);
	y += ty * (deltaTime / 10);

	int temp_x = x - 1;
	int temp_y = y - 1;

	if (temp_y > SCREEN_HEIGHT - 32) alive = false;

	sprite->getRect().x = x;
	sprite->getRect().y = y;

	collision_rect.x = sprite->getRect().x + 16;
	collision_rect.y = y;
}

void Enemy::translate(double x_val, double y_val) {
	tx = x_val;
	ty = y_val;
}

void Enemy::render() {
	SDL_RendererFlip flipType = SDL_FLIP_VERTICAL;
	SDL_Rect srcRect = { 0, 0,  sprite->getWidth(),sprite->getHeight() };

	render_rect = { (int)x, (int)y, sprite->getWidth(), sprite->getHeight() };
	sprite->render(&srcRect, &render_rect, NULL, flipType);
}


void Enemy::kill(double x, double y, vector<GameObject*>& objs) {
	if (health <= 0) {
		alive = false;
		int Num = rand() % 10;

		GameObject* E = new Explosion(x, y, 64, renderer);
		x += 16;
		y += 16;

		for (int j = 0; j < Num; j++) {

			int Xdev = rand() % 32;
			int Ydev = rand() % 32;
			int S = rand() % 48;
			GameObject* e = new Explosion(x + Xdev, y + Ydev, S, renderer);
			objs.insert(objs.begin(), e);
		}

		objs.insert(objs.begin(), E);
	}
	else {
		health--;
	}
}