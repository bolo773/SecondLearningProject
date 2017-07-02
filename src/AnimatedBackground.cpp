/*
 * AnimatedBackground.cpp
 *
 *  Created on: May 26, 2017
 *      Author: bolo
 */
#include "AnimatedBackground.hpp"

AnimatedBackground::AnimatedBackground(): Background(), utime(0), csprite(0){}

AnimatedBackground::AnimatedBackground(SDL_Renderer* renderer, SDL_Texture* texture) : Background(renderer,texture), utime(0), csprite(0){}

void AnimatedBackground::draw(){

	Uint32 sprite = (SDL_GetTicks()/10);

	if((sprite - utime) >= 5){

		utime = sprite;
		csprite = sprite % 800;

	}

	if (csprite >= 799) csprite = 0;

	SDL_Rect srcrect{csprite , 0, 100, 100};
	SDL_RenderCopy( renderer, background, &srcrect, NULL);

}

AnimatedBackground::~AnimatedBackground(){}


