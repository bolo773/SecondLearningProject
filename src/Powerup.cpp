/*
 * Powerup.cpp
 *
 *  Created on: Jun 7, 2017
 *      Author: bolo
 */

#include "Powerup.hpp"

Powerup::Powerup(int x,int y,int w,int h,int vel, SDL_Texture* texture,SDL_Renderer* renderer)
: Object(x,y,w,h,vel,texture,renderer){}

Powerup::~Powerup(){}




