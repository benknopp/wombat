/*
 * ParticleStorage.hpp
 *
 *  Created on: 18.04.2010
 *      Author: bknopp
 */

#ifndef PARTICLESTORAGE_HPP_
#define PARTICLESTORAGE_HPP_

#include "Particle.hpp"
//#include "AnnealedParticleFilter.hpp"
#include <iostream>
#include <wombat/helpers.h>

namespace wombat
{

	/*!
	 *	stores a particles with information about its layer, partition and timestep
	 */
	template<typename StateType>
	class AnnealingParticleData
	{
	public:
		AnnealingParticleData(Particle<StateType> _p) : particle(_p), layer(0), partition(0), timestep(0){}
		AnnealingParticleData() : layer(0), partition(0), timestep(0){}
		Particle<StateType> particle;
		unsigned long layer, partition, timestep;
	};


	/*!
	 * stores (statistical information about an annealing layer
	 */
	template<typename StateType>
	class AnnealingLayerData
	{
	public:
		AnnealingLayerData() : desiredAnnealingRate(0), estimatedAnnealingRate(0), beta(0){}
	  double desiredAnnealingRate;
	  double estimatedAnnealingRate;
	  double beta;
	  double averageWeight;
	  double varianceWeight;
	  double maximumWeight;
	  double minimumWeight;
	  unsigned long layer, partition, timestep;
	  const Particle<StateType> *bestParticle;
	};



	/*!
	 * container for particle and layer information
	 */
	template<typename StateType>
	class ParticleStorage
	{
	public:
		typedef AnnealingParticleData<StateType> AnnealingParticleDataType;
		typedef AnnealingLayerData<StateType> AnnealingLayerDataType;
		void addLayerData(const AnnealingLayerDataType &_data){ mLayerData.push_back(_data); }
		const AnnealingLayerDataType& layerData(size_t _index) const {return mLayerData.at(_index); }
		const AnnealingLayerDataType* layerData(unsigned long _timestep,
				unsigned long _partition, unsigned long _layer) const;
		size_t layerDataCount() const {return mLayerData.size(); }

		void addParticleData(const AnnealingParticleDataType &_data){ mParticleData.push_back(_data); }
		const AnnealingParticleDataType& particleData(size_t _index) const {return mParticleData.at(_index); }
		bool particleIsOptimum(size_t _index) const;
		const AnnealingParticleData<StateType>* findBestParticle(unsigned long _timestep,
				unsigned long _partition, unsigned long _layer) const;
		void markBestParticle(unsigned long _timestep, unsigned long _partition, unsigned long _layer);

		size_t  particleDataCount() const {return mParticleData.size(); }

		void clear();
		bool writeMatlabFile(const std::string &_filename) const;

	protected:
		std::string particleDataToString(const AnnealingParticleDataType &_data) const;
		std::string layerDataToString(const AnnealingLayerDataType &_data) const;

		std::vector<AnnealingParticleDataType> mParticleData;
		std::vector<AnnealingLayerDataType> mLayerData;
	};


	//*****************************************************************************************************************


	template<typename StateType>
	const AnnealingLayerData<StateType>* ParticleStorage<StateType>::layerData(unsigned long _timestep,
		unsigned long _partition, unsigned long _layer) const
	{
//		TRACE("returning layer data for %i %i %i", _timestep, _partition, _layer);
		for(typename std::vector<AnnealingLayerDataType>::const_iterator it = mLayerData.begin(); it != mLayerData.end(); it++)
		{
			if((_timestep == it->timestep) & (_layer == it->layer) & (_partition == it->partition))
			{
				return &(*it);
			}
		}
		return 0;
	}

	template<typename StateType>
	bool ParticleStorage<StateType>::particleIsOptimum(size_t _index) const
	{
		if(_index >= mParticleData.size()) return false;

		const AnnealingLayerDataType* lData = layerData(mParticleData.at(_index).timestep, mParticleData.at(_index).partition, mParticleData.at(_index).layer);
		if(lData == 0)
		{
			//std::cout << "can't estimate optimum, no layer data for current particle" << std::endl;
			return false;
		}

		if(lData->bestParticle->weight == mParticleData.at(_index).particle.weight) return true;

		return false;
	}

