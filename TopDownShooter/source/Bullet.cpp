#include "../headers/Bullet.h"
#include "../headers/consts.h"

Bullet::Bullet() {}

Bullet::Bullet(double x, double y, SDL_Renderer* renderer, 
	string path, bool identifier, bool dir, Player* player) : GameObject(x, y, path, renderer) {

	sprite->getRect().w = 4;
	sprite->getRect().h = 16;
	this->dir = dir;

	collision_rect.x = sprite->getRect().x;
	collision_rect.y = y;
	collision_rect.w = 4;
	collision_rect.h = 16;

	this->player = player;

	if (!identifier) {
		calc_vector();
		type = "enemy_bullet";
	}
	else {
		type = "player_bullet";
	}

	frame = 0;
	isPlayer = identifier;

	rects[0].x = 0;
	rects[0].y = 0;
	rects[0].w = 4;
	rects[0].h = 16;

	rects[1].x = 4;
	rects[1].y = 0;
	rects[1].w = 4;
	rects[1].h = 16;

	rects[2].x = 8;
	rects[2].y = 0;
	rects[2].w = 6;
	rects[2].h = 16;

	rects[3].x = 12;
	rects[3].y = 0;
	rects[3].w = 4;
	rects[3].h = 16;
}

void Bullet::move(double x_val, double y_val, double deltaTime) {
	// if player is shooting
	if (isPlayer) {
		if (y > 0)
			y -= (y_val + 1) * (deltaTime /4);
		else alive = false;
	}
	// if ranger shoots
	else {

		if (y < 704) y += 1 * (deltaTime / 2);
		else alive = false;
		if (x > 0 && x < SCREEN_WIDTH - sprite->getWidth()) x -= (unit_x * (deltaTime / 2));
		else alive = false;
	}

	if (dir) {
		if (y < SCREEN_HEIGHT - sprite->getHeight()) {
			y += y_val * (deltaTime / 4);
		}
		else alive = false;
	}

	sprite->getRect().y = y;
	sprite->getRect().x = x;
	collision_rect.x = x;
	collision_rect.y = y;
}

void Bullet::render() {
	SDL_Rect clip = { x, y, 4, sprite->getHeight() };
	
	SDL_Rect destrec;
	Uint32 time = SDL_GetTicks();

	destrec = rects[time % 4];

	sprite->render(&destrec, &clip, NULL);
}

void Bullet::calc_vector() {
	double diff_x = x - player->get_x();
	double diff_y = y - player->get_y();

	double magnitude = sqrt((pow(diff_x, 2) + pow(diff_y, 2)));
	unit_x = (diff_x / magnitude);
	unit_y = (diff_x / magnitude);
}