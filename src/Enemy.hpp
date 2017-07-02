/*
 * Enemy.hpp
 *
 *  Created on: Jun 3, 2017
 *      Author: bolo
 */

#ifndef SRC_ENEMY_HPP_
#define SRC_ENEMY_HPP_
#include "Object.hpp"
#include "Bullet.hpp"


class Enemy : public Object{


protected:

	int hp;
	int c_hp;
	int damage;

	Uint32 bullet_timer;
	SDL_Texture* bullet_texture;
	Mix_Chunk* shootsound;
	Mix_Chunk* deathsound;


public:

	Enemy(int,int,int,int,int,SDL_Texture*,SDL_Texture*,Mix_Chunk*, Mix_Chunk*,SDL_Renderer* );
	~Enemy();
	int get_hp();
	int get_c_hp();
	void set_c_hp(int);
	void draw();
	virtual void update(std::vector<Bullet*>* bullet_list);
	virtual void shoot(float,std::vector<Bullet*>*);

};

#endif /* SRC_ENEMY_HPP_ */
