/*
 * main.cpp
 *
 *  Created on: Jun 3, 2017
 *      Author: bolo
 */

#include "Object.hpp"
#include "Enemy.hpp"
#include "DeathPillar.hpp"
#include "Player.hpp"
#include "Static.hpp"
#include "Bullet.hpp"
#include "Textbox.hpp"


SDL_Texture* loadtext(char* path, SDL_Renderer*);


void bullet_update(std::vector<Bullet*> &);
void enemy_update(std::vector<Enemy*> &, std::vector<Bullet*> &,std::vector<Bullet*> & , Player player);

void player_update(std::vector<Enemy*> &, std::vector<Bullet*> &,std::vector<Bullet*> & , Player player);


void add_enemy(int,std::vector<Enemy*> &, SDL_Renderer*, SDL_Texture*);
void message( const Uint8 stuff, Textbox output, char* message);



void message( Textbox & output, char* message , SDL_Renderer* gamerenderer){

	SDL_RenderClear(gamerenderer);

	Uint32 timer = SDL_GetTicks()/100;

	while((SDL_GetTicks()/100 - timer) <= 10){


	output.print(message);

	SDL_RenderPresent(gamerenderer);

	}





}


void bullet_update(std::vector<Bullet*> & list){

	std::vector<Bullet*>::iterator z = list.begin();

	for(unsigned int i = 0; i < list.size();i++){

		if (list[i]->get_hitbox().x <= 0 || (list[i]->get_hitbox().x + list[i]->get_hitbox().w) >= SCREEN_WIDTH){

			Bullet* temp_bullet = list[i];

			list.erase(z);

			delete temp_bullet;

		}else if(list[i]->get_hitbox().y <= 0 || (list[i]->get_hitbox().y + list[i]->get_hitbox().h) >= SCREEN_HEIGHT){
			Bullet* temp_bullet = list[i];
			list.erase(z);
			delete temp_bullet;

		} else {

		list[i]->update();
		list[i]->draw();

		}

		z++;
	}

}

void enemy_update(std::vector<Enemy*> & enemylist, std::vector<Bullet*> & bulletlist, std::vector<Bullet*> & bulletlist_out , Player player){

	//create iterator for bullets
	std::vector<Enemy*>::iterator z = enemylist.begin();

	for(unsigned int i = 0; i < enemylist.size();i++){

		if (enemylist[i]->get_hitbox().x <= 0 || (enemylist[i]->get_hitbox().x + enemylist[i]->get_hitbox().w) >= SCREEN_WIDTH){

			enemylist.erase(z);
			std::cout << "erased enemy \n" << std::endl;

		}else if(enemylist[i]->get_hitbox().y <= 0 || (enemylist[i]->get_hitbox().y + enemylist[i]->get_hitbox().h) >= SCREEN_HEIGHT){

			enemylist.erase(z);
			std::cout << "erased enemy \n" << std::endl;

		}

		z++;
	}
	z = enemylist.begin();

	for(unsigned int i = 0; i < enemylist.size();i++){
		std::vector<Bullet*>::iterator b = bulletlist.begin();

			for(unsigned int x = 0; x < bulletlist.size(); x++){

				//yeah i used a break but hear me out this is pretty straightforward
				if(enemylist[i]->check_col( *bulletlist[x]) ) {

					int c_hp = enemylist[i] -> get_c_hp();
					enemylist[i]->set_c_hp(c_hp - player.get_damage());

					Bullet* temp_bullet = bulletlist[x];

					delete temp_bullet;

					bulletlist.erase(b);


					if(enemylist[i]->get_c_hp() <= 0)enemylist.erase(z);

					break;
				}
				b++;

			}

		z++;
	}


	for(unsigned int i = 0; i < enemylist.size(); i++) enemylist[i]->update(&bulletlist_out);
	for(unsigned int i = 0; i < enemylist.size(); i++) enemylist[i]->draw();




}
SDL_Texture* loadtext(char* path, SDL_Renderer* renderer) {

	SDL_Texture* temp;

	SDL_Surface* surface = IMG_Load(path);

	SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0, 0xFF, 0xFF ) );

	temp = SDL_CreateTextureFromSurface( renderer, surface );

	SDL_FreeSurface( surface );

	return temp;
}


