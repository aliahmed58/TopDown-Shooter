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
#include "../headers/Missile.h"
#include <SDL_ttf.h>
#include "../headers/Smoke.h"
#include "../headers/Explosion.h"

using namespace std;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Player* player;

SDL_Texture* buttoncornertexture = NULL;
SDL_Texture* buttonmiddletexture = NULL;
SDL_Texture* buttonsidetexture = NULL;

//ali
bool init();
void close();
void create_enemies(vector<GameObject*>& objs);
bool check_collision(GameObject* a, GameObject* b, int y_offset);
void clear_list(vector<GameObject*>& objects, bool all);
void update_delta(Uint64& LAST, Uint64& NOW, double& deltaTime);

//shaz
bool loadMedia();
void CreateMenuScreen();
void DrawButton(int H, int W, int x, int y);
char IntToChar(int N);
SDL_Texture* loadTexture(std::string path);

int main(int argc, char* argv[]) {

	vector<GameObject*> objects;
	vector<GameObject*> missiles;
	bool inMenu = true;

	if (!init()) {
		printf("Failed to init\n");
	}
	else {
		loadMedia();

		Uint64 NOW = SDL_GetPerformanceCounter();
		Uint64 LAST = 0;
		double deltaTime = 0;

		bool explosion = false;
		// create player object
		player = new Player(500, 500, gRenderer);

		bool quit = false;
		SDL_Event e;

		unsigned int counter = 0;
		unsigned int smoke_counter = 0;
		CreateMenuScreen();

		while (!quit) {
			update_delta(LAST, NOW, deltaTime);
			while (inMenu) {
				SDL_RenderPresent(gRenderer);
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT) {
						close(); exit(0);
					}

					if (e.type == SDL_MOUSEBUTTONDOWN) {
						if (e.button.x > 575 && e.button.x < 775 && e.button.y > 475 && e.button.y < 575) { close(); exit(0); } //EXIT
						if (e.button.x > 575 && e.button.x < 775 && e.button.y > 275 && e.button.y < 375) { inMenu = false; } //PLAY
					}
				}
				update_delta(LAST, NOW, deltaTime);
			}
			counter += deltaTime;

			if (counter > 4000) {
				create_enemies(objects);
				counter = 0;
			}

			smoke_counter += deltaTime;
			if (smoke_counter > 1) {
				smoke_counter = 0;
				for (int i = 0; i < objects.size(); i++) {
					if (objects.at(i)->get_type() == "missile") {
						int x = objects.at(i)->get_x();
						int y = objects.at(i)->get_y();
						GameObject* S1 = new Smoke(x + 16, y + 32, gRenderer);
						objects.insert(objects.begin(), S1);
						break;
					}
				}
			}
		
			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT) {
					quit = true;
				}
				if (e.key.keysym.sym == SDLK_SPACE) {
					player->power(objects, deltaTime);
				}
				if ((e.key.keysym.sym) == SDLK_b) {
					player->missile(objects, SDL_GetTicks());
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
			SDL_SetRenderDrawColor(gRenderer, 0x36, 0x45, 0x4F, 0xaa);
			SDL_RenderClear(gRenderer);
			// renders sprite on screen
			player->render();

			// render list items
			for (int i = 0; i < objects.size(); i++) {

				objects.at(i)->render();
				objects.at(i)->move(0, 1, deltaTime);
				objects.at(i)->fire(objects, SDL_GetTicks());

				if (check_collision(player, objects.at(i), 0)) {
					if (objects.at(i)->get_type() != "player_bullet" &&
						objects.at(i)->get_type() != "missile") {
					}
				}

				if (objects.at(i)->get_type() == "ranger") {
					objects.at(i)->power(objects, deltaTime);
				}

				for (int j = 0; j < objects.size(); j++) {

					if (objects.at(i) == objects.at(j)) continue;
					if (check_collision(objects.at(i), objects.at(j), 0)) {
						if (objects.at(i)->get_type() == "player_bullet") {
							explosion = true;
							objects.at(i)->kill(objects.at(i)->get_x(), objects.at(i)->get_y(), objects);
							objects.at(j)->kill(objects.at(j)->get_x(), objects.at(j)->get_y(), objects);
						}
						if (objects.at(i)->get_type() == "missile") {
							if (!(objects.at(j)->get_type() == "ranger_bullet") &&
								!(objects.at(j)->get_type() == "nimble_bullet")) {
								objects.at(i)->kill(objects.at(i)->get_x(), objects.at(i)->get_y(), objects);
								objects.at(j)->kill(objects.at(j)->get_x(), objects.at(j)->get_y(), objects);
							}
						}
					}
				}
				for (int j = 0; j < objects.size(); j++) {

					if (objects.at(i) == objects.at(j)) continue;
					if (check_collision(objects.at(i), objects.at(j), -10)) {
						if (objects.at(j)->get_type() == "nimble") {
							if (objects.at(i)->get_type() == "player_bullet" ||
								objects.at(i)->get_type() == "missile") {
								objects.at(j)->power(objects, deltaTime);
							}
						}
					}
				}
			}
			// check collisions
			// clean up list
			clear_list(objects, false);
			// updates screen
			SDL_RenderPresent(gRenderer);
			
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
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);

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

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	buttoncornertexture = loadTexture("./images/button_corner.png");
	if (buttoncornertexture == NULL)
	{
		printf("Failed to load button_corner image!\n");
		success = false;
	}

	buttonmiddletexture = loadTexture("./images/button_middle.png");
	if (buttonmiddletexture == NULL)
	{
		printf("Failed to load button_middle image!\n");
		success = false;
	}

	buttonsidetexture = loadTexture("./images/button_side.png");
	if (buttonsidetexture == NULL)
	{
		printf("Failed to load button_side image!\n");
		success = false;
	}

	return success;
}

