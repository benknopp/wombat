/*!
 * \file 	StringSerialization.h
 *
 * \date	Created on: 14.06.2010
 * \author	Author: Benjamin Knopp <benjamin@knopp-online.com>
 */

#ifndef STRINGSERIALIZATION_H_
#define STRINGSERIALIZATION_H_

#include <string>
#include <vector>

namespace wombat
{

/*!
 * create a vector of doubles from a given string, values are seperated by whitespace
 */
std::vector<double> stringToDoubles(const std::string &_values);

/*!
 * create a string from a vector of doubles
 */
std::string doublesToString(std::vector<double> _doubles);


}

#endif /* STRINGSERIALIZATION_H_ */
