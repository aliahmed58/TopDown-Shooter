#include "../headers/GameTexture.h"
#include <SDL_image.h>

GameTexture::GameTexture() {
	obj_texture = NULL;
	width = height = 0;
}

GameTexture::GameTexture(SDL_Renderer* gRenderer, string file_path) {
	obj_texture = NULL;
	renderer = gRenderer;
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
			renderRect.w = width;
			renderRect.h = height;
		}

		SDL_FreeSurface(temp);
	}

	obj_texture = new_text;
	return obj_texture != NULL;

}

void GameTexture::render(SDL_Rect* clip, SDL_Rect* render_rect, double angle, 
	SDL_RendererFlip flipType ) {
	SDL_RenderCopyEx(renderer, obj_texture, clip, render_rect, angle, NULL, flipType);
	
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

SDL_Texture* GameTexture::get_texture() {
	return obj_texture;
}