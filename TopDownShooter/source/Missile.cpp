#include "../headers/Missile.h"
#include "../headers/consts.h"

Missile::Missile() {};

Missile::Missile(double x, double y, SDL_Renderer* renderer, GameObject* target, Player* player) : GameObject(x, y, missile_png, renderer) {
	this->player = player;
	this->target = target;
	angle = 0;

}

void Missile::move(double x_val, double y_val, double deltaTime) {
	if (y > 0) {
		y -= 2 * (deltaTime / 4);
	}
	else {
		alive = false;
	}
}

void Missile::calc_vector() {
	double diff_x = target->get_x() - player->get_x();
	double diff_y = target->get_y() - player->get_y();

	double magnitude = sqrt((pow(diff_x, 2) + pow(diff_y, 2)));
	unit_x = (diff_x / magnitude);
	unit_y = (diff_x / magnitude);

	angle = atan2(unit_y, unit_x);
	angle = angle * (180 / 3.14159);
}

void Missile::render() {
	SDL_Rect srcRect = { 0, 0,  sprite->getWidth(),sprite->getHeight() };

	render_rect = { (int)x, (int)y, sprite->getWidth(), sprite->getHeight() };
	sprite->render(&srcRect, &render_rect, angle);
}

void Missile::fire(vector<GameObject*>& objs) {

}