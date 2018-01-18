/*
 * Error.hpp
 *
 *  Created on: Jul 21, 2017
 *      Author: bolo
 */

#ifndef SRC_ERROR_HPP_
#define SRC_ERROR_HPP_
#include <string>

class Error {

	std::string er_msg;

public:
	Error(std::string);
	std::string get_message();

};


#endif /* SRC_ERROR_HPP_ */