	template<typename StateType>
	const AnnealingParticleData<StateType>* ParticleStorage<StateType>::findBestParticle(unsigned long _timestep,
		unsigned long _partition, unsigned long _layer) const
	{
		const AnnealingParticleData<StateType>* data = 0;
		double maxWeight = -1;

		for(typename std::vector<AnnealingParticleDataType>::const_iterator it = mParticleData.begin(); it != mParticleData.end(); it++)
		{
			if((_timestep == it->timestep) & (_layer == it->layer) & (_partition == it->partition) & (it->particle.weight > maxWeight))
			{
				data = &(*it);
				maxWeight = it->particle.weight;
			}
		}

		//std::cout << "best particle has weight:" << data->particle.weight << std::endl;
		return data;
	}

	template<typename StateType>
	void ParticleStorage<StateType>::markBestParticle(unsigned long _timestep, unsigned long _partition, unsigned long _layer)
	{
		const AnnealingParticleData<StateType>* particleData = findBestParticle(_timestep, _partition, _layer);
		if(particleData == 0) return;

		for(typename std::vector<AnnealingLayerDataType>::iterator it = mLayerData.begin(); it != mLayerData.end(); it++)
		{
			if((_timestep == it->timestep) & (_layer == it->layer) & (_partition == it->partition))
			{
				it->bestParticle = &(particleData->particle);
				return;
			}
		}
	}


	template<typename StateType>
	void ParticleStorage<StateType>::clear()
	{
		mParticleData.clear();
		mLayerData.clear();
	}

	template<typename StateType>
	bool ParticleStorage<StateType>::writeMatlabFile(const std::string &_filename) const
	{
		if(_filename.size() == 0) return false;

		std::ofstream stream;
		stream.open(_filename.c_str());

		const std::string preParticles ="% timestep, partition, layer, state, weight, partial weights \n"
				"particles = [\n";
		const std::string postParticles = "];\n";

		stream << preParticles;

		typename std::vector<AnnealingParticleData<StateType> >::const_iterator it;
		for(it = mParticleData.begin(); it != mParticleData.end(); it++)
		{
			const AnnealingParticleData<StateType> &data = *it;
			stream << particleDataToString(data);
			stream << "\n";
		}

		stream << postParticles;

		// ************************************************************************************************************
		const std::string preLayer = "% layer, partition, timestep, averageWeight varianceWeight minimumWeight "
				"maximumWeight beta desiredAnnealingRate estimatedAnnealingRate\n"
				"layers = [\n";
		const std::string postLayer = "];\n";

		stream << preLayer;

		for(typename std::vector<AnnealingLayerDataType>::const_iterator it = mLayerData.begin(); it != mLayerData.end(); it++)
		{
			stream << layerDataToString(*it);
			stream << "\n";
		}

		stream << postLayer;
		// ************************************************************************************************************

		stream.close();
		return true;
	}


	template<typename StateType>
	std::string  ParticleStorage<StateType>::particleDataToString(const AnnealingParticleDataType &_data) const
	{
		std::string value;

		value += toString(_data.timestep);
		value += " ";
		value += toString(_data.partition);
		value += " ";
		value += toString(_data.layer);
		value += " ";
		value += doublesToString((_data.particle.state.toDoubles()));
		value += " ";
		value += fToString(_data.particle.weight);
		value += " ";
		value += doublesToString(_data.particle.partialWeights);

		return value;
	}


	template<typename StateType>
	std::string  ParticleStorage<StateType>::layerDataToString(const AnnealingLayerDataType &_data) const
	{
		std::string value;

		value += toString(_data.timestep);

		value += " ";
		value += toString(_data.partition);

		value += " ";
		value += toString(_data.layer);

		value += " ";
		value += fToString(_data.averageWeight);

		value += " ";
		value += fToString(_data.varianceWeight);

		value += " ";
		value += fToString(_data.minimumWeight);

		value += " ";
		value += fToString(_data.maximumWeight);

		value += " ";
		value += fToString(_data.beta);

		value += " ";
		value += fToString(_data.desiredAnnealingRate);

		value += " ";
		value += fToString(_data.estimatedAnnealingRate);

		return value;
	}


} // end NS wombat

#endif /* PARTICLESTORAGE_HPP_ */
