/*
 * World.hpp
 *
 *  Created on: May 25, 2017
 *      Author: bolo
 */

#ifndef WORLD_HPP_
#define WORLD_HPP_

#include "Object.hpp"
#include "Enemy.hpp"
#include "DeathPillar.hpp"
#include "Player.hpp"
#include "Static.hpp"
#include "Bullet.hpp"
#include "DamageUp.hpp"
#include "Powerup.hpp"
#include "Textbox.hpp"
#include "Background.hpp"
#include "AnimatedBackground.hpp"
#include "Twitchy.hpp"


class World {

	Textbox* dialoguebox;
	SDL_Window* game_window;
	SDL_Renderer* game_renderer;

	Textbox* player_hp;
	Textbox* player_damage;

	SDL_Rect game_viewport;
	SDL_Rect HUD_viewport;
	SDL_Rect full_viewport;

	std::vector<Bullet*> enemy_bullets;
	std::vector<Bullet*> player_bullets;
	std::vector<Enemy*> enemies;
	std::vector<SDL_Texture*> textures;
	std::vector<Object*> entitys;
	std::vector<Textbox*> damageboxes;
	std::vector<Powerup*> powerups;

	Background background;

	//sounds
	std::vector<Mix_Chunk*> sfx;

	const Uint8* state;

	TTF_Font* font;

	Player player;

	Textbox endgame_message;

	int timer;

	int diff;

	int score;

public:

	World();
	~World();
	void gameloop();
	void quit();
	void message( Textbox & output, char* message , SDL_Renderer* gamerenderer);
	int get_score();
	void bullet_update(std::vector<Bullet*> & list);
	void enemy_update();
	void add_enemy();
	void menu();
	void levelup();

};


#endif /* WORLD_HPP_ */
