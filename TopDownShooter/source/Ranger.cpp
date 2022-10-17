#include "../headers/Ranger.h"
#include "../headers/consts.h"
#include "../headers/Bullet.h"
Ranger::Ranger() {};

Ranger::Ranger(double x, double y, SDL_Renderer* renderer) : Enemy(x, y, ranger_png, renderer) {
	health = 3;
}

void Ranger::power(vector<GameObject*> objects, Uint32 time) {
	if (time % 3 == 0) {
		GameObject* bullet = new Bullet(x, y, renderer, ranger_bullets, false);
		objects.insert(objects.begin(), bullet);
	}
}

void Ranger::registerHit() {

}