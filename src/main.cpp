/*
 * main.cpp
 *
 *  Created on: Jun 3, 2017
 *      Author: bolo
 */


#include "World.hpp"
#include "Error.hpp"
void init(){

	if (SDL_Init(SDL_INIT_VIDEO) != 0) throw Error("SDL video did not initialize");
	if (TTF_Init() != 0) throw Error("True type font stuff didnt initialize right");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
	IMG_Init(IMG_INIT_PNG);
	if (Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048) != 0) throw Error("audio stuff isnt initializing");
	srand(time(NULL));

}



int main(){


try {
	init();

	World game;

	game.menu();
}

catch ( Error &error) {

	std::cout << error.get_message();
}

}
