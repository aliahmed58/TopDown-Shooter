#include "../headers/Nimble.h"
#include "../headers/consts.h"

Nimble::Nimble() {};

Nimble::Nimble(double x, double y, SDL_Renderer* renderer) : Enemy(x, y, nimble_png, renderer) {
	health = 1;
	friction = 1.5;
	type = "nimble";
}

void Nimble::power(vector<GameObject*>& objects, Uint32 time, double deltaTime) {
	int random = rand() % 1;

	double xRatio = 1 / (1 + (deltaTime * friction));

	if (random == 0) tx = 15;
	else tx = -15;

	tx *= xRatio;

	int diff_x = x + random;
	if (diff_x > 0 && diff_x < SCREEN_WIDTH - 64) {
		x += tx * deltaTime + 2;
		sprite->getRect().x = x;

	}
}

void Nimble::registerHit() {

}