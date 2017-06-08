/*
 * Powerup.hpp
 *
 *  Created on: Jun 6, 2017
 *      Author: bolo
 */

#ifndef SRC_POWERUP_HPP_
#define SRC_POWERUP_HPP_

class Powerup : public Object{


public:
	virtual ~Powerup();
	Powerup(int ,int ,int ,int ,int , SDL_Texture* ,SDL_Renderer* );
	virtual void activate( Player *) = 0;



};



#endif /* SRC_POWERUP_HPP_ */
