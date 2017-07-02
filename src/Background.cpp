/*
 * Background.cpp
 *
 *  Created on: May 26, 2017
 *      Author: bolo
 */

#include "Background.hpp"

Background::Background():background(NULL),renderer(NULL){};

Background::Background(SDL_Renderer* renderer,SDL_Texture* btexture):background(btexture),renderer(renderer){};

void Background::draw(){

	SDL_RenderCopy( renderer,background, NULL, NULL);

};


Background::~Background(){}
