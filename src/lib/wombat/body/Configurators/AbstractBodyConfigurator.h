/*
 * AbstractBodyConfigurator.h
 *
 *  Created on: 10.12.2009
 *      Author: bknopp
 */

#ifndef ABSTRACTBODYCONFIGURATOR_H_
#define ABSTRACTBODYCONFIGURATOR_H_

#include "../BodyConfiguration.h"
#include "../BodyStateVector.h"
#include "../Body.h"
#include "../BodyNodes.h"
#include "../BodyNodeTree.h"

namespace wombat {


/*!
  * \brief this class mainly provides an interface to generate body-configurations from state-vectors
  */
class AbstractBodyConfigurator {
public:
    AbstractBodyConfigurator();
    virtual ~AbstractBodyConfigurator();

    virtual bool configure(const BodyStateVector &_state, BodyConfiguration &_config) = 0;
    virtual bool configure(const std::vector<BodyStateVector> &_states, std::vector<BodyConfiguration> &_configs) = 0;

    /*!
      * \brief create a body which is able to interpret configurations generated with this configurator
      */
    Body* createBody(int _primitiveType);

    /*!
     * get a pointer to the internal tree
     */
    const BodyNodeTree* getBodyNodeTree() const;

    /*!
     * create a new statevector
     */
    BodyStateVector* newStateVector() const;
    BodyStateVector stateVector() const;

    BodyConfiguration configuration() const;

    bool hasValidStateVector() const{return mBodyStateVector != 0;}

    /*!
     * returns true iff body is ready to be used
     */
    virtual bool isReady() const = 0;

    /*!
     * \brief scale all sizes of the object according to the given factor
     */
    void setBodyScaleFactor(double _scaleFactor);

    /*!
     * \brief returns the currently used scale factor
     */
    double bodyScaleFactor() const;
protected:
    /*!
     * initially create a statevector with correct ranges, which will be duplicated at runtime
     */
    void createStateVectorAndConfiguration();

    BodyNodeTree *mBodyNodeTree;
    BodyStateVector* mBodyStateVector;
    BodyConfiguration *mBodyConfiguration;
};

}

#endif /* ABSTRACTBODYCONFIGURATOR_H_ */
