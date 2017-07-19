/*
 * Object.hpp
 *
 *  Created on: Jun 3, 2017
 *      Author: bolo
 */

#ifndef SRC_OBJECT_HPP_
#define SRC_OBJECT_HPP_
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

#define pi 3.14159265359

class Object{

protected:
	SDL_Rect hitbox;
	SDL_Rect drawbox;

	SDL_Texture* texture;
	SDL_Renderer* render_target;

	int velocity;
	Uint32 m_timer;

public:

	Object(int,int,int,int,int,SDL_Texture*,SDL_Renderer*);
	virtual void move(float);
	virtual void draw();
	virtual void place(int, int);
	Object();
	virtual ~Object();
	SDL_Rect get_hitbox();
	bool check_col(Object &b);

};



#endif /* SRC_OBJECT_HPP_ */
