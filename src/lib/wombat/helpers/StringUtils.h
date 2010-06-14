/*!
 * \file StringUtils.h
 * \brief provides some algorithms for handling strings
 *
 * \author Benjamin Knopp  <bknopp@uni-koblenz.de>
 * \date 2007-10-27
 */
#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_

#include <string>
#include <vector>
#include <map>
#include <algorithm>

namespace wombat
{

typedef std::map<std::string, std::string> StringMap;
typedef StringMap::iterator StringMapIt;
typedef std::vector<std::string> StringVec;
typedef std::pair<std::string, std::string> StringPair;


/*!
 *  seperates a string into a vector of substrings, seperators are all
 *  characters in _seperators
 */
std::vector<std::string> splitString(const std::string &_orginal,
		const std::string &_seperators);

/*!
 * convert a number into a std::string
 */
std::string toString(const long _value);

/*!
 * convert a floating point number to std::string
 */
std::string fToString(const double _value);

/*!
 *  convert a string to lower case
 */
std::string toLower(const std::string &_orginal);

/*!
 * strip directory name from a given absolute path
 */
std::string dirName(const std::string &_orginal);

/*!
 * strip filename from a given absolut path
 */
std::string fileName(const std::string &_orginal);

/*!
 * strip filename without extension from a given filename
 */
std::string fileBaseName(const std::string &_orginal);



}

#endif /* STRINGUTILS_H_ */
