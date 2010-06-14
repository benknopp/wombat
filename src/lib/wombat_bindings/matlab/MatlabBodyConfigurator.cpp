#include "MatlabBodyConfigurator.h"
#include "MatlabAdapter.h"

#include <wombat/helpers.h>

namespace wombat
{

MatlabBodyConfigurator::MatlabBodyConfigurator(const QString &_directory)
    : mIsReady(false)
{
    init(_directory);
}

bool MatlabBodyConfigurator::configure(const BodyStateVector &_state, BodyConfiguration &_config)
{
    bool result = false;
    // check pointers
    if(!mIsReady) return false;

    result = mAdapter->configure(_state, _config);



    return result;
}

bool MatlabBodyConfigurator::configure(const std::vector<BodyStateVector> &_states, std::vector<BodyConfiguration> &_configs)
{
    if(_states.size() == 0) return false;
    bool result = true;
    _configs.resize(_states.size());

    unsigned count = 0;
    for(std::vector<BodyStateVector>::const_iterator it = _states.begin(); it != _states.end(); it++)
    {
        result &= configure(*it, _configs.at(count++));
    }

    return result;
}


void MatlabBodyConfigurator::init(const QString &_directory)
{
    try
    {
        TRACE("creating adapter");
        mAdapter = new MatlabAdapter();
        mAdapter->setWorkingDir(_directory);
        mAdapter->setEngineArgs("");
        mAdapter->init();
        //mModel = &(mAdapter->model);
        mBodyNodeTree = &(mAdapter->tree);

        printBodyNodeTree(*mBodyNodeTree);

        createStateVectorAndConfiguration();
        TRACE("successfully created matlab body configurator.");

    }
    catch(int e)
    {
        TRACE("model creation terminated with status %i", e);
        mIsReady = false;
        return;
    }

    mIsReady = true;

}

}
