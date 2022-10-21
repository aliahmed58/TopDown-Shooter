#include "../headers/Player.h"
#include "../headers/Bullet.h"
#include "../headers/Missile.h"
#include "../headers/Smoke.h"

Player::Player() {}

Player::Player(double x, double y, SDL_Renderer* renderer) : GameObject(x, y, player_png, renderer) {
	friction = 0.9;
	shoot_time = 0;
	missile_fired = false;
	missile_count = 10;
}

void Player::move(double x_val, double y_val, double deltaTime) {
	translate(x_val, y_val);

	for (int i = 0; i < 3; i++) {
		x -= tx * (deltaTime / 3);
		y -= ty * (deltaTime / 3);

		tx *= friction;
		ty *= friction;
	}

	int temp_x = x - tx;
	int temp_y = y - ty;

	if (temp_x < 0) x = 0;
	if (temp_x > SCREEN_WIDTH - sprite->getWidth()) x = SCREEN_WIDTH - sprite->getWidth();
	if (temp_y > SCREEN_HEIGHT - sprite->getWidth()) y = SCREEN_HEIGHT - sprite->getHeight();
	if (temp_y < 0) y = 0;

	sprite->getRect().x = x;
	sprite->getRect().y = y;

	collision_rect.x = sprite->getRect().x + 16;
	collision_rect.y = y;

}

void Player::translate(double x_val, double y_val) {
	tx = x_val;
	ty = y_val;
}

void Player::power(vector<GameObject*> &objects, double deltaTime) {
	
	if (shoot_time > SDL_GetTicks()) {
		Bullet* ins = new Bullet(x + 32, y, renderer, player_bullet_png, "player_bullet", this);
		objects.insert(objects.begin(), ins);
	}

	shoot_time = SDL_GetTicks() + 5000;

}

void Player::missile(vector<GameObject*>& objs, Uint32 time) {
	time /= 1000;
	GameObject* target = nullptr;

	if (missile_count > 0) {
		for (int i = 0; i < objs.size(); i++) {
			if (objs.at(i)->get_type() == "nimble" || objs.at(i)->get_type() == "ranger") {
				target = objs.at(i);
				break;
			}
		}
		if (target == nullptr) cout << "no target" << endl;
		if (target != nullptr) {
			if (!missile_fired) {
				missile_time = SDL_GetTicks() + 2000;
				GameObject* missile = new Missile(x + 31.5, y, renderer, target, this);
				objs.insert(objs.begin(), missile);
				missile_fired = true;
				missile_count--;
			}
			if (missile_time < SDL_GetTicks())
				missile_fired = false;
		}

	}
}

void Player::reset_player() {
	missile_count = 10;
}