/*
 * DamageUp.cpp
 *
 *  Created on: Jun 7, 2017
 *      Author: bolo
 */

#include "DamageUp.hpp"
DamageUp::DamageUp(int x,int y,int w,int h,int vel, SDL_Texture* texture,SDL_Renderer* renderer) : Powerup(x,y,w,h,vel,texture,renderer){}

void DamageUp::activate(Player* player){

	int c_damage = player->get_damage();
	c_damage++;
	player->set_damage(c_damage);


}

DamageUp::~DamageUp(){}


