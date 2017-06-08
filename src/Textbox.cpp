
#include "Textbox.hpp"

Textbox::Textbox(int x,int y,int w,int h,SDL_Texture* background, SDL_Renderer* renderer, TTF_Font* font ){

	SDL_Rect temp = {x,y,w,h};
	textarea = temp;
	border = temp;
	this-> background = background;
	this->renderer = renderer;
	this->font = font;
	noback = false;

}

Textbox::Textbox():background(NULL), renderer(NULL), font(NULL){

	SDL_Rect temp = {0,0,0,0};
	textarea = temp;
	border = temp;
	noback = false;

}

void Textbox::print(char* text){


	SDL_Color fg = {0,0,0};

	SDL_Surface* ftext = TTF_RenderText_Solid(font, text,fg);

	SDL_Texture * temp = SDL_CreateTextureFromSurface( renderer, ftext );

	SDL_QueryTexture(temp,NULL,NULL,&textarea.w,&textarea.h);

	SDL_FreeSurface(ftext);

	if(noback == false) SDL_RenderCopy(renderer,background,NULL,&border);
	SDL_RenderCopy( renderer, temp, NULL, &textarea);

}

void Textbox::setback(bool x){

	noback = x;

}

void Textbox::move(int x, int y){

	textarea.x = x;
	textarea.y = y;

	border.x = x;
	border.y = y;

}


