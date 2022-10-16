#include "../headers/Player.h"
#include "../headers/Bullet.h"

Player::Player() {}

Player::Player(double x, double y, SDL_Renderer* renderer) : GameObject(x, y, player_png, renderer) {
	friction = 1.6;
}

void Player::move(double x_val, double y_val) {
	translate(x_val, y_val);

	//cout << "x: " << x << "y: " << y << endl;

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
}

void Player::translate(double x_val, double y_val) {
	tx = x_val;
	ty = y_val;
}

void Player::fire(vector<GameObject*> &objects) {
	
	Bullet* ins = new Bullet(x + 16, y + 32, renderer, player_bullet_png);
	Bullet* ins2 = new Bullet(x + 48, y + 32, renderer, player_bullet_png);
	objects.insert(objects.begin(), ins);
	objects.insert(objects.begin(), ins2);

	cout << objects.size() << endl;
}