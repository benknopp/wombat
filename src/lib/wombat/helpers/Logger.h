/*!
 * \file Logger.h
 * \brief defines a logger
 *
 * \author Benjamin Knopp  <bknopp@uni-koblenz.de>
 * \date 2007-10-27
 */
#ifndef LOGGER_H_
#define LOGGER_H_

/***********************************************************
 *  					INCLUDES
 **********************************************************/
#include <string>
#include <vector>

#include "messaging/AbstractMessageWriter.h"

namespace wombat {

typedef std::vector<wombat::AbstractMessageWriter*> MessageWriterVec;

/**
 * \brief The global Logger (SIGNLETON).
 *
 * this logger recieves all system messages
 */
class Logger {
public:
	static Logger* getInstanceOf();

	virtual void writeLogMessage(const std::string &_logMessage, MessageType _mt =
			StatusMessage);

	static void uncriticalErrorMessage(const std::string &_logMessage);
	static void criticalErrorMessage(const std::string &_logMessage);
	static void statusMessage(const std::string &_logMessage);
	static void verboseMessage(const std::string &_logMessage);

	virtual void setMessageWriter(AbstractMessageWriter *_MessageWriter);
	virtual void addMessageWriter(AbstractMessageWriter *_MessageWriter);

protected:
	Logger();
	virtual ~Logger();

	static Logger *mInstance;

	MessageWriterVec mMessageWriterVec;
};

}
#endif /*LOGGER_H_*/
