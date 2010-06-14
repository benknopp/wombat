/*!
 * \file AbstractMessageWriter.h
 * \brief AbstractMessageWriter defines a base class for all MessageWriters,
 * wich could be used with Logger.
 *
 * \author Benjamin Knopp  <bknopp@uni-koblenz.de>
 * \date 2007-10-27
 */
#ifndef ABSTRACTMESSAGEWRITER_H_
#define ABSTRACTMESSAGEWRITER_H_

#include <string>

namespace wombat {
enum MessageType {
	CriticalError = 1,
	UncriticalError = 2,
	StatusMessage = 3,
	VerboseMessage = 4
};

/**
 * \brief Prototype for MessageWriters. Every MessageWriter must be derieved from this class
 */
class AbstractMessageWriter {
public:
	AbstractMessageWriter();
	virtual ~AbstractMessageWriter();

	/**
	 * write message to log destinations.
	 * \param _message the message
	 * \param _messageType the message type (critical, verbose) etc.
	 */
	virtual void writeMessage(const std::string &_message,
			MessageType _messageType = StatusMessage) = 0;

	/**
	 * use this message writer only for messages, with a log level lower than
	 * _maxLogLevel
	 */
	void setMaxLogLevel(MessageType _maxLogLevel) {
		mMaxLogLevel = _maxLogLevel;
	}
	;
protected:
	int mMaxLogLevel;

};
}
;

#endif /*ABSTRACTMESSAGEWRITER_H_*/