void CreateMenuScreen() {

	int H = 10;  //no of times to draw sprite
	int W = 10;

	int HC = 10;  //Space to leave from the top
	int WC = 320; //Space to leave from the right

	DrawButton(H, W, WC, HC); //Menu

	H = 1;
	W = 5;

	HC = 10 + 4 * 64;
	WC = 320 + 2.5 * 64;

	DrawButton(H, W, WC, HC); //Play Button

	H = 1;
	W = 5;

	HC = 10 + 7 * 64;
	WC = 320 + 2.5 * 64;

	DrawButton(H, W, WC, HC); //Exit Button

	TTF_Init();
	TTF_Font* Sans = TTF_OpenFont("./images/sans.ttf", 72);
	if (!Sans)
		printf("Unable to open font");
	SDL_Color White = { 255, 255, 255 };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "MENU", White);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 575;  //controls the rect's x coordinate 
	Message_rect.y = 50; // controls the rect's y coordinte
	Message_rect.w = 200; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect
	SDL_RenderCopyEx(gRenderer, Message, NULL, &Message_rect, 0, NULL, SDL_FLIP_NONE);

	surfaceMessage = TTF_RenderText_Solid(Sans, "PLAY", White);
	Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
	Message_rect.x = 575;  //controls the rect's x coordinate 
	Message_rect.y = 275; // controls the rect's y coordinte
	Message_rect.w = 200; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect
	SDL_RenderCopyEx(gRenderer, Message, NULL, &Message_rect, 0, NULL, SDL_FLIP_NONE);

	surfaceMessage = TTF_RenderText_Solid(Sans, "EXIT", White);
	Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
	Message_rect.x = 575;  //controls the rect's x coordinate 
	Message_rect.y = 475; // controls the rect's y coordinte
	Message_rect.w = 200; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect
	SDL_RenderCopyEx(gRenderer, Message, NULL, &Message_rect, 0, NULL, SDL_FLIP_NONE);


	//Buttons

}

void DrawButton(int H, int W, int x, int y) {
	SDL_Rect R1;
	SDL_Rect* R = &R1;

	for (int h = 0; h <= H; h++) {
		for (int w = 0; w <= W; w++) {

			R1.x = x + 64 * w;
			R1.y = y + 64 * h;
			R1.h = 64;
			R1.w = 64;


			if (w != 0 && w != W && h != 0 && h != H) {        //Middle
				SDL_RenderCopyEx(gRenderer, buttonmiddletexture, NULL, R, 0, NULL, SDL_FLIP_NONE);
			}
			else if (w == 0 && w != W && h != 0 && h != H) {   //Left Side
				SDL_RenderCopyEx(gRenderer, buttonsidetexture, NULL, R, 90, NULL, SDL_FLIP_NONE);
			}
			else if (w != 0 && w == W && h != 0 && h != H) {   //Right Side
				SDL_RenderCopyEx(gRenderer, buttonsidetexture, NULL, R, 90, NULL, SDL_FLIP_VERTICAL);
			}
			else if (w != 0 && w != W && h == 0 && h != H) {   //Top
				SDL_RenderCopyEx(gRenderer, buttonsidetexture, NULL, R, 180, NULL, SDL_FLIP_NONE);
			}
			else if (w != 0 && w != W && h != 0 && h == H) {   //Bottom
				SDL_RenderCopyEx(gRenderer, buttonsidetexture, NULL, R, 0, NULL, SDL_FLIP_NONE);
			}
			else if (w == 0 && w != W && h == 0 && h != H) {   //Top Left Corner
				SDL_RenderCopyEx(gRenderer, buttoncornertexture, NULL, R, 90, NULL, SDL_FLIP_NONE);
			}
			else if (w == 0 && w != W && h != 0 && h == H) {   //Bottom Left Corner
				SDL_RenderCopyEx(gRenderer, buttoncornertexture, NULL, R, 0, NULL, SDL_FLIP_NONE);
			}
			else if (w != 0 && w == W && h == 0 && h != H) {   //Top Right Corner
				SDL_RenderCopyEx(gRenderer, buttoncornertexture, NULL, R, 180, NULL, SDL_FLIP_NONE);
			}
			else if (w != 0 && w == W && h != 0 && h == H) {   //Bottom Right Corner
				SDL_RenderCopyEx(gRenderer, buttoncornertexture, NULL, R, 270, NULL, SDL_FLIP_NONE);
			}
		}
	}


}

char IntToChar(int N) {
	switch (N) {
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	case 0:
		return '0';
	}
}

SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}


void close() {

	//Free loaded image
	SDL_DestroyTexture(buttoncornertexture);
	buttoncornertexture = NULL;

	SDL_DestroyTexture(buttonmiddletexture);
	buttonmiddletexture = NULL;

	SDL_DestroyTexture(buttonsidetexture);
	buttonsidetexture = NULL;
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

void update_delta(Uint64& LAST, Uint64& NOW, double& deltaTime) {

	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();
	deltaTime = ((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

}

void clear_list(vector<GameObject*>& objects, bool all) {
	for (int i = 0; i < objects.size(); i++) {
		if (!all) {
			if (!objects.at(i)->isAlive()) {
				objects.at(i)->getTexture()->free();
				delete objects.at(i);
				objects.erase(objects.begin() + i);
			}
		}
		else {
			objects.at(i)->getTexture()->free();
			delete objects.at(i);
			objects.erase(objects.begin() + i);
		}
	}
}
