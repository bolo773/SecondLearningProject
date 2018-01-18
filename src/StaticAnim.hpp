/*
 * StaticAnim.hpp
 *
 *  Created on: Jul 25, 2017
 *      Author: bolo
 */

#ifndef SRC_STATICANIM_HPP_
#define SRC_STATICANIM_HPP_

#include "Static.hpp"

class StaticAnim : public Static{

	SDL_Rect srcrect;

	int length;

public:

	StaticAnim();
	StaticAnim(int, int, int,int,int, SDL_Renderer*,SDL_Texture*);
	~StaticAnim();
	void draw();

};

#endif /* SRC_STATICANIM_HPP_ */
