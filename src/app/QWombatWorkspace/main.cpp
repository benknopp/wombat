/*
 * main.cpp
 *
 *  Created on: 17.11.2009
 *      Author: bknopp
 */

#include<QApplication>
#include<wombat/helpers.h>
#include<wombatui_qt/wombatui_qt.h>


#include"MainWindow.h"

using namespace std;
using namespace wombat;


int main(int argc, char **argv)
{
    QGlobalState::instance()->cmdLineParser()->init(argc, argv);

    CmdLineParser parser(argc, argv);
    if (parser.hasArgument("logfile"))
    {
    	QString filename = parser.argument("logfile", "logmessages.txt").toString();
    	FileMessageWriter *fmw = new FileMessageWriter(filename.toStdString());
    	Logger::getInstanceOf()->addMessageWriter(fmw);
    }

    QApplication app(argc, argv);
    app.setApplicationName("wombat");
    app.setOrganizationName("HuMAn");

    MainWindow mw;
    mw.show();
    app.exec();

}
