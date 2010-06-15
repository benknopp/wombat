#include "QWombatProject.h"
#include <wombat/helpers.h>

using namespace wombat;

namespace wombat
{

QWombatProject::QWombatProject()
    : mIsModified(true)
{
    mRootElement = mDomDocument.createElement("MyPetProject");
    mRootElement.setAttribute("version", "0.1");
    mDomDocument.appendChild(mRootElement);
}


bool QWombatProject::saveToFile(const QString &_filename)
{
    bool success = true;
    const int IndentSize = 4;

    QFile file(_filename);
    file.open(QIODevice::WriteOnly);

    QTextStream out(&file);

    QString msg = "saving project with ";
    msg.append(QString::number(valueMap.size())).append(" entries to: ").append(_filename);
    Logger::verboseMessage(msg.toStdString());


    mRootElement = mDomDocument.createElement("MyPetProject");
    mRootElement.setAttribute("version", "0.1");
    mDomDocument.clear();

    for(QMap<QString, QVariant>::iterator it = valueMap.begin(); it != valueMap.end(); it++)
    {
        QDomElement element = mDomDocument.createElement("property");
        element.setAttribute("name", it.key());
        QVariant value = it.value();
        element.setAttribute("type", value.type());
        element.setAttribute("data", value.toString());
        mRootElement.appendChild(element);
    }
    mDomDocument.appendChild(mRootElement);

    mDomDocument.save(out, IndentSize);
    file.close();

    return success;
}


bool QWombatProject::loadFromFile(const QString &_filename)
{
	TRACE("loading %s", _filename.toStdString().c_str());
    QString errorStr;
    int errorLine, errorColumn;
    QFile file(_filename);

    if (!mDomDocument.setContent(&file, true, &errorStr, &errorLine, &errorColumn))
    {
        Logger::criticalErrorMessage(QString("Parse error at line %i, column %i: %s").arg(
                QString::number(errorLine), QString::number(errorColumn), errorStr).toStdString());
        return false;
    }

    QDomElement root = mDomDocument.documentElement();
    if ((root.tagName() != "MyPetProject") || !(root.hasAttribute("version")) || (root.attribute("version") != "0.1"))
    {
    	TRACE("XML FILE NOT IN MyPetProject-Format. -> %s", root.tagName().toStdString().c_str());
        return false;
    }

    QDomElement child = root.firstChildElement("property");
    while (!child.isNull())
    {
    	QString name = child.attribute("name");
    	QString type = child.attribute("type");
    	QString data = child.attribute("data");

    	QVariant value((QVariant::Type) type.toInt());
    	value = data;
    	valueMap.insert(name, value);

        //parseBodyPart(child);
        child = child.nextSiblingElement("property");
    }

    TRACE("project successfully loaded");
    mFileName = _filename;
    return true;
}


void QWombatProject::close()
{

}


QString QWombatProject::filename() const
{
    return mFileName;
}


void QWombatProject::setFilename(const QString &_filename)
{
    mFileName = _filename;
}



}


