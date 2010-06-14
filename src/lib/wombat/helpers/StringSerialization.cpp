/*!
 * \file 	StringSerialization.cpp
 *
 * \date	Created on: 14.06.2010
 * \author	Author: Benjamin Knopp <benjamin@knopp-online.com>
 */

#include "StringSerialization.h"
#include <algorithm>
#include "StringUtils.h"

namespace wombat
{

    std::vector<double> stringToDoubles(const std::string &_values)
    {
        std::vector<double> results;
        std::vector<std::string> tokens = splitString(_values, " ");
        for(unsigned i=0; i < tokens.size(); i++)
        {
            double value = atof(tokens[i].c_str());
            results.push_back(value);
        }

        return results;
    }


    std::string doublesToString(std::vector<double> _doubles)
    {
        std::string result;
        for(unsigned i=0; i < _doubles.size(); i++)
        {
            if(i>0) result.append(" ");
            result.append(fToString(_doubles[i]));
        }
        return result;
    }

}
