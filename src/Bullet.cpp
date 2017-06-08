/*
 * Bullet.cpp
 *
 *  Created on: Jun 3, 2017
 *      Author: bolo
 */

#include "Bullet.hpp"

Bullet::Bullet(int x,int y,int w,int h,int vel,float angle, SDL_Texture* texture,SDL_Renderer* renderer)
:Object(x,y,w,h,vel,texture,renderer),angle(angle){}

void Bullet::draw(){

	SDL_RenderCopy( render_target, texture, NULL, &drawbox);
}


void Bullet::update(){

	move(angle);

}


