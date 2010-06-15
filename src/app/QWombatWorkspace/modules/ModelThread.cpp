#include "ModelThread.h"

#include <wombat/helpers.h>
#include <wombatui_qt/wombatui_qt.h>
#include <cstdlib>


using namespace wombat;

ModelThread::ModelThread()
    : mInitDone(false), mBodyConfigurator(0), mVoxelspace(0), mParticleFilter(0),
      mBodyObservationModel(0), mBody(0), mBodyPrimitiveType(wombat::CylinderPrimitve),
      mFilterFactory(0)
{
}

void ModelThread::run()
{
    TRACE("starting  new modelthread")
    if(mInitDone) cleanUp();
	mInitDone = true;

	bool isValid = parseAndCreateProject();
	if(!isValid)
	{
		Logger::criticalErrorMessage("could not parse and create the body model.");
		cleanUp();
		return;
	}

    bool timeout = false;
    unsigned count = 0;

    /*!
     * wait for  body configurator to become ready
     */
    while(!(mBodyConfigurator->isReady() | timeout))
    {
        TRACE("waiting for model..");
        count++;
        if(count > 300) timeout = true;
        msleep(500);
    }

    if(!timeout & mBodyConfigurator->isReady())
    {
        rebuildBody();
        initDone();
    } else
    {
        // ok, somethings wrong
        Logger::criticalErrorMessage("somethings wrong with your model configurator. aborting");
        return;
    }

    mFilterFactory = AnnealedParticleFilterFactory::instance();
    updateByProject();
	particleFilterCreated();
	runTracker();

    exec();
}

void ModelThread::cleanUp()
{
	stopped();
	msleep(500); // sleep some time to give everybody a chance do disconnect

    if(mBodyConfigurator) delete mBodyConfigurator;
    if (mParticleFilter) delete mParticleFilter;
}


wombat::AbstractBodyConfigurator* ModelThread::bodyConfigurator()
{
    return mBodyConfigurator;
}


void ModelThread::setVoxelspace(const wombat::Voxelspace<wombat::VoxelValueExt> &_voxelspace, size_t _voxelspaceIndex)
{
	if(mVoxelspace == 0)
	{
		mVoxelspace = new Voxelspace<wombat::VoxelValueExt>(_voxelspace);
	} else
	{
		(*mVoxelspace) = _voxelspace;
	}

	if(mParticleFilter)
	{
		BodyObservationModel *om = dynamic_cast<BodyObservationModel*>(mParticleFilter->observationModel());
		if(om)
		{
			om->setVoxelspace(mVoxelspace);
		} else
		{
		}

		if(mParticleFilter->particleStorage())
		{
			TRACE("setting current time to %lu", _voxelspaceIndex);
			mParticleFilter->setCurrentTimeStep(_voxelspaceIndex);
		}
	}

}


wombat::Voxelspace<wombat::VoxelValueExt>* ModelThread::voxelspace() const
{
	return mVoxelspace;
}


wombat::AnnealedParticleFilter<wombat::BodyStateVector>* ModelThread::particleFiler() const
{
	return mParticleFilter;
}


void ModelThread::setBodyState(const wombat::BodyStateVector *_state)
{
    BodyConfiguration config;
    mBodyConfigurator->configure(*_state, config);
    mBody->configure(config);
    bodyChanged();

    std::vector<Vector3d> positions;
    std::vector<std::string> names;

    readJointPositions(*mBody, positions, names);

    std::cout << "\n\n";
    for(unsigned i=0; i < names.size(); i++)
    {
    	std::cout << names[i] << "\n";
    }

    for(unsigned i=0; i < positions.size(); i++)
    {
    	std::cout << positions[i] << "\n";
    }
    std::cout << "\n\n";
}


void ModelThread::resizeBodyPart(const QString _name, double _x, double _y, double _z)
{
    bool found = false;
    TRACE("resizing body part");
    AbstractBodyPart* part = mBody->bodyPart(_name.toStdString(), &found);
    VectorXd vec(3);
    vec << _x, _y, _z;
    part->resize(vec);

    bodyChanged();
}


void ModelThread::rebuildBody()
{
    if(mBody) delete mBody;
    bodyChanged();

    Logger::statusMessage("creating new body-model..");
    mBody = mBodyConfigurator->createBody(mBodyPrimitiveType);
    if(mBodyObservationModel) mBodyObservationModel->setBody(mBody);

    if(mFilterFactory)
    {
    	updateByProject();
    }

    /*
     * who uses mBody ?
     * - mBodyObservationModel
     * - BodyPartsRenderEngine
     * - BodyRenderEngine
     */


    bodyChanged();
}


