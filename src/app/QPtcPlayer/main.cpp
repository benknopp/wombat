/*
 * main.cpp
 *
 *  Created on: 17.11.2009
 *      Author: bknopp
 */

#include<QApplication>
#include"widgets/PtcPlayer.h"
#include<wombat/helpers.h>

using namespace std;
using namespace wombat;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    PtcPlayer player;

    CmdLineParser parser(argc, argv);
    if(parser.hasArgument("file"))
    {
        player.setSource(parser.argument("file").toString());
    }

    player.show();
    app.exec();

}
