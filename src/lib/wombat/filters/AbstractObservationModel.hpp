/*
 * AbstractObservationModel.hpp
 *
 *  Created on: 25.02.2010
 *      Author: bknopp
 */

#ifndef ABSTRACTOBSERVATIONMODEL_HPP_
#define ABSTRACTOBSERVATIONMODEL_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Particle.hpp"


namespace wombat
{

template<typename StateType>
class AbstractObservationModel
{
public:
	virtual void meassure(Particle<StateType> *_particle) = 0;
protected:

};


template<typename StateType>
class RandomObservationModel : public AbstractObservationModel<StateType>
{
public:
	RandomObservationModel(){srand ( time(NULL) );}
	void meassure(Particle<StateType> *_particle){_particle->weight = (double)(rand()) / (double)(RAND_MAX);}
protected:

};



}


#endif /* ABSTRACTOBSERVATIONMODEL_HPP_ */
