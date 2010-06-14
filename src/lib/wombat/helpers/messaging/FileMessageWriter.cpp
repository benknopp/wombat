#include "FileMessageWriter.h"
#include <sstream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include "../debug.h"

using namespace std;

namespace wombat {

FileMessageWriter::FileMessageWriter(const std::string &_filename) {
	mOfstream = new ofstream();
	mOfstream->open(_filename.c_str());
}

FileMessageWriter::~FileMessageWriter() {
	mOfstream->close();
	delete mOfstream;
}

void FileMessageWriter::writeMessage(const std::string &_message,
		MessageType _messageType) {
	string logMessage;
	switch (_messageType) {
	case CriticalError:
		logMessage = "CriticalError       ";
		break;
	case UncriticalError:
		logMessage = "UncriticalError    ";
		break;
	case StatusMessage:
		logMessage = "StatusMessage       ";
		break;
	case VerboseMessage:
		logMessage = "VerboseMessage      ";
		break;
	}
	logMessage += " :: " + _message + "\n";

	mOfstream->write(logMessage.c_str(), logMessage.size());
	mOfstream->flush();
}

}
