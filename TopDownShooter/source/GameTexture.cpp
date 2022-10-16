#include "../headers/GameTexture.h"
#include <SDL_image.h>

GameTexture::GameTexture() {
	obj_texture = NULL;
	width = height = 0;
}

GameTexture::GameTexture(SDL_Renderer* gRenderer, string file_path) {
	obj_texture = NULL;
	renderer = gRenderer;
	height = width = 0;
	bool loaded = this->loadTexture(file_path);
	if (!loaded) {
		printf("Could not load media\n");
	}
}

GameTexture::~GameTexture() {
	free();
}


void GameTexture::free() {
	if (obj_texture != NULL) {
		SDL_DestroyTexture(obj_texture);
		obj_texture = NULL;
		width = 0;
		height = 0;
	}
}

bool GameTexture::loadTexture(string file_path) {
	// clearing pre existing texture
	free();
	// final texture
	SDL_Texture* new_text = NULL;

	//load surface from image
	SDL_Surface* temp = IMG_Load(file_path.c_str());
	if (temp == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", file_path.c_str(), IMG_GetError());
	}
	else {
		new_text = SDL_CreateTextureFromSurface(renderer, temp);
		if (new_text == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", file_path.c_str(), SDL_GetError());
		}
		else {
			width = temp->w;
			height = temp->h;
		}

		SDL_FreeSurface(temp);
	}

	obj_texture = new_text;
	return obj_texture != NULL;

}

void GameTexture::render(int x, int y, SDL_Rect* clip) {
	
	// set rendering space
	renderRect = { x, y, width, height };

	// set clip dims
	SDL_RenderCopy(renderer, obj_texture, clip, &renderRect);
	
}

int GameTexture::getHeight() {
	return height;
}

int GameTexture::getWidth() {
	return width;
}

SDL_Rect& GameTexture::getRect() {
	return renderRect;
}
