

#ifndef STATIC_HPP_
#define STATIC_HPP_

#include "Object.hpp"

class Static{

protected:

	SDL_Rect drawbox;

	SDL_Renderer* render_target;

	SDL_Texture* texture;

public:

	Static();
	Static(int, int, int,int, SDL_Renderer*,SDL_Texture*);
	~Static();
	void draw();

};

#endif /* STATIC_HPP_ */
