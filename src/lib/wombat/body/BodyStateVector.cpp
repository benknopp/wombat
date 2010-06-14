/*
 * BodyStateVector.cpp
 *
 *  Created on: 08.03.2010
 *      Author: bknopp
 */

#include "BodyStateVector.h"
#include <wombat/helpers.h>

namespace wombat
{

BodyStateVector::BodyStateVector() : StateVector<AbstractDouble>()
{

}

BodyStateVector& BodyStateVector::operator=(double _value)
{
	std::vector<AbstractDouble*>::iterator it;
	for(it = mValues.begin(); it != mValues.end(); it++)
	{
		(**it) = _value;
	}

	return *this;
}


BodyStateVector& BodyStateVector::operator=(const BodyStateVector &_source)
{
	mValues.clear();

	for(std::vector<AbstractDouble*>::const_iterator it = _source.mValues.begin();
			it != _source.mValues.end(); it++)
	{
		mValues.push_back((*it)->clone());
	}

	name = _source.name;
	return *this;
}



//BodyStateVector& BodyStateVector::operator=(const StateVector<AbstractDouble> &_source)
//{
//	mValues.clear();
//
//	for(std::vector<AbstractDouble*>::const_iterator it = _source.mValues.begin();
//			it != _source.mValues.end(); it++)
//	{
//		mValues.push_back((*it)->clone());
//	}
//
//	return *this;
//}



std::string toString(const BodyStateVector &_state)
{
	std::string value = _state.name;

	for(unsigned i=0; i < (unsigned) _state.size(); i++)
	{
		value += " ";
		value+= fToString(_state[i]);
	}
	return value;
}

bool readFromString(BodyStateVector &_state, const std::string &_values)
{
	std::vector<std::string> tokens = splitString(_values, " ");

	// there should be state.size +1 tokens ..
	if(tokens.size() != _state.size()+1)
	{
		TRACE("failed. string contains insufficient number of parameters.");
		return false;
	}

	std::string name = (tokens.size()) ? tokens.at(0) : "conversion failed";
	_state.name = name;

	for(unsigned i=1; i < tokens.size(); i++)
	{
		_state[i-1] = atof(tokens[i].c_str());
	}
	return true;
}


}



