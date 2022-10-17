#include "../headers/Missile.h"
#include "../headers/consts.h"

Missile::Missile() {};

Missile::Missile(double x, double y, SDL_Renderer* renderer, GameObject* target, Player* player) : GameObject(x, y, missile_png, renderer) {
	this->player = player;
	this->target = target;
	angle = 0;
	type = "missile";

	collision_rect.w = 32;
	collision_rect.h = 32;
}

void Missile::move(double x_val, double y_val, double deltaTime) {


	if (y >= target->get_y()) {
		calc_vector();
	}

	if (y > 0) {
		y -= 1 * (deltaTime / 4);
	}
	else {
		alive = false;
	}
	if (x > 0 && x < SCREEN_WIDTH - sprite->getWidth()) {
		x += (unit_x * (deltaTime / 4));
	}
	else {
		alive = false;
	}

	collision_rect.x = x;
	collision_rect.y = y;
	
}

void Missile::calc_vector() {
	double diff_x = target->get_x() - x;
	double diff_y = target->get_y() - y;

	double magnitude = sqrt((pow(diff_x, 2) + pow(diff_y, 2)));
	unit_x = (diff_x / magnitude);
	unit_y = (diff_x / magnitude);

	angle = atan2(abs(diff_y), abs(diff_x));
	angle = angle * (180 / 3.14159);
	// fix too much tilt

	if (x > target->get_x()) {
		angle *= -1;
	}
}

void Missile::render() {
	SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
	SDL_Rect srcRect = { 0, 0,  sprite->getWidth(),sprite->getHeight() };

	render_rect = { (int)x, (int)y, sprite->getWidth(), sprite->getHeight() };
	sprite->render(&srcRect, &render_rect, angle, flip);
}
