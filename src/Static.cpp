/*
 * Static.cpp
 *
 *  Created on: Jun 3, 2017
 *      Author: bolo
 */
#include "Object.hpp"
#include "Static.hpp"

Static::Static(){}
Static::Static(int x, int y, int w, int h, SDL_Renderer* renderer, SDL_Texture* texture) : drawbox({x,y,w,h}),render_target(renderer),texture(texture){}
Static::~Static(){}
void Static::draw(){

	SDL_RenderCopy( render_target, texture, NULL, &drawbox);

}

