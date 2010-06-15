#ifndef MYPETPROJECT_H
#define MYPETPROJECT_H

#include<QObject>
#include<QMap>
#include<QMultiMap>
#include<QString>
#include<QVariant>
#include<QtXml>
#include <QPair>

#include <wombat/body.h>

namespace wombat
{
	/*!
	 * wombat workspace project description
	 */
	class QWombatProject : public QObject
	{
		Q_OBJECT
	public:
		enum PROJECT_STATE {projectClosed = 0, projectOpened = 1,
			projectModified = 2};

		QWombatProject();

		bool saveToFile(const QString &_filename);
		bool loadFromFile(const QString &_filename);

		void close();

		QString filename() const;
		void setFilename(const QString &_filename);
		bool modified() const{return mIsModified;}

		QMultiMap<QString, QVariant> valueMap;
	protected:
		QDomDocument mDomDocument;
		QDomElement mRootElement;

		QString mFileName;
		bool mIsModified;
	};


}



#endif // MYPETPROJECT_H
