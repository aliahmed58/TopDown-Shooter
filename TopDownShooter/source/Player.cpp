#include "../headers/Player.h"
#include "../headers/Bullet.h"

Player::Player() {}

Player::Player(double x, double y, SDL_Renderer* renderer) : GameObject(x, y, player_png, renderer) {
	friction = 1.6;
	count = 0;
}

void Player::move(double x_val, double y_val) {
	translate(x_val, y_val);

	int temp_x = x - x_val;
	int temp_y = y - y_val;

	if (x < 0) x = 0;
	if (x > SCREEN_WIDTH - sprite->getWidth()) x = SCREEN_WIDTH - sprite->getWidth();
	if (y > SCREEN_HEIGHT - sprite->getWidth()) y = SCREEN_HEIGHT - sprite->getHeight();
	if (y < 0) y = 0;

	x -= tx;
	y -= ty;

	tx *= friction;
	ty *= friction;

	sprite->getRect().x = x;
	sprite->getRect().y = y;
}

void Player::translate(double x_val, double y_val) {
	tx = x_val;
	ty = y_val;
}

void Player::power(vector<GameObject*> &objects, Uint32 time) {
	
	if (count < 3) count++;

	if (count >= 3) {
		Bullet* ins = new Bullet(x + 32, y, renderer, player_bullet_png, true);
		objects.insert(objects.begin(), ins);
		count = 0;
	}

}