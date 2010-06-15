/*
 * AnnealedParticleFilterFactory.h
 *
 *  Created on: 09.04.2010
 *      Author: bknopp
 */

#ifndef ANNEALEDPARTICLEFILTERFACTORY_H_
#define ANNEALEDPARTICLEFILTERFACTORY_H_

#include <wombat/body.h>
#include <wombat/filters.h>

/*
 *
 */
namespace wombat
{

class QWombatProject;

/*!
 * this factory can create exactly one instance of an annealed particle filter
 * and manages all its members / strategies
 */
class AnnealedParticleFilterFactory
{
	public:
		/*!
		 * pointer to singleton if this class
		 * @return
		 */
		static AnnealedParticleFilterFactory* instance();

		/*!
		 * get instance of the filter, create one, if none is present
		 * @return
		 */
		wombat::AnnealedParticleFilter<wombat::BodyStateVector>* theParticleFiler() const;

		/*!
		 *	rebuild the filter and read current setup from project
		 */
		void rebuildAndUpdateByProject();

		/*!
		 * set sources AND rebuild depending filter parts (not the whole filter)
		 * @param _body
		 * @param _configurator
		 * @param _voxelspace
		 */
		void setSources(Body *_body, AbstractBodyConfigurator *_configurator, Voxelspace<wombat::VoxelValueExt> *_voxelspace);

		/*!
		 * unset sorces, i.a. mark them as invalid
		 */
		void unsetSources();

		/*!
		 * update all parameters which can be changed without a complete rebuild of the filter
		 */
		void updateRuntimeParameters();



		ParticleStorage<BodyStateVector>* particleStorage() const { return mParticleStorage;}
		// TODO: should be obsolete use rebuildAndUpdateByProject instead
		//void rebuild(){createParticleFilter();}
	protected:
		AnnealedParticleFilterFactory();
		virtual ~AnnealedParticleFilterFactory();

		bool createParticleFilter();
		void deleteParticleFilter();

		void createDiffusionStrategy();
		void deleteDiffusionStrategy();

		void createObservationModel();
		void deleteObservationModel();

		void createModeSelector();
		void deleteModeSelector();

		void createParticleGenerator();
		void updateGaussianParticleGenerator();
		void updateRandomFieldParticleGenerator();
		void updateIterativeParticleGenerator();
		void deleteParticleGenerator();


		AnnealedParticleFilter<wombat::BodyStateVector>* mParticleFilter;
		QWombatProject *mProject;

		AbstractBodyConfigurator *mBodyConfigurator;
		Body* mBody;

		AbstractDiffusionStrategy<BodyStateVector> *mDiffusionStrategy;
		AbstractModeSelector<BodyStateVector> *mModeSelector;
		AbstractParticleGenerator<BodyStateVector> *mParticleGenerator;
		ParticleStorage<BodyStateVector> *mParticleStorage;

		BodyObservationModel *mObservationModel;
		Voxelspace<wombat::VoxelValueExt> *mVoxelspace;

		static AnnealedParticleFilterFactory *mInstance;
};

}

#endif /* ANNEALEDPARTICLEFILTERFACTORY_H_ */
