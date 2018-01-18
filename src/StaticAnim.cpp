/*
 * StaticAnim.cpp
 *
 *  Created on: Jul 25, 2017
 *      Author: bolo
 */


#include "StaticAnim.hpp"

StaticAnim::StaticAnim() : Static(),srcrect({0,0,0,0}), length(0){}

StaticAnim::StaticAnim(int x, int y, int w,int h, int length,SDL_Renderer* renderer, SDL_Texture* texture)
: Static(x,y,w,h,renderer,texture),length(length),srcrect({0,0,100,100}){}

StaticAnim::~StaticAnim(){

}

void StaticAnim::draw(){

	Uint32 sprite = ((SDL_GetTicks() / 100) % length);

	SDL_Rect srcrect{sprite*100,0,100,100};

	SDL_RenderCopy( render_target, texture, &srcrect, &drawbox);

}
