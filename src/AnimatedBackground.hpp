/*
 * AnimatedBackground.hpp
 *
 *  Created on: May 25, 2017
 *      Author: bolo
 */

#ifndef ANIMATEDBACKGROUND_HPP_
#define ANIMATEDBACKGROUND_HPP_

#include "Background.hpp"

class AnimatedBackground : public Background{

	Uint32 utime;
	Uint32 csprite;

public:

	void draw();
	virtual ~AnimatedBackground();
	AnimatedBackground();
	AnimatedBackground(SDL_Renderer*, SDL_Texture*);
};




#endif /* ANIMATEDBACKGROUND_HPP_ */
