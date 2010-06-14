/*!
 * \file StandardMessageWriter
 * \brief implements a MessageWriter forwarding all Messages to std::out.
 *
 * \author Benjamin Knopp  <bknopp@uni-koblenz.de>
 * \date 2007-10-27
 */
#ifndef STANDARDMESSAGEWRITER_H_
#define STANDARDMESSAGEWRITER_H_

#include "AbstractMessageWriter.h"

namespace wombat
{

	/**
	 * \brief a simple std::out message writer.
	 *
	 * this message writer prints all messages to the standard output
	*/
	class StandardMessageWriter: public AbstractMessageWriter
	{
	public:
		StandardMessageWriter();
		virtual ~StandardMessageWriter();

		virtual void writeMessage( const std::string &_message, MessageType _messageType = StatusMessage );

	};

	}
#endif /*STANDARDMESSAGEWRITER_H_*/
