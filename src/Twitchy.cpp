/*
 * Twitchy.cpp
 *
 *  Created on: Jun 21, 2017
 *      Author: bolo
 */

#include "Twitchy.hpp"


Twitchy::Twitchy(int x,int y,int w,int h,int vel,SDL_Texture* texture,SDL_Texture* bullet,Mix_Chunk* sound,Mix_Chunk* deathsound, SDL_Renderer* renderer)
: Enemy(x,y,w,h,vel,texture,bullet,sound,deathsound,renderer){}

void Twitchy::draw(){


	Uint32 c_sprite = SDL_GetTicks()/100 % 5;

	SDL_Rect srcrect{c_sprite*100,0,100,100};

	SDL_RenderCopy( render_target, texture, &srcrect, &drawbox);


}
 Twitchy::~Twitchy(){


}
void Twitchy::update(std::vector<Bullet*>* bullet_list){

	int random = rand()%360;

	float dir = random;

	move(dir);

	shoot(dir,bullet_list);


}

void Twitchy::shoot(float dir , std::vector<Bullet*>* bullet_list){

	Uint32 temptime = SDL_GetTicks()/100;

	if ((temptime - bullet_timer) %5 == 2){

		Bullet* temp = new Bullet(drawbox.x, drawbox.y, 30, 30, 10, dir, bullet_texture, render_target);

		bullet_list->push_back(temp);
		Mix_PlayChannel( -1, shootsound, 0 );

		bullet_timer = temptime;
	}


}
