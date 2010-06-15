/*
 * QMessageWriter.h
 *
 *  Created on: 07.11.2009
 *      Author: bknopp
 */

#ifndef QMESSAGEWRITER_H_
#define QMESSAGEWRITER_H_

#include <wombat/helpers.h>
#include <QListWidget>

namespace wombat {

/*!
 * \brief qt message writer backend
 */
class QMessageWriter : public QListWidget, public AbstractMessageWriter
{
    Q_OBJECT
public:
	QMessageWriter( QWidget *_parent = 0 );
	virtual ~QMessageWriter();

	virtual void writeMessage( const std::string &_message, MessageType _messageType = StatusMessage );
protected:
	QIcon *mIconCritical, *mIconUncritical, *mIconStatus, *mIconVerbose;
	bool mPrintTimestamps;
};

}

#endif /* QMESSAGEWRITER_H_ */
