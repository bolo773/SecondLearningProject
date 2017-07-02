/*
 * Twitchy.hpp
 *
 *  Created on: Jun 21, 2017
 *      Author: bolo
 */

#ifndef SRC_TWITCHY_HPP_
#define SRC_TWITCHY_HPP_

#include "Enemy.hpp"

class Twitchy : public Enemy {


public:
	Twitchy(int,int,int,int,int,SDL_Texture*,SDL_Texture*,Mix_Chunk*,Mix_Chunk*, SDL_Renderer*);
	~Twitchy();
	void draw();
	virtual void update(std::vector<Bullet*>* bullet_list);
	void shoot(float,std::vector<Bullet*>*);


};



#endif /* SRC_TWITCHY_HPP_ */
