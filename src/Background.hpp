/*
 * Background.hpp
 *
 *  Created on: May 25, 2017
 *      Author: bolo
 */

#ifndef BACKGROUND_HPP_
#define BACKGROUND_HPP_

#include "Static.hpp"

class Background{

protected:

	SDL_Texture* background;
	SDL_Renderer* renderer;

public:

	virtual ~Background();
	Background();
	Background(SDL_Renderer*,SDL_Texture*);
	virtual void draw();

};


#endif /* BACKGROUND_HPP_ */
