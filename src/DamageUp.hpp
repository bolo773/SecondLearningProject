/*
 * DamageUp.hpp
 *
 *  Created on: Jun 7, 2017
 *      Author: bolo
 */

#ifndef SRC_DAMAGEUP_HPP_
#define SRC_DAMAGEUP_HPP_

class DamageUp : public Powerup{

void activate(Player*);
DamageUp(int ,int ,int ,int ,int , SDL_Texture* ,SDL_Renderer* );
~DamageUp();

};



#endif /* SRC_DAMAGEUP_HPP_ */
