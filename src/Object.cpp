/*
 * Object.cpp
 *
 *  Created on: Jun 3, 2017
 *      Author: bolo
 */


#include "Object.hpp"
#include <tgmath.h>



Object::Object(int x,int y,int w,int h,int vel, SDL_Texture* texture,SDL_Renderer* renderer)
: drawbox({x,y,w,h}),hitbox({x,y,w,h}),render_target(renderer) , texture(texture), velocity (vel), m_timer(0){}

void Object::move(float angle){

	double radangle = (angle * pi / 180);

	Uint32 temptimer = SDL_GetTicks()/10;


	if(m_timer != temptimer){

		drawbox.x += cos(radangle) * velocity;
		hitbox.x +=   cos(radangle) * velocity;

		drawbox.y -= sin(radangle) * velocity;
		hitbox.y -= sin(radangle) * velocity;

		m_timer = temptimer;
	}

}


void Object::draw(){

	SDL_RenderCopy( render_target, texture, NULL, &drawbox);

}

bool Object::check_col(Object &b){

	int lefta, leftb;
	int topa, topb;
	int bottoma, bottomb;
	int righta, rightb;

	lefta = hitbox.x;
	righta = hitbox.x + hitbox.w;
	topa = hitbox.y;
	bottoma = hitbox.y + hitbox.h;

	leftb = b.hitbox.x;
	rightb = b.hitbox.x + b.hitbox.w;
	topb = b.hitbox.y;
	bottomb = b.hitbox.y + b.hitbox.h;

	if(bottoma <= topb) return false;
	if(topa >= bottomb) return false;
	if(righta <= leftb) return false;
	if(lefta >= rightb) return false;

	return true;
}

 Object::~Object(){


}

SDL_Rect Object::get_hitbox(){

	return hitbox;
}



