#include "../headers/Smoke.h"
#include "../headers/consts.h"

Smoke::Smoke() {};

Smoke::Smoke(double x, double y, SDL_Renderer* renderer) : GameObject(x, y, smoke_png, renderer) {
	this->x = x;
	this->y = y;
	type = "smoke";
	SDL_SetTextureBlendMode(this->getTexture()->get_texture(), SDL_BLENDMODE_BLEND);
	this->RenderHeight = 14;
	this->RenderWidth = 14;
	
}

void Smoke::move(double x_val, double y_val, double deltaTime) {
	double ChangeInAlpha = rand() % 50;
	double ChangeInAngle = rand() % 15;
	this->alpha = this->alpha - ChangeInAlpha;
	this->angle = (double)((int)(this->angle + ChangeInAngle) % 360);
	if (this->alpha < 10)
		this->alive = false;
	if (this->alpha < 0)
		this->alpha = 0;

	double ChangeInSize = rand() % 5;
	RenderHeight += ChangeInSize;
	RenderWidth += ChangeInSize;

	SDL_SetTextureAlphaMod(this->sprite->get_texture() , this->alpha);
}