#include "../headers/Missile.h"
#include "../headers/consts.h"

Missile::Missile() {};

Missile::Missile(double x, double y, SDL_Renderer* renderer) : GameObject(x, y, missile_png, renderer) {
	
}

void Missile::move(double x_val, double y_val) {

}