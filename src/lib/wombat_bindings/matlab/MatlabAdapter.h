/*
 * MatlabAdapter.h
 *
 *  Created on: 06.03.2010
 *      Author: bknopp@uni-koblenz.de
 */
#ifndef MATLABADAPTER_H
#define MATLABADAPTER_H

#include <engine.h>
#include <vector>
#include <string>
#include <QString>
#include "../../BodyStateVector.h"
#include "../../BodyConfiguration.h"
#include "../../BodyNodes.h"
#include "../../BodyNodeTree.h"

namespace wombat
{
    /*!
      * \brief adapter communicating with a matlab instance, hosting a mkdtools model
      */
    class MatlabAdapter
    {
    public:
        MatlabAdapter();

        void init();

        void setEngineArgs(const QString &_args){mEngineArgs = _args;}
        QString engineArgs() const{return mEngineArgs;}

        void setWorkingDir(const QString &_dir){mWorkingDir = _dir;}
        QString workingDir() const{return mWorkingDir;}

        //*****************************************************************************************

        bool configure(const BodyStateVector &_state, BodyConfiguration &_configuration);
        bool configure(const std::vector<BodyStateVector> &_state, std::vector<BodyConfiguration> &_configuration);

        BodyNodeTree tree;
    protected:
        void initModel();
        void initSegments();
        void initJoints();
        void initGenCoords();
        void printMap();

        std::string& getModelName(unsigned _index);

        Engine *mEngine;
        QString mEngineArgs, mWorkingDir;
        char *mBuffer;
        int mBufferSize;
        std::vector<std::string> mModelNames;
    };
}



#endif // MATLABADAPTER_H
