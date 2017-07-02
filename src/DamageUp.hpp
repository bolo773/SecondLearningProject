/*
 * DamageUp.hpp
 *
 *  Created on: Jun 7, 2017
 *      Author: bolo
 */

#ifndef SRC_DAMAGEUP_HPP_
#define SRC_DAMAGEUP_HPP_
#include "Powerup.hpp"

class DamageUp : public Powerup{

public:
	void activate(Player*);
	DamageUp(int ,int ,int ,int ,int , SDL_Texture* ,SDL_Renderer* );
	~DamageUp();

};



#endif /* SRC_DAMAGEUP_HPP_ */
