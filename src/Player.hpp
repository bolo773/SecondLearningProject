/*
 * Player.hpp
 *
 *  Created on: Jun 3, 2017
 *      Author: bolo
 */

#ifndef SRC_PLAYER_HPP_
#define SRC_PLAYER_HPP_

#include "Object.hpp"
#include "Bullet.hpp"

class Player : public Object {

	int hp;
	int c_hp;
	int c_sprite;

	int damage;

	Uint32 bullet_timer;
	SDL_Texture* bullet_texture;
	SDL_Texture* head_texture;
	Mix_Chunk* shootsound;
	SDL_Rect head_drawbox;


public:

	Player(int,int,int,int,int,SDL_Texture*,SDL_Texture*, SDL_Texture*,Mix_Chunk*,SDL_Renderer*);
	int get_hp();
	int get_c_hp();
	void set_c_hp(int);
	void draw();
	void draw_idle();
	void update( std::vector<Bullet*>* , const Uint8* );
	void shoot(float , std::vector<Bullet*>*);
	void move(float);
	void regen();
	int get_damage();
	void set_damage(int);

};

#endif /* SRC_PLAYER_HPP_ */
