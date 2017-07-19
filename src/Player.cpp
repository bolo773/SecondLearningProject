/*
 * Player.cpp
 *
 *  Created on: Jun 3, 2017
 *      Author: bolo
 */

#include "Player.hpp"

Player::Player(int x,int y,int w,int h,int vel,SDL_Texture* texture,SDL_Texture* bullet_texture, SDL_Texture* head_texture,Mix_Chunk* shootsound ,Mix_Chunk* deathsound ,SDL_Renderer* renderer)
: Object(x,y,w,h,vel,texture,renderer),head_drawbox{x,y,w,h} ,
  bullet_texture(bullet_texture),hp(10),c_hp(10),bullet_timer(0),
  shootsound(shootsound), head_texture(head_texture),c_sprite(0),
  deathsound(deathsound) {

	damage = 2;

	hitbox.w = drawbox.w/4;
	hitbox.h = drawbox.h/4;

	hitbox.x = drawbox.x +(drawbox.w - hitbox.w )/2;
	hitbox.y = drawbox.y +(drawbox.h - hitbox.h )/2;

}

Player::Player()
: Object() , hp(0), bullet_texture(NULL), head_texture(NULL), c_hp(0), c_sprite(0), damage(0), bullet_timer(0), shootsound(NULL), deathsound(NULL) {



}

int Player::get_hp(){

	return hp;
}

int Player::get_c_hp(){

	return c_hp;

}

void Player::set_c_hp(int val){

	c_hp = val;

}

void Player::draw(){


	Uint32 sprite = ((SDL_GetTicks() / 100) % 2);

	SDL_Rect srcrect{sprite*100,0,100,100};

	SDL_RenderCopy( render_target, texture, &srcrect, &drawbox);


}

void Player::shoot(float angle, std::vector<Bullet*>* bullet_list){

	Uint32 temptime = SDL_GetTicks()/100;

		if ((temptime - bullet_timer) >= 2){

			Bullet* temp = new Bullet(drawbox.x+ .5 * drawbox.w, drawbox.y + .5 * drawbox.h , 30, 30, 20, angle, bullet_texture,render_target);
			Mix_PlayChannel( -1, shootsound, 0 );

			bullet_list->push_back(temp);

			bullet_timer = temptime;
		}

}

void Player::draw_idle(){

	SDL_Rect srcrect{0,0,100,100};

	SDL_RenderCopy( render_target, texture, &srcrect, &drawbox);

}


void Player::update( std::vector<Bullet*>* bullet_out,const Uint8* state){


	//handle player events
	if(state[SDL_SCANCODE_W]){
		move(90);
		draw();
	} else
	if(state[SDL_SCANCODE_S]) {
		move(270);
		draw();
	} else
	if(state[SDL_SCANCODE_A]) {
		move(180);
		draw();
	}else
	if(state[SDL_SCANCODE_D]){
		move(0);
		draw();
	}else{
		draw_idle();

	}

	if(state[SDL_SCANCODE_UP]) {
		shoot(90,bullet_out);
		c_sprite = 0;
	} else
	if(state[SDL_SCANCODE_DOWN]){
		shoot(270,bullet_out);
		c_sprite = 2;
	} else
	if(state[SDL_SCANCODE_LEFT]){
		shoot(180,bullet_out);
		c_sprite = 3;
	} else

	if(state[SDL_SCANCODE_RIGHT]){
		shoot(0,bullet_out);
		c_sprite = 1;
	}

	if(drawbox.x < 0) place(0,drawbox.y);
	if(drawbox.x > SCREEN_WIDTH) place(SCREEN_WIDTH,drawbox.y);
	if(drawbox.y < 0) place(drawbox.x,0);
	if(drawbox.y > SCREEN_HEIGHT) place(drawbox.x,SCREEN_HEIGHT);

	SDL_Rect srcrect{c_sprite*100,0,100,100};
	SDL_RenderCopy( render_target, head_texture, &srcrect, &head_drawbox);


}


void Player::move(float angle){

	double radangle = (angle * pi / 180);

	Uint32 temptimer = SDL_GetTicks()/10;


	if(m_timer != temptimer){

		drawbox.x += cos(radangle) * velocity;
		hitbox.x +=   cos(radangle) * velocity;
		head_drawbox.x +=   cos(radangle) * velocity;
		//std::cout << cos(radangle);

		drawbox.y -= sin(radangle) * velocity;
		hitbox.y -= sin(radangle) * velocity;
		head_drawbox.y -= sin(radangle) * velocity;


		m_timer = temptimer;
	}

}

void Player::place(int x, int y){

	int xdisp = drawbox.x -x;
	int ydisp = drawbox.y -y;

	drawbox.x = x;
	hitbox.x -= xdisp;
	head_drawbox.x -= xdisp;

	drawbox.y = y;
	hitbox.y -=  ydisp;
	head_drawbox.y -= ydisp;

}


int Player::get_damage(){

	return damage;

}


void Player::set_damage(int newval){

	damage= newval;
}

