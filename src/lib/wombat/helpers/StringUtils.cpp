#include "StringUtils.h"

#include <sstream>
#include <iostream>
#include "StlAlgorithms.hpp"

using namespace std;

namespace wombat {

vector<string> splitString(const string &_orginal, const string &_seperators) {
	vector<string> elements;
	string::const_iterator endIt, beginIt = _orginal.begin();

	do {
		endIt = find_first_of(beginIt, _orginal.end(), _seperators.begin(),
				_seperators.end());
		if (beginIt != endIt) {
			elements.push_back("");
			copy(beginIt, endIt, back_inserter(elements.back()));
		}
		beginIt = find_first_not_of(endIt, _orginal.end(), _seperators.begin(),
				_seperators.end());

	} while (beginIt != _orginal.end());

	return elements;
}

string toString(const long _value) {
	ostringstream o;
	o << _value;
	return (o.str());
}

string fToString(const double _value) {
	ostringstream o;
	o << _value;
	return (o.str());
}

string toLower(const string &_orginal) {
	string result(_orginal.size(), ' ');

	for (unsigned int i = 0; i < _orginal.size(); i++) {
		result[i] = (tolower(_orginal[i]));
	}

	return result;
}





} // end namespace
