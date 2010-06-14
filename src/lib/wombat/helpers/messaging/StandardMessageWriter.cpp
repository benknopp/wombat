#include "StandardMessageWriter.h"
#include <string>
#include <stdio.h>

using namespace std;

namespace wombat {

StandardMessageWriter::StandardMessageWriter() {
}

StandardMessageWriter::~StandardMessageWriter() {
}

void StandardMessageWriter::writeMessage(const std::string &_message,
		MessageType _messageType) {
	string messageType;

	switch (_messageType) {
	case CriticalError:
		messageType = "CriticalError   ";
		break;
	case UncriticalError:
		messageType = "UncriticalError ";
		break;
	case VerboseMessage:
		messageType = "VerboseMessage  ";
		break;
	default:
	case StatusMessage:
		messageType = "StatusMessage   ";
		break;
	}

	printf("%s: %s  \n", messageType.c_str(), _message.c_str());
}

}
