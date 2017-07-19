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

	double radangle = ((angle / 180) * pi);

	Uint32 temptimer = SDL_GetTicks()/10;


	if(m_timer != temptimer){

		float xdisp = cos(radangle) * velocity;
		float ydisp = sin(radangle) * velocity;
		if(xdisp > -.1 && xdisp < .1 ) xdisp = 0;
		if(ydisp > -.1 && ydisp < .1 ) ydisp = 0;


		drawbox.x += xdisp;
		hitbox.x +=   xdisp;

		drawbox.y -= ydisp;
		hitbox.y -=  ydisp;

		m_timer = temptimer;
	}

}

void Object::place(int x, int y){

	int xdisp = drawbox.x -x;
	int ydisp = drawbox.y -y;

	drawbox.x = x;
	hitbox.x +=   xdisp;

	drawbox.y = y;
	hitbox.y -=  ydisp;

}



Object::Object() : drawbox({0,0,0,0}),hitbox({0,0,0,0}), render_target(NULL), texture(NULL), velocity(0), m_timer(0){


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



