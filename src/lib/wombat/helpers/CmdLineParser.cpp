/*
 * CmdLineParser.cpp
 *
 *  Created on: 19.05.2009
 *      Author: bknopp
 */

#include "CmdLineParser.h"
#include <stdio.h>

namespace wombat
{

QString removeDashes(const QString &_string)
{
   QString result = _string;

   while(result.at(0) == '-')
   {
      result = result.right(result.length()-1);

   }

   return result;
}



CmdLineParser::CmdLineParser()
{
}


CmdLineParser::~CmdLineParser()
{
}


CmdLineParser::CmdLineParser(int &_argc, char **_argv)
{
   init(_argc, _argv);
}


void CmdLineParser::init(int &_argc, char **_argv)
{
   mIsCaseSensitive = false;
   mValueMap.clear();

   //skip first -> appname
   for(int i=1; i < _argc; i++)
   {
      QString argv(_argv[i]);
      QString key, value;

      if(!argv.contains("="))
      {
         //first case: atomic item, eg: --verbose
         key = removeDashes(argv);
      } else
      {
         //second case: key value --query==".."
         int pos = argv.indexOf("=");
         QString left = argv.left(pos);
         QString right = argv.right(argv.length() -pos - 1);
         key=removeDashes(left);
         value=right;
      }

      if(!mIsCaseSensitive) key = key.toLower();

      //printf("key: %s value:%s\n", key.toStdString().c_str(), value.toStdString().c_str());
      mValueMap.insert(key, value);
   }


}


unsigned CmdLineParser::argumentsCount() const
{
   return mValueMap.size();
}


QVariant CmdLineParser::argument(const QString &_name, const QVariant _default)
{
   QString key = _name;
   if(!mIsCaseSensitive) key = key.toLower();

   if(!mValueMap.contains(key))
   {
      return _default;
   } else
   {
      QVariant result = mValueMap.value(key);
      if(result.isNull() | (!result.isValid())) result = _default;
      return result;
   }

}


bool CmdLineParser::hasArgument(const QString &_name) const
{
   QString key = _name;
   if(!mIsCaseSensitive) key = key.toLower();

   return mValueMap.contains(key);
}


QStringList CmdLineParser::arguments() const
{
   return mValueMap.keys();
}


void CmdLineParser::printDebugMap() const
{
   QString key, value;

   int count =0;


   printf("     %-20s %-40s \n","key", "value");
   for(int i=0; i<80; i++){printf("=");}; printf("\n");

   for(QMap<QString, QVariant>::const_iterator it = mValueMap.begin(); it!=mValueMap.end(); it++)
   {
      key =it.key();

      if(it.value().isNull())
      {
         value = "[NULL]";
      } else
      {
         value = it.value().toString();
      }

      printf("%3i  %-20s %-40s \n",++count, key.toStdString().c_str(), value.toStdString().c_str());
   }

   for(int i=0; i<80; i++){printf("=");}; printf("\n");
}

}