void ModelThread::testIntersection()
{
	if(mBody==0) return;
	if(mVoxelspace==0) return;

#define SYMMETRIC
#ifdef SYMMETRIC

	SymmetricVoxelspaceIntersector intersector;
    double sum = 0;
    resetLabels(*mVoxelspace);

	for(unsigned i=0; i < mBody->size(); i++)
	{
	    double overlapping = intersector(*(mBody->bodyPart(i).voxelspace()), *mVoxelspace);
	    sum += overlapping;
	    //std::cout << mBody->bodyPart(i).partName() << " -> overlapping: " << overlapping << "\n";
	}

	std::cout << "OVERALL RATING:" << sum / (double) mBody->size() << "\n";

#else
	Voxelspace<VoxelValueExt> *mIntersectionSpace = new Voxelspace<VoxelValueExt>(100, 100, 100);

    VoxelspaceIntersector<VoxelValueExt> intersector;
	intersector.setDestinationValue(VoxelValueExt(128, 128, 246, 255, true, 1));
    intersector.setStepSize(Vector3i(1, 1, 1));

	// iterate over all bodyparts
    Timer t;
    t.start();
    double  hits, total, percent;

	for(unsigned i=0; i < mBody->size(); i++)
	{
	    intersector(*mIntersectionSpace,
	    		*(mBody->bodyPart(i).voxelspace()), *mVoxelspace);

	    total = mBody->bodyPart(i).voxelspace()->occupiedVoxelsCount();
	    hits = intersector.hits();
	    percent = hits / total;
	    std::cout << mBody->bodyPart(i).partName() << " -> hits: " << hits <<
	    		" ~ " << percent * 100 << " %" << std::endl;
	}

	double ellapsed = t.stop();
	ellapsed /= 1000000;
	QString message = "intersection took ";
	message.append(QString::number(ellapsed)).append(" seconds");
	Logger::statusMessage(message);
#endif
}


void ModelThread::startTracking()
{
	mTrackSingleStep = false;
	mTrackerSleeping = false;
}


void ModelThread::startSingleStepTracking()
{
	mTrackSingleStep = true;
	mTrackerSleeping = false;
}


void ModelThread::stopTracking()
{
	mTrackerSleeping = true;
}

void ModelThread::updateByProject()
{
	mFilterFactory->setSources(mBody, mBodyConfigurator, mVoxelspace);
	mFilterFactory->rebuildAndUpdateByProject();
	mParticleFilter = mFilterFactory->theParticleFiler();
}


bool ModelThread::parseAndCreateProject()
{
	QGlobalState *state = QGlobalState::instance();

	if(!state)
	{
		Logger::criticalErrorMessage("could not connect to global state. aborting.");
		return false;
	}

	QWombatProject *project = state->currentProject;
	if(!project)
	{
		Logger::criticalErrorMessage("no project currently opened. aborting.");
		return false;
	}

	/**************************************************************************
	 *					CREATE BODY CONFIGURATOR
	 *************************************************************************/

	const QString type = project->valueMap.value("model_type", "native").toString();

	if(type.compare("native") == 0)
	{
		const QString filename  = project->valueMap.value("model_file", "").toString();
		Logger::statusMessage("loading new NATIVE bodymodel from: " + filename.toStdString());
		NativeBodyConfigurator *configurator = new NativeBodyConfigurator();
		mBodyConfigurator = configurator;

		QFile file(filename);
		file.open(QIODevice::ReadOnly);

		QNativeBodyXmlBackend backend;
		backend.read(&file);

		fillConfiguratorFromBackend(*configurator, backend);
		configurator->generate();

	}

#ifdef WITH_MATLAB_SUPPORT
	if(type.compare("matlab") == 0)
	{
		const QString dir  = project->valueMap.value("matlab_model", "").toString();
		TRACE("loading new bodymodel from %s", dir.toStdString().c_str());
	    Logger::statusMessage("loading new MATLAB bodymodel from: " + dir.toStdString());
	    mBodyConfigurator =  new wombat::MatlabBodyConfigurator(dir);
	    TRACE("matlab adapter created.");
	}
#endif

	return true;
}


bool ModelThread::deleteTracker()
{
	bool success = true;


	if(mParticleFilter)
	{
		stopTracking();
		sleep(1);
		delete mParticleFilter;
		mParticleFilter = 0;
		TRACE("deleting tracker(particle filter)");
		Logger::statusMessage("deleting current tracker(particle filter) instance");
	} else
	{

	}


	return success;
}



void ModelThread::runTracker()
{
	bool exitTracker = false;
	mTrackerSleeping = true;
	mTrackSingleStep = true;

	BodyStateVector *optimState = 0;

	trackerRunning();

	// run until interupted or no frames left
	while(!exitTracker)
	{
		while(mTrackerSleeping)
		{
			msleep(1000);
			//std::cout << ".\n";
			trackerSleeping();
		}
		trackerRunning();

		if(mTrackSingleStep)
		{
			mTrackerSleeping = true;
		} else
		{
			// TODO: request next frame
		}
		if(!mBody->isRasterized()) mBody->rasterize();

		mParticleFilter->setMatlabFileName("results.m");

		TRACE("generating particles");
		mParticleFilter->generateParticles();

		TRACE("starting filter");
		mParticleFilter->filter();

		optimState = mParticleFilter->optimalState();
		if(optimState != 0)
		{
			setBodyState(optimState);
		}

	}

	trackerSleeping();
}
