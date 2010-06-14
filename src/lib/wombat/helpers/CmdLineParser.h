/*
 * CmdLineParser.h
 *
 *  Created on: 19.05.2009
 *      Author: bknopp
 */

#ifndef CMDLINEPARSER_H_
#define CMDLINEPARSER_H_

#include <QString>
#include <QVariant>
#include <QMap>
#include <QStringList>

namespace wombat {

/**
 * \brief parse (argc, argv) command-line options
 *
 * provides a qt-style interface to them.
 */
class CmdLineParser {
public:
	CmdLineParser();
	CmdLineParser(int &_argc, char **_argv);
	virtual ~CmdLineParser();

	/**
	 * read comand line parameters
	 */
	void init(int &_argc, char **_argv);

	/**
	 * number of processed arguments
	 */
	unsigned argumentsCount() const;

	/**
	 * returns value of argument with name _name
	 * \param _name argument name
	 * \param _default default value, if not found
	 * \return argument value
	 */
	QVariant argument(const QString &_name, const QVariant _default = 0);

	/**
	 * check if argument exists
	 * \param _name name of the argument
	 * \return true if argument exists, false otherwise
	 */
	bool hasArgument(const QString &_name) const;

	/**
	 * returns names of all parsed arguments
	 */
	QStringList arguments() const;

	/**
	 * helper function, which prints all parsed informations to std::out
	 */
	void printDebugMap() const;

protected:
	QMap<QString, QVariant> mValueMap;
	bool mIsCaseSensitive;
};

}

#endif /* CMDLINEPARSER_H_ */
