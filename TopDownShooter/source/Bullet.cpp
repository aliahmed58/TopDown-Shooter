#include "../headers/Bullet.h"
#include "../headers/consts.h"

Bullet::Bullet() {}

Bullet::Bullet(double x, double y, SDL_Renderer* renderer, string path) : GameObject(x, y, path, renderer) {
	frame = 0;
}

void Bullet::move(double x_val, double y_val) {
	if (y > 0) {
		this->y -= y_val;
	}
	else {
		alive = false;
	}
}

void Bullet::render() {
	SDL_Rect clip = { 0, 0, 4, sprite->getHeight() };
	SDL_Rect render_rect[4];
	int c = 0;
	for (int i = 0; i < 4; i++) {
		render_rect[i] = {(int)x ,(int) y, c, 16};
		c += 4;
	}
	
	SDL_Rect destrec = render_rect[1];
	if (frame % 36 == 0)
		destrec = render_rect[frame % 4];
	frame++;

	sprite->render(&clip, &destrec);
}