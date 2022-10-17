#include "../headers/Bullet.h"
#include "../headers/consts.h"

Bullet::Bullet() {}

Bullet::Bullet(double x, double y, SDL_Renderer* renderer, 
	string path, bool identifier, Player* player) : GameObject(x, y, path, renderer) {

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

void Bullet::move(double x_val, double y_val) {
	// if player is shooting
	if (isPlayer) {
		if (y > 0)
			y -= y_val + 1;
		else alive = false;
	}
	// if ranger shoots
	else {

		if (y < 704) y += 10;
		else alive = false;
		if (x > 0 && x < SCREEN_WIDTH - sprite->getWidth()) x -= (unit_x * 4);
		else alive = false;
	}

	sprite->getRect().y = y;
	sprite->getRect().x = x;
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