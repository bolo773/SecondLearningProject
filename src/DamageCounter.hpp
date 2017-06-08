/*
 * DamageCounter.hpp
 *
 *  Created on: Jun 6, 2017
 *      Author: bolo
 */

#ifndef SRC_DAMAGECOUNTER_HPP_
#define SRC_DAMAGECOUNTER_HPP_


class DamageCounter{


	SDL_Rect textarea;
	SDL_Renderer* renderer;
	TTF_Font * font;
	Uint32 lifetime;
	Uint32 creationtime;

public:

	DamageCounter(int,int,int,int,SDL_Renderer*, TTF_Font* );
	DamageCounter();
	void print(char*);
	void setback(bool);


};


#endif /* SRC_DAMAGECOUNTER_HPP_ */
