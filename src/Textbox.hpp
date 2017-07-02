

#ifndef TEXTBOX_HPP_
#define TEXTBOX_HPP_
#include "Object.hpp"

class Textbox {

	SDL_Rect textarea;
	SDL_Rect border;
	SDL_Texture* background;
	SDL_Renderer* renderer;
	TTF_Font * font;
	bool noback;

public:

	Textbox(int,int,int,int,SDL_Texture*,SDL_Renderer*, TTF_Font* );
	Textbox();
	void print(char*);
	void print(const char*);
	void setback(bool);
	void move(int,int);

};


#endif /* TEXTBOX_HPP_ */
