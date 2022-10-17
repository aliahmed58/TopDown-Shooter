#include "../headers/Explosion.h"
#include "../headers/consts.h"

Explosion::Explosion() {};

Explosion::Explosion(double x, double y, SDL_Renderer* renderer) : GameObject(x, y, explosion_png, renderer) {
	this->x = x;
	this->y = y;
	SDL_SetTextureBlendMode(this->sprite->get_texture(), SDL_BLENDMODE_BLEND);
	this->RenderHeight = 64;
	this->RenderWidth = 64;

}

void Explosion::move(double x_val, double y_val) {
	double ChangeInAlpha = rand() % 50;
	double ChangeInAngle = rand() % 5;
	this->alpha = this->alpha - ChangeInAlpha;
	this->angle = (double)((int)(this->angle + ChangeInAngle) % 360);
	if (this->alpha < 10)
		this->alive = false;
	if (this->alpha < 0)
		this->alpha = 0;
	SDL_SetTextureAlphaMod(this->sprite->get_texture(), this->alpha);
}