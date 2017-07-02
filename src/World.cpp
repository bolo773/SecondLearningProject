/*
 * World.cpp
 *
 *  Created on: May 26, 2017
 *      Author: bolo
 */
#include "World.hpp"
#include <fstream>


//load texture
SDL_Texture* loadtext(char*, SDL_Renderer* );


SDL_Texture* loadtext(char* path, SDL_Renderer* renderer){

		SDL_Texture* temp = NULL;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load( path);

		if (loadedSurface == NULL){

			std::cout << "failed to load image " << path << std::endl;
			exit(0);

		}

		//color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
		temp = SDL_CreateTextureFromSurface( renderer, loadedSurface );

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );

		return temp;
}

void World::menu(){

	bool quit = false;

	Textbox menu_message(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,SCREEN_WIDTH/2,SCREEN_HEIGHT/2,textures[7],game_renderer,font);

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

			} else {

				SDL_RenderSetViewport(game_renderer,&full_viewport);
				SDL_RenderCopy(game_renderer,textures[7],NULL,NULL);
				menu_message.print("Press Space To Start");
				SDL_RenderPresent(game_renderer);
				if (state[SDL_SCANCODE_SPACE]){

					gameloop();
					quit = true;

				}

			}

		}

	}

}



void World::add_enemy(){

	Enemy * temp;
	for(int i =0; i < diff ; i++){

		int x = rand() % SCREEN_WIDTH;
		int y =rand() % SCREEN_HEIGHT;
		int enemy_roll = rand() % 2;

		switch(enemy_roll) {

		case 0:
			temp = new Twitchy(x,y,SCREEN_WIDTH/12,SCREEN_HEIGHT/12,3, textures[10],textures[5],shootsound,sfx[1],game_renderer);
			enemies.push_back(temp);
			break;

		case 1:
			temp = new DeathPillar(x,y,SCREEN_WIDTH/12,SCREEN_HEIGHT/12,3,textures[2],textures[5],shootsound,sfx[1],game_renderer);
			enemies.push_back(temp);
			break;

		default:
			break;

		}

	}

}


//bullet creator
void bulletgen(std::vector<Bullet*> &list, int timer, SDL_Renderer* renderer,SDL_Texture * texture ){

	//every 20 miliseconds draw create a new bullet
	if(timer % 20 == 2) {

	Bullet* tempRect = new Bullet(SCREEN_WIDTH/2, rand()%SCREEN_HEIGHT, 30, 30, rand()%4+1, (rand()%360), texture,renderer);

	//add bullet to list of bullets
	list.push_back(tempRect);

	}

}

