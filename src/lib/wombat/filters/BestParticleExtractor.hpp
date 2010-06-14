/*
 * BestParticleExtractor.hpp
 *
 *  Created on: 27.04.2010
 *      Author: bknopp
 */

#ifndef BESTPARTICLEEXTRACTOR_HPP_
#define BESTPARTICLEEXTRACTOR_HPP_

#include <algorithm>

namespace wombat
{

template< typename Particle >
class BestParticleExtractor
{
public:
	BestParticleExtractor()
	{

	}

	void operator()(std::vector<Particle> &_pdf, size_t _numSamples, std::vector<Particle> &_sampleDest)
	{
		sort(_pdf.begin(), _pdf.end());

		size_t numSamples = _numSamples;

		// don't draw to much samples
		if(numSamples > _pdf.size()) numSamples = _pdf.size();

		for(unsigned i = _pdf.size() - numSamples; i < _pdf.size(); i++)
		{
			_sampleDest.push_back(_pdf[i]);
			TRACE("adding sample with weight %f", _pdf[i].weight);
		}



	}
};

} // end namespace

#endif /* BESTPARTICLEEXTRACTOR_HPP_ */
