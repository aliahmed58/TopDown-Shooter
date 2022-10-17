#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "../headers/consts.h"
#include "../headers/GameTexture.h"
#include "../headers/GameObject.h"
#include <iostream>
#include "../headers/Player.h"
#include <vector>
#include "../headers/Nimble.h"
#include "../headers/Ranger.h"
#include "../headers/Bullet.h"

using namespace std;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Player* player;

bool init();
void close();
void create_enemies(vector<GameObject*>& objs);
bool check_collision(GameObject* a, GameObject* b, int y_offset);

int main(int argc, char* argv[]) {

	vector<GameObject*> objects;

	if (!init()) {
		printf("Failed to init\n");
	}
	else {
		// current start time
		Uint32 time = 0;
		Uint64 NOW = SDL_GetPerformanceCounter();
		Uint64 LAST = 0;
		double deltaTime = 0;

		// create player object
		player = new Player(500, 500, gRenderer);

		bool quit = false;
		SDL_Event e;

		unsigned int counted_frames = 0;
		unsigned int counter = 0;

		while (!quit) {

			LAST = NOW;
			NOW = SDL_GetPerformanceCounter();
			deltaTime = ((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

			// get time
			time = SDL_GetTicks();

			// calculate fps
			int avgFps = counted_frames / (SDL_GetTicks() / 1000.0f);
			if (avgFps > 2000000) avgFps = 0;

			// generate enemies every 2 seconds
			//if (((time + 990) / 10) % 300 == 0) {
			//	create_enemies(objects);
			//}
			if (counter < 300) {
				counter++;
			}
			if (counter >= 300) {
				create_enemies(objects);
				counter = 0;
			}

			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT) {
					quit = true;
				}
				if (e.key.keysym.sym == SDLK_SPACE) {
					player->power(objects, time, deltaTime);
				}
				if ((e.key.keysym.sym) == SDLK_b) {
					player->missile(objects, time);
				}

			}
			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			if (currentKeyStates[SDL_SCANCODE_UP]) {
				player->move(0, 1, deltaTime);
			}
			if (currentKeyStates[SDL_SCANCODE_DOWN]) {
				player->move(0, -1, deltaTime);
			}
			if (currentKeyStates[SDL_SCANCODE_LEFT]) {
				player->move(1, 0, deltaTime);
			}
			if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
				player->move(-1, 0, deltaTime);
			}


			// clear screen
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xaa);
			SDL_RenderClear(gRenderer);
			// renders sprite on screen
			player->render();

			// render list items
			for (int i = 0; i < objects.size(); i++) {

				objects.at(i)->render();
				objects.at(i)->move(0, 1, deltaTime);
				if (objects.at(i)->get_type() == "ranger") {
					objects.at(i)->power(objects, time, deltaTime);
				}

				for (int j = 0; j < objects.size(); j++) {

					if (objects.at(i) == objects.at(j)) continue;
					if (check_collision(objects.at(i), objects.at(j), 0)) {
						if (objects.at(i)->get_type() == "player_bullet") {
							objects.at(i)->kill();
							objects.at(j)->kill();
						}
						if (objects.at(i)->get_type() == "enemy_bullet") {
							objects.at(i)->kill();
						}
					}
				}
				for (int j = 0; j < objects.size(); j++) {

					if (objects.at(i) == objects.at(j)) continue;
					if (check_collision(objects.at(i), objects.at(j), -10)) {
						if (objects.at(j)->get_type() == "nimble") {
							if (objects.at(i)->get_type() != "enemy_bullet") {
								objects.at(j)->power(objects, time, deltaTime);
							}
						}
					}
				}
				
			}
			// check collisions

			// clean up list
			for (int i = 0; i < objects.size(); i++) {
				if (!objects.at(i)->isAlive()) {
					objects.at(i)->getTexture()->free();
					delete objects.at(i);
					objects.erase(objects.begin() + i);
				}
			}

			// updates screen
			SDL_RenderPresent(gRenderer);
			++counted_frames;

		}
	}
	cout << objects.size() << endl;
	close();

	return 0;
}



bool init() {
	bool success = true;

	// init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		// create window 
		gWindow = SDL_CreateWindow("Top Down Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL Error %s\n", SDL_GetError());
			success = false;
		}
		else {

			// init renderer
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				// init renderer color
				SDL_SetRenderDrawColor(gRenderer, 0x00,0x00,0x00,0x00);

				//init png loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL image could not init! SDL_image error: %s \n", IMG_GetError());
					success = false;
				}

			}
		}
	}
	return success;
}

void create_enemies(vector<GameObject*>& objs) {

	int rand_x = rand() % 1000;
	int rand_x2 = rand() % 1000;

	if (abs(rand_x - rand_x2) < 64) {
		if (rand_x > rand_x2) {
			int diff = rand_x - rand_x2;
			rand_x2 -= diff + 20;
			rand_x += diff + 20;
		}
		else {
			int diff = rand_x2 - rand_x;
			rand_x -= diff + 20;
			rand_x2 += diff + 20;
		}
	}
	GameObject* r = new Ranger(rand_x, -1, gRenderer, player);
	GameObject* n = new Nimble(rand_x2, -1, gRenderer);

	objs.insert(objs.begin(), r);
	objs.insert(objs.begin(), n);
}

void close() {

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();

	delete player;
}

bool check_collision(GameObject* a, GameObject* b, int y_offset) {

	SDL_Rect rect1 = a->getCollisionRect();
	SDL_Rect rect2 = b->getCollisionRect();

	return (
		rect1.x < rect2.x + rect2.w &&
		rect1.x + rect1.w > rect2.x &&
		rect1.y + y_offset < rect2.y + rect2.h &&
		rect1.h + rect1.y + y_offset> rect2.y
		);
}