//this updates the list of bullets
void World::bullet_update(std::vector<Bullet*> & list){

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

void World::enemy_update(){

	//create iterator for bullets
	std::vector<Enemy*>::iterator z = enemies.begin();

	for(unsigned int i = 0; i < enemies.size();i++){

		if (enemies[i]->get_hitbox().x <= 0 || (enemies[i]->get_hitbox().x + enemies[i]->get_hitbox().w) >= SCREEN_WIDTH){

			enemies.erase(z);
			std::cout << "erased enemy \n" << std::endl;

		}else if(enemies[i]->get_hitbox().y <= 0 || (enemies[i]->get_hitbox().y + enemies[i]->get_hitbox().h) >= SCREEN_HEIGHT){

			enemies.erase(z);
			std::cout << "erased enemy \n" << std::endl;

		}

		z++;
	}
	z = enemies.begin();

	for(unsigned int i = 0; i < enemies.size();i++){
		std::vector<Bullet*>::iterator b = player_bullets.begin();

			for(unsigned int x = 0; x < player_bullets.size(); x++){

				//yeah i used a break but hear me out this is pretty straightforward
				if(enemies[i]->check_col( *player_bullets[x]) ) {

					int c_hp = enemies[i] -> get_c_hp();
					enemies[i]->set_c_hp(c_hp - player.get_damage());
					Bullet* temp_bullet = player_bullets[x];
					delete temp_bullet;
					player_bullets.erase(b);

					if(enemies[i]->get_c_hp() <= 0){
						enemies.erase(z);
						Mix_PlayChannel( -1, sfx[1], 0 );
					}

					break;
				}

				b++;

			}

		z++;

	}

	for(unsigned int i = 0; i < enemies.size(); i++) enemies[i]->update(&enemy_bullets);
	for(unsigned int i = 0; i < enemies.size(); i++) enemies[i]->draw();

}


World::World()
: timer(0), score(0),diff(0), HUD_viewport({0,SCREEN_HEIGHT-40,SCREEN_WIDTH,40}),
 game_viewport({0,0,SCREEN_WIDTH,SCREEN_HEIGHT - 40}), full_viewport({0,0,SCREEN_WIDTH,SCREEN_HEIGHT}){

	//Create window
	game_window = SDL_CreateWindow( "Purity", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	//Create renderer for window
	game_renderer = SDL_CreateRenderer( game_window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC );

	std::ifstream resources("resources.txt");
	std::string resourceelement;

	while (!resources.eof()){

		getline(resources,resourceelement);
		std::cout << "loaded: " <<  resourceelement.c_str() << std::endl;
		char carray[40];
		strcpy(carray,resourceelement.c_str());
		SDL_Texture* temp = loadtext(carray,game_renderer);
		textures.push_back(temp);

	}

	Background temp_background(game_renderer,textures[3]);
	background = temp_background;

	font = TTF_OpenFont("Roboto-Regular.ttf",20);

	shootsound = Mix_LoadWAV( "Laser_Shoot.wav" );
	sfx.push_back(Mix_LoadWAV("Levelup.wav"));
	sfx.push_back(Mix_LoadWAV("deathsound.wav"));
	sfx.push_back(Mix_LoadWAV("Explosion.wav"));


	Textbox textbox_temp( 0,0,SCREEN_WIDTH,SCREEN_HEIGHT,textures[7], game_renderer, font );
	endgame_message = textbox_temp;

	//textbox
	dialoguebox = new Textbox(0,SCREEN_HEIGHT-SCREEN_HEIGHT/4,SCREEN_WIDTH,SCREEN_HEIGHT/4,textures[3],game_renderer,font);

	player_hp = new Textbox(0,0,40,40,textures[9],game_renderer,font);
	player_damage = new Textbox(80,0,40,40,textures[9],game_renderer,font);

	Player temp(SCREEN_WIDTH/8,SCREEN_HEIGHT/8,80,80,6,textures[1],textures[5],textures[0],sfx[2],sfx[1],game_renderer);
	player = temp;
	state = SDL_GetKeyboardState(NULL);

	resources.close();

}


void World::gameloop(){

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
				levelup();
				add_enemy();
				Powerup* powerup_temp = new DamageUp(rand()%SCREEN_WIDTH,rand()%SCREEN_HEIGHT,SCREEN_WIDTH/100,SCREEN_HEIGHT/100,3,textures[6],game_renderer);
				powerups.push_back(powerup_temp);
			}

			for(int i = 0; i < enemy_bullets.size(); i++ ){

				if(player.check_col(*enemy_bullets[i])){
					SDL_RenderSetViewport(game_renderer,&full_viewport);
					message(endgame_message,"X" , game_renderer);
					quit = true;
					break;

				}

			}

			std::vector<Powerup*>::iterator z;
			z = powerups.begin();
			for(int i = 0; i < powerups.size(); i++ ){



						if(player.check_col(*powerups[i])){

							powerups[i]->activate(&player);

							Powerup* temp = powerups[i];

							powerups.erase(z);

							delete temp;

							break;
						}

						z++;

					}

			SDL_RenderClear(game_renderer);
			SDL_RenderSetViewport(game_renderer,&game_viewport);

			background.draw();
			player.update(&player_bullets, state);
			enemy_update();
			bullet_update(enemy_bullets);
			bullet_update(player_bullets);
			for(unsigned int i = 0; i< powerups.size();i++) powerups[i]->draw();


			SDL_RenderSetViewport(game_renderer,&HUD_viewport);

			SDL_RenderCopy(game_renderer,textures[8],NULL,NULL);


			std::string val = std::to_string(player.get_c_hp());

			player_hp-> print(val.c_str());

			val = std::to_string(player.get_damage());

			player_damage ->print(val.c_str());

			SDL_PumpEvents();
			SDL_RenderPresent(game_renderer);

		}

	}

}



void World::quit(){

	//Destroy window
	SDL_DestroyRenderer( game_renderer );
	SDL_DestroyWindow( game_window );

	//close font
	 TTF_CloseFont(font);

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

}


void World::message( Textbox & output, char* message , SDL_Renderer* gamerenderer){

	SDL_RenderClear(gamerenderer);

	Uint32 timer = SDL_GetTicks()/100;

	while((SDL_GetTicks()/100 - timer) <= 10){

	output.print(message);
	SDL_RenderPresent(gamerenderer);

	}
}

void World::levelup(){
	bool quit = false;

		Textbox menu_message(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,SCREEN_WIDTH/2,SCREEN_HEIGHT/2,textures[7],game_renderer,font);

		Uint32 start_time = SDL_GetTicks()/100;
		//While application is running
		while( !quit )
		{
			SDL_PumpEvents();

			SDL_RenderSetViewport(game_renderer,&full_viewport);
			SDL_RenderCopy(game_renderer,textures[7],NULL,NULL);
			menu_message.print("LEVEL UP");
			Mix_PlayChannel( -1, sfx[0], 0 );
			SDL_RenderPresent(game_renderer);
			if (SDL_GetTicks()/100 - start_time >= 10){

			quit = true;

			}

		}

}


int World::get_score(){

	return score;
}

World::~World(){}

