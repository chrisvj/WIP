#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* image = NULL;

bool init();
bool loadMedia(std::string path);
void close();

int main(int argc, char* argv[]) {
	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		if (!loadMedia("resources\\startbutton.png")) {
			printf("Failed to load media!\n");
		}
		else {
			SDL_BlitSurface(image, NULL, screenSurface, NULL);
			SDL_UpdateWindowSurface(window);
			SDL_Delay(2000);
		}
	}
	close();
	return 0;
}

bool init(){
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initiailze! Error: %s\n", SDL_GetError());
		success = false;
	}

	else {
		window = SDL_CreateWindow("WIP Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created. Error: %s\n", SDL_GetError());
			success = false;
		}

		else {
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags)&imgFlags))
			{
				printf("SDL_image could not initialize! Error: %s", IMG_GetError());
				success = false;
			}
			screenSurface = SDL_GetWindowSurface(window);
		}
	}
	return success;
}

bool loadMedia(std::string path) {
	bool success = true;
	//int imgFlags = IMG_INIT_PNG;

	image = IMG_Load(path.c_str());
	if (image == NULL) {
		printf("Unable to load image %s! Error: %s\n", path.c_str(), IMG_GetError());
		success = false;
	}
	return success;
}

void close() {
	SDL_FreeSurface(image);
	image = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}