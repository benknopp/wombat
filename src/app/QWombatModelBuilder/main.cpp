/*
 * main.cpp
 *
 *  Created on: 17.11.2009
 *      Author: bknopp
 */

#include <wombat/wombat.h>
#include "BuilderMainWindow.h"

using namespace wombat;
using namespace std;



int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	BuilderMainWindow mw;
	mw.show();
	return app.exec();
}

