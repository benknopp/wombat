/*
 * MatlabAdapter.h
 *
 *  Created on: 06.03.2010
 *      Author: bknopp@uni-koblenz.de
 */
#ifndef MATLABBODYCONFIGURATOR_H
#define MATLABBODYCONFIGURATOR_H


#include "../AbstractBodyConfigurator.h"
#include <QString>

namespace wombat
{
class MatlabAdapter;


class MatlabBodyConfigurator : public wombat::AbstractBodyConfigurator
{
public:
    MatlabBodyConfigurator(const QString &_directory);
    virtual bool configure(const BodyStateVector &_state, BodyConfiguration &_config);
    virtual bool configure(const std::vector<BodyStateVector> &_states, std::vector<BodyConfiguration> &_configs);

    bool isReady() const{return mIsReady;}
protected:
    void init(const QString &_directory);
    MatlabBodyConfigurator(){};
    MatlabAdapter *mAdapter;
    bool mIsReady;
};


}
#endif // MATLABBODYCONFIGURATOR_H
