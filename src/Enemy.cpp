/*
 * Enemy.cpp
 *
 *  Created on: Jun 3, 2017
 *      Author: bolo
 */

#include "Enemy.hpp"

Enemy::Enemy(int x,int y,int w,int h,int vel,SDL_Texture* texture,SDL_Texture* bullet_texture, Mix_Chunk* shootsound,Mix_Chunk* deathsound, SDL_Renderer* renderer)
: Object(x,y,w,h,vel,texture,renderer) , bullet_texture(bullet_texture),hp(10),c_hp(10),bullet_timer(0), shootsound(shootsound), deathsound(deathsound){
damage = 1;

}

int Enemy::get_hp(){

	return hp;
}

int Enemy::get_c_hp(){

	return c_hp;

}

void Enemy::set_c_hp(int val){

	c_hp = val;

}

void Enemy::draw(){

	SDL_RenderCopy( render_target, texture, NULL, &drawbox);

}

void Enemy::shoot(float angle, std::vector<Bullet*>* bullet_list){

	Uint32 temptime = SDL_GetTicks()/100;

		if ((temptime - bullet_timer) %5 == 2){

			Bullet* temp = new Bullet(drawbox.x, drawbox.y, 30, 30, 10, angle, bullet_texture, render_target);

			bullet_list->push_back(temp);
			Mix_PlayChannel( -1, shootsound, 0 );

			bullet_timer = temptime;
		}

}

Enemy::~Enemy(){}

void Enemy::update(std::vector<Bullet*>* bullet_list){

	int random = rand()%360;

	float dir = random;

	move(dir);

	shoot(dir,bullet_list);

}

