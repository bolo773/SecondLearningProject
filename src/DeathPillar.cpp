/*
 * DeathPillar.cpp
 *
 *  Created on: Jun 6, 2017
 *      Author: bolo
 */

#include "DeathPillar.hpp"

DeathPillar::DeathPillar(int x, int y, int w, int h, int vel, SDL_Texture* texture, SDL_Texture* bullet_texture, Mix_Chunk* shootsound, SDL_Renderer* renderer)
: Enemy(x,y,w,h,vel,texture,bullet_texture,shootsound,renderer){



}

void DeathPillar::draw(){

	Uint32 sprite = ((SDL_GetTicks() / 100) % 4);

	SDL_Rect srcrect{sprite*100,0,100,100};

	SDL_RenderCopy( render_target, texture, &srcrect, &drawbox);

}

void DeathPillar::update(std::vector<Bullet*>* bullet_list){


	shoot(0,bullet_list);


}


void DeathPillar::shoot(float angle, std::vector<Bullet*>* bullet_list){

	Uint32 temptime = SDL_GetTicks()/100;

		if ((temptime - bullet_timer) >= 10){

			Bullet* temp1 = new Bullet(drawbox.x, drawbox.y, 30, 30, 5, 0 + angle, bullet_texture, render_target);
			Bullet* temp2 = new Bullet(drawbox.x, drawbox.y, 30, 30, 5, 90 + angle, bullet_texture, render_target);
			Bullet* temp3 = new Bullet(drawbox.x, drawbox.y, 30, 30, 5, 180 + angle, bullet_texture, render_target);
			Bullet* temp4 = new Bullet(drawbox.x, drawbox.y, 30, 30, 5, 270 + angle, bullet_texture, render_target);

			bullet_list->push_back(temp1);
			bullet_list->push_back(temp2);
			bullet_list->push_back(temp3);
			bullet_list->push_back(temp4);

			Mix_PlayChannel( -1, shootsound, 0 );

			bullet_timer = temptime;
		}

}
