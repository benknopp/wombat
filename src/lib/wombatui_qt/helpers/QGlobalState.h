#ifndef GLOBALSTATE_H
#define GLOBALSTATE_H

#include <QObject>
#include "QWombatProject.h"

namespace wombat
{
    class Logger;
    class CmdLineParser;

    class QGlobalState : public QObject
    {
        Q_OBJECT
    public:
        static QGlobalState* instance();
        Logger* logger() const{return mLogger;}
        CmdLineParser* cmdLineParser() const{return mParser;}

        QWombatProject* currentProject;

        /*!
         * convenience function to access project specific variables
         */
        static QVariant value(const QString _name);
        static QVariant value(const QString _name, const QVariant &_default);
        static void setValue(const QString _name, const QVariant &_value);

    protected:
        QGlobalState();

        Logger* mLogger;
        CmdLineParser *mParser;

        static QGlobalState* mInstance;
    };
}


#endif // GLOBALSTATE_H
