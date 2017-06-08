/*
 * Bullet.hpp
 *
 *  Created on: Jun 3, 2017
 *      Author: bolo
 */

#ifndef SRC_BULLET_HPP_
#define SRC_BULLET_HPP_


#include "Object.hpp"

class Bullet : public Object {

	float angle;

public:

	Bullet(int,int,int,int,int,float,SDL_Texture*,SDL_Renderer*);
	void draw();
	void update();
};

#endif /* SRC_BULLET_HPP_ */
