#include "../headers/Nimble.h"
#include "../headers/consts.h"

Nimble::Nimble() {};

Nimble::Nimble(double x, double y, SDL_Renderer* renderer) : Enemy(x, y, nimble_png, renderer) {
	health = 1;
}

void Nimble::power(vector<GameObject*> objects, Uint32 time) {

}

void Nimble::registerHit() {

}