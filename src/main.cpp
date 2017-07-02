/*
 * main.cpp
 *
 *  Created on: Jun 3, 2017
 *      Author: bolo
 */


#include "World.hpp"

void init(){

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
	IMG_Init(IMG_INIT_PNG);
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
	srand(time(NULL));

}



int main(){

init();

World game;

game.menu();

}
