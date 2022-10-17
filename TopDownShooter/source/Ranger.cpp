#include "../headers/Ranger.h"
#include "../headers/consts.h"
#include "../headers/Bullet.h"
Ranger::Ranger() {};

Ranger::Ranger(double x, double y, SDL_Renderer* renderer, Player* player) : Enemy(x, y, ranger_png, renderer) {
	health = 3;
	this->player = player;
	fireLimit = 0;
}

void Ranger::power(vector<GameObject*> &objects, Uint32 time) {
	
	if (fireLimit < 70) fireLimit++;
	if (fireLimit >= 70) {
		if (player->get_y() > y) {
			GameObject* bullet = new Bullet(x + 32, y + 65, renderer, ranger_bullets, false, player);
			objects.insert(objects.begin(), bullet);
			fireLimit = 0;
		}
	}
	
}

void Ranger::registerHit() {

}