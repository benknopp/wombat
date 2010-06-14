/*!
 * \file FileMessageWriter.h
 * \brief implements a MessageWriter writing all log messages to disk
 *
 * \author Benjamin Knopp  <bknopp@uni-koblenz.de>
 * \date 2007-10-27
 */
#ifndef FILEMESSAGEWRITER_H_
#define FILEMESSAGEWRITER_H_

#include <string>
#include "AbstractMessageWriter.h"

namespace wombat {
/**
 * \brief write  log-messages to file.
 *
 * Add this message writer to the global logger to dump all messages to file
 */
class FileMessageWriter: public AbstractMessageWriter {
public:
	FileMessageWriter(const std::string &_filename);
	virtual ~FileMessageWriter();

	virtual void writeMessage(const std::string &_message,
			MessageType _messageType = StatusMessage);

protected:
	std::string mFilename;
	std::ofstream* mOfstream;
};

}

#endif /*FILEMESSAGEWRITER_H_*/
