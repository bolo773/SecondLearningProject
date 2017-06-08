/*
 * DamageUp.cpp
 *
 *  Created on: Jun 7, 2017
 *      Author: bolo
 */

void DamageUp::activate(Player* player){

	int c_damage = player->get_damage();
	c_damage++;
	player->set_damage(c_damage);


}


