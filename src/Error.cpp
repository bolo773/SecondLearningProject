/*
 * Error.cpp
 *
 *  Created on: Jul 22, 2017
 *      Author: bolo
 */


#include "Error.hpp"

Error::Error(std::string msg) : er_msg(msg){}

std::string Error::get_message(){

	return er_msg;

}