void add_enemy(int diff, std::vector<Enemy*>& enemy_list, SDL_Renderer* renderer, SDL_Texture* enemy_texture,SDL_Texture* pillar_texture, SDL_Texture* bullet_texture ,Mix_Chunk* shootsound){

	Enemy * temp;
	for(int i =0; i < diff ; i++){


		int x = rand() % SCREEN_WIDTH;
		int y =rand() % SCREEN_HEIGHT;
		int enemy_roll = rand() % 2;

		switch(enemy_roll) {
		case 0:
			temp = new Enemy(x,y,SCREEN_WIDTH/12,SCREEN_HEIGHT/12,3,enemy_texture,bullet_texture,shootsound,renderer);
			enemy_list.push_back(temp);
			break;

		case 1:
			temp = new DeathPillar(x,y,SCREEN_WIDTH/12,SCREEN_HEIGHT/12,3,pillar_texture,bullet_texture,shootsound,renderer);
			enemy_list.push_back(temp);
			break;

		default:
			break;

		}


	}



}


int main(){
	int diff = 5;
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
	IMG_Init(IMG_INIT_PNG);
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
	srand(time(NULL));

	Mix_Chunk* shootsound = Mix_LoadWAV( "Laser_Shoot.wav" );

	SDL_Window* gamewindow = SDL_CreateWindow("Purity",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);


	SDL_Renderer* gamerenderer = SDL_CreateRenderer(gamewindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

	const Uint8* state = SDL_GetKeyboardState(NULL);

	SDL_Texture* player = loadtext("walk.png",gamerenderer);
	SDL_Texture* bullet = loadtext("bullet.png",gamerenderer);
	SDL_Texture* enemy = loadtext("enemy.png",gamerenderer);
	SDL_Texture* background =loadtext("base.png",gamerenderer);
	SDL_Texture* messagescreen = loadtext("message_back.png", gamerenderer);
	SDL_Texture* player_head = loadtext("spritesheet.png", gamerenderer);
	SDL_Texture* pillar = loadtext("mpanim.png",gamerenderer);


	TTF_Font* font  = TTF_OpenFont("Roboto-Regular.ttf",40);

	Textbox textthing(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,messagescreen,gamerenderer, font );

	Textbox scorebox(0,0,SCREEN_WIDTH/14,SCREEN_HEIGHT/14,messagescreen,gamerenderer, font );
	scorebox.setback(true);

	Textbox damagebox(0,0,SCREEN_WIDTH/14,SCREEN_HEIGHT/14,messagescreen,gamerenderer, font );
	damagebox.setback(true);


	Player you( SCREEN_WIDTH/10, SCREEN_HEIGHT/10,SCREEN_WIDTH/10, SCREEN_HEIGHT/10, 3, player, bullet,player_head,shootsound,  gamerenderer);

	std::vector<Bullet*> player_bullets;
	std::vector<Bullet*> enemy_bullets;
	std::vector<Enemy*> enemies;
	std::vector<Textbox*> damageboxes;

	Static backgr(0,0,SCREEN_WIDTH,SCREEN_HEIGHT, gamerenderer, background);

	add_enemy(diff,enemies, gamerenderer, enemy,pillar, bullet, shootsound);

	bool quit = false;

	while(quit == false){

		SDL_Event e;

		//While application is running
		while( !quit )
		{

			while( SDL_PollEvent( &e ) != 0 )
			{
				SDL_PumpEvents();

				//User requests quit
				if( e.type == SDL_QUIT )
				{
					quit = true;

				}

			}



		if(enemies.size() <= 0){

			diff += 1;

			add_enemy(diff,enemies, gamerenderer, enemy,pillar, bullet, shootsound);


		}

		for(int i = 0; i < enemy_bullets.size(); i++ ){

			if(you.check_col(*enemy_bullets[i])){




				message(textthing,"                         YOU LOSE" , gamerenderer);
				quit = true;
				break;
			}

		}

		SDL_RenderClear(gamerenderer);

		backgr.draw();

		you.update(&player_bullets, state);

		enemy_update(enemies, player_bullets, enemy_bullets, you);

		bullet_update(enemy_bullets);
		bullet_update(player_bullets);

		SDL_PumpEvents();

		SDL_RenderPresent(gamerenderer);
	}

}

}
