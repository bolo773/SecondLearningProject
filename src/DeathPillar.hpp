/*
 * DeathPillar.hpp
 *
 *  Created on: Jun 6, 2017
 *      Author: bolo
 */

#ifndef SRC_DEATHPILLAR_HPP_
#define SRC_DEATHPILLAR_HPP_

#include "Enemy.hpp"

class DeathPillar : public Enemy{

public:
	DeathPillar(int,int,int,int,int,SDL_Texture*,SDL_Texture*,Mix_Chunk*,Mix_Chunk*, SDL_Renderer* );
	void draw();
	virtual void update(std::vector<Bullet*>* bullet_list);
	void shoot(float,std::vector<Bullet*>*);
};



#endif /* SRC_DEATHPILLAR_HPP_ */
