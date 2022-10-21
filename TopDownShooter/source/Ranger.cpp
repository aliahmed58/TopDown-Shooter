#include "../headers/Ranger.h"
#include "../headers/consts.h"
#include "../headers/Bullet.h"
Ranger::Ranger() {};

Ranger::Ranger(double x, double y, SDL_Renderer* renderer, Player* player) : Enemy(x, y, ranger_png, renderer) {
	health = 2;
	type = "ranger";
	this->player = player;
	fireLimit = 0;
}

void Ranger::power(vector<GameObject*> &objects, double deltaTime) {
	
	if (!fired) {
		if (player->get_y() > y) {
			GameObject* bullet = new Bullet(x + 32, y + 65, renderer, ranger_bullets, "ranger_bullet", player);
			objects.insert(objects.begin(), bullet);
		}
		fireLimit = SDL_GetTicks() + 2000;
		fired = true;
	}
	if (fireLimit < SDL_GetTicks()) fired = false;
	
}
