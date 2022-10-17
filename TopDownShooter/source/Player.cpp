#include "../headers/Player.h"
#include "../headers/Bullet.h"
#include "../headers/Missile.h"

Player::Player() {}

Player::Player(double x, double y, SDL_Renderer* renderer) : GameObject(x, y, player_png, renderer) {
	friction = 1.6;
	shoot_time = 0;
}

void Player::move(double x_val, double y_val, double deltaTime) {
	translate(x_val, y_val);

	int temp_x = x - x_val;
	int temp_y = y - y_val;

	if (x < 0) x = 0;
	if (x > SCREEN_WIDTH - sprite->getWidth()) x = SCREEN_WIDTH - sprite->getWidth();
	if (y > SCREEN_HEIGHT - sprite->getWidth()) y = SCREEN_HEIGHT - sprite->getHeight();
	if (y < 0) y = 0;

	x -= tx * deltaTime;
	y -= ty * deltaTime;

	tx *= friction;
	ty *= friction;

	sprite->getRect().x = x;
	sprite->getRect().y = y;

	collision_rect.x = sprite->getRect().x + 16;
	collision_rect.y = y;

}

void Player::translate(double x_val, double y_val) {
	tx = x_val;
	ty = y_val;
}

void Player::power(vector<GameObject*> &objects, Uint32 time, double deltaTime) {
	
	/*if (count < 3) count++;

	if (count >= 3) {
		Bullet* ins = new Bullet(x + 32, y, renderer, player_bullet_png, true);
		objects.insert(objects.begin(), ins);
		count = 0;
	} */

	if (shoot_time > SDL_GetTicks()) {
		Bullet* ins = new Bullet(x + 32, y, renderer, player_bullet_png, true);
		objects.insert(objects.begin(), ins);
	}

	shoot_time = SDL_GetTicks() + 5000;

}

void Player::missile(vector<GameObject*>& objs, Uint32 time) {
	time /= 1000;
	GameObject* target = nullptr;

	for (int i = 0; i < objs.size(); i++) {
		if (objs.at(i)->get_type() == "nimble" || objs.at(i)->get_type() == "ranger") {
			target = objs.at(i);
			break;
		}
	}
	if (target == nullptr) cout << "no target" << endl;
	if (target != nullptr) {
		if (missile_time > SDL_GetTicks()) {
			cout << "reached" << endl;
			GameObject* missile = new Missile(x + 31.5, y, renderer, target, this);
			objs.insert(objs.begin(),missile);
		}
	}
	missile_time = SDL_GetTicks() + 2000;
}