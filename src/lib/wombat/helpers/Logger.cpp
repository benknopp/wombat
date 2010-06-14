#include "Logger.h"

using namespace std;

namespace wombat {

Logger* Logger::mInstance = 0;

Logger* Logger::getInstanceOf() {
	if (mInstance == 0) {
		mInstance = new Logger();
	}
	return mInstance;
}

void Logger::writeLogMessage(const std::string &_logMessage, MessageType _mt) {
	for (MessageWriterVec::iterator it = mMessageWriterVec.begin(); it
			!= mMessageWriterVec.end(); it++) {
		(*it)->writeMessage(_logMessage, _mt);
	}
}

void Logger::setMessageWriter(AbstractMessageWriter *_messageWriter) {
	mMessageWriterVec.clear();
	mMessageWriterVec.push_back(_messageWriter);
}

void Logger::addMessageWriter(AbstractMessageWriter *_messageWriter) {
	mMessageWriterVec.push_back(_messageWriter);
}

void Logger::uncriticalErrorMessage(const std::string &_logMessage) {
	Logger::getInstanceOf()->writeLogMessage(_logMessage, UncriticalError);
}

void Logger::criticalErrorMessage(const std::string &_logMessage) {
	Logger::getInstanceOf()->writeLogMessage(_logMessage, CriticalError);
}

void Logger::statusMessage(const std::string &_logMessage) {
	Logger::getInstanceOf()->writeLogMessage(_logMessage, StatusMessage);
}

void Logger::verboseMessage(const std::string &_logMessage) {
	Logger::getInstanceOf()->writeLogMessage(_logMessage, VerboseMessage);
}

Logger::Logger() {
}

Logger::~Logger() {
	//if ( mInstance ) delete mInstance;
}

} // end namespace
