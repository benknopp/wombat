/*
 * FilterSpecialization.hpp
 *
 *  Created on: 11.03.2010
 *      Author: bknopp
 */

#ifndef FILTERSPECIALIZATION_HPP_
#define FILTERSPECIALIZATION_HPP_

#include "diffusion/AlphaDiffusionStrategy.hpp"
#include <wombat/body.h>

namespace wombat
{

//template<>
//void AlphaDiffusionStrategy<wombat::BodyStateVector>::diffuse(const ParticleList &_src, ParticleList &_dest)
//{
////	_dest.resize(_src.size());
////
////	const unsigned nDofs = _src[0].state.size();
////	unsigned index = 0;
////	VectorXd noise(nDofs);
////
////	// iterate over all source particles
////	for(ParticleListConstIterator it = _src.begin(); it != _src.end(); it++)
////	{
////		for(unsigned i=0; i < nDofs; i++)
////		{
////			noise(i) = this->mNormDistGenerator() *  mDiffusion[i];
////		}
//}
//
//
//template<>
//void AlphaDiffusionStrategy<wombat::BodyStateVector>::update()
//{
////	std::vector<double> alphas = this->mObservedFilter->annealingRates();
////	mDiffusion = mInitialDiffusion;
////
////	for(std::vector<double>::iterator it = alphas.begin(); it != alphas.end(); it++)
////	{
////		mDiffusion *= (*it);
////	}
//}

}


#endif /* FILTERSPECIALIZATION_HPP_ */
