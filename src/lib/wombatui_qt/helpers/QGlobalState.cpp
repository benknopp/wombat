#include "QGlobalState.h"
#include <wombat/helpers.h>

namespace wombat
{
    QGlobalState* QGlobalState::mInstance = 0;

    QGlobalState::QGlobalState()
        : currentProject(0)
    {
        mLogger = Logger::getInstanceOf();
        mParser = new CmdLineParser();

    }


    QGlobalState* QGlobalState::instance()
    {
        if(mInstance == 0)
        {
            mInstance = new QGlobalState();
        }
        return mInstance;
    }


    QVariant QGlobalState::value(const QString _name)
    {
    	QWombatProject* project = mInstance->currentProject;
    	QVariant def = 0;
    	if(project==0) return def;
    	return value(_name, def);
    }


    QVariant QGlobalState::value(const QString _name, const QVariant &_default)
    {
    	QWombatProject* project = mInstance->currentProject;
    	if(project==0) return _default;
    	return project->valueMap.value(_name, _default);
    }


    void QGlobalState::setValue(const QString _name, const QVariant &_value)
    {
    	QWombatProject* project = mInstance->currentProject;
    	if(project==0) return;
    	project->valueMap.replace(_name, _value);
    }



}
