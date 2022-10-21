#include "../headers/Explosion.h"
#include "../headers/consts.h"

Explosion::Explosion() {};

Explosion::Explosion(double x, double y, SDL_Renderer* renderer) : GameObject(x, y, explosion_png, renderer) {
	this->x = x;
	this->y = y;
	SDL_SetTextureBlendMode(this->sprite->get_texture(), SDL_BLENDMODE_BLEND);
	this->RenderHeight = 32;
	this->RenderWidth = 32;
	alpha = 255;
	size = 64;
}

Explosion::Explosion(double x, double y, int size, SDL_Renderer* renderer) : GameObject(x, y, explosion_png, renderer) {
	this->x = x;
	this->y = y;
	SDL_SetTextureBlendMode(this->sprite->get_texture(), SDL_BLENDMODE_BLEND);
	this->RenderHeight = size;
	this->RenderWidth = size;
	this->size = size;
}

void Explosion::move(double x_val, double y_val, double deltaTime) {

	int ChangeInAlpha = rand() % 10;
	int dTime = (int)(deltaTime);
	double ChangeInAngle = rand() % 5;
	this->alpha -= ChangeInAlpha * (dTime / 4);
	cout << alpha << endl;
	this->angle = (double)((int)(this->angle + ChangeInAngle) % 360);
	if (this->alpha < 10)
		this->alive = false;
	if (this->alpha < 0) {
		alpha = 0;
		alive = false;
	}
	SDL_SetTextureAlphaMod(this->sprite->get_texture(), this->alpha);
}

void Explosion::render() {

	SDL_Rect srcRect = { 0, 0, sprite->getWidth(), sprite->getHeight() };

	render_rect = { (int)x, (int)y, RenderWidth, RenderHeight };
	sprite->render(&srcRect, &render_rect, NULL);
}