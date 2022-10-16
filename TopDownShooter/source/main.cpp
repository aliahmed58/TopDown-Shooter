#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "../headers/consts.h"
#include "../headers/GameTexture.h"
#include "../headers/GameObject.h"
#include <iostream>


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;


bool init();
void close();

int main(int argc, char* argv[]) {
	if (!init()) {
		printf("Failed to init\n");
	}
	else {
		GameObject x(10, 10, "./sprites/Player.png",gRenderer);

		bool quit = false;
		SDL_Event e;

		while (!quit) {
			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT) {
					quit = true;
				}
			}

			// clear screen
			SDL_RenderClear(gRenderer);
			// renders sprite on screen
			SDL_Rect clip = { 0, 0, 64, 64 };
			cout << x.getTexture().getHeight();
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
}

