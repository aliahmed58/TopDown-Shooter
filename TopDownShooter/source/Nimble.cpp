#include "../headers/Nimble.h"
#include "../headers/consts.h"
#include "../headers/Bullet.h"

Nimble::Nimble() {};

Nimble::Nimble(double x, double y, SDL_Renderer* renderer) : Enemy(x, y, nimble_png, renderer) {
	health = 1;
	friction = 0.9;
	type = "nimble";

}

void Nimble::power(vector<GameObject*>& objects, double deltaTime) {
	int random = rand() % 1;


	if (random == 0) tx = 2;
	else tx = -2;

	int diff_x = x + random;
	if (diff_x > 0 && diff_x < SCREEN_WIDTH - 64) {
		for (int i = 0; i < 4; i++) {
			x -= tx * (deltaTime / 4);
			tx *= friction;
		}
		int temp_x = x - tx;

		sprite->getRect().x = x;
		sprite->getRect().y = y;
		collision_rect.x = sprite->getRect().x + 16;
		collision_rect.y = y;
	}
}

void Nimble::registerHit() {}

void Nimble::fire(vector<GameObject*>& objs, double deltaTime) {
	if (!fired) {
		GameObject* bullet = new Bullet(x + 32, y + 65, renderer, nimble_bullets, "nimble_bullet");
		objs.insert(objs.begin(), bullet);

		fireLimit = SDL_GetTicks() + 2000;
		fired = true;
	}
	if (fireLimit < SDL_GetTicks()) fired = false;
}