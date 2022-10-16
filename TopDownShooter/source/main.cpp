#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "../headers/consts.h"
#include "../headers/GameTexture.h"
#include "../headers/GameObject.h"
#include <iostream>
#include "../headers/Player.h"
#include <vector>
#include "../headers/Bullet.h"


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
GameObject* player;

bool init();
void close();

int main(int argc, char* argv[]) {

	vector<GameObject*> objects;

	if (!init()) {
		printf("Failed to init\n");
	}
	else {
		player = new Player(500, 500,gRenderer);
		GameObject* bullet = new Bullet(900, 500, gRenderer, player_bullet_png);

		bool quit = false;
		SDL_Event e;

		while (!quit) {
			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT) {
					quit = true;
				}
				if (e.key.keysym.sym == SDLK_SPACE) {
					player->fire(objects);
				}
			}
			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			if (currentKeyStates[SDL_SCANCODE_UP]){
				player->move(0, 1);
			}
			if (currentKeyStates[SDL_SCANCODE_DOWN]){
				player->move(0, -1);
			}
			if (currentKeyStates[SDL_SCANCODE_LEFT]){
				player->move(1, 0);
			}
			if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
				player->move(-1, 0);
			}
			
			// clear screen
			SDL_RenderClear(gRenderer);
			// renders sprite on screen
			player->render();

			// render list items
			for (int i = 0; i < objects.size(); i++) {
				objects.at(i)->render();
				objects.at(i)->move(0, 0.5);
			}

			// clean up list
			for (int i = 0; i < objects.size(); i++) {
				if (!objects.at(i)->isAlive()) {
					delete objects.at(i);
					objects.erase(objects.begin() + i);
				}
			}

			// updates screen
			SDL_RenderPresent(gRenderer);
		}
		}

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
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				// init renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

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



void close() {

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();

	delete player;
}

