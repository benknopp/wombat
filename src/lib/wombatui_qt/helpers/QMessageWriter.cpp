/*
 * QMessageWriter.cpp
 *
 *  Created on: 07.11.2009
 *      Author: bknopp
 */

#include "QMessageWriter.h"
#include <QtGui>

namespace wombat {

QMessageWriter::QMessageWriter( QWidget *_parent )
	: QListWidget( _parent ), AbstractMessageWriter(), mPrintTimestamps( true )
{
        mIconCritical = new QIcon(":/icons/24/dialog-error.png");
        mIconUncritical = new QIcon(":/icons/24/dialog-warning.png");
        mIconStatus = new QIcon(":/icons/24/dialog-information.png");
        mIconVerbose = new QIcon(":/icons/24/dialog-information.png");

	setSelectionMode(QAbstractItemView::SingleSelection);
	setMinimumSize(320, 240);
}

QMessageWriter::~QMessageWriter()
{
}


void QMessageWriter::writeMessage( const std::string &_message, MessageType _messageType )
{
	QIcon *theIcon = 0;
	switch (_messageType)
	{
		case CriticalError:
			theIcon = mIconCritical;
			break;
		case UncriticalError:
			theIcon = mIconUncritical;
			break;
		case StatusMessage:
			theIcon = mIconStatus;
			break;
		case VerboseMessage:
			theIcon = mIconVerbose;
			break;
		default:
			break;
	}

	std::string message;
	if( mPrintTimestamps ){
		 message = QTime::currentTime().toString().toStdString() + " : " +  _message;
	} else
	{
		message = _message;
	}

	QListWidgetItem *item = new QListWidgetItem( *theIcon, QString::fromStdString(message));
	addItem( item );

	setCurrentRow(count());
}

}
