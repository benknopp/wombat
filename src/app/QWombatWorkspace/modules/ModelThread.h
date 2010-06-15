#ifndef MODELTHREAD_H
#define MODELTHREAD_H

#include <QThread>
#include <QString>
#include <wombat/body.h>
#include <wombat/filters.h>
#include "AnnealedParticleFilterFactory.h"


namespace wombat
{
//template<typename T> class VoxelspaceReader;
template<typename T> class Voxelspace;
class AnnealedParticleFilterFactory;
}


class ModelThread : public QThread
{
    Q_OBJECT
public:
    ModelThread();
    void run();

    /*!
     * get pointer to the body configurator
     * @return
     */
    wombat::AbstractBodyConfigurator *bodyConfigurator();
    /*!
     * get pointer to the body
     * @return
     */
    wombat::Body* body() const{return mBody;}


    /*!
     * set voxelspace which should be used by the filter, voxelspace will be copied
     * @param _voxelspace
     */
    void setVoxelspace(const wombat::Voxelspace<wombat::VoxelValueExt> &_voxelspace,
    		size_t _voxelspaceIndex = 0);

    /*!
     * get pointer to the voxelspace containing the volume read from the ptc file
     * @return
     */
    wombat::Voxelspace<wombat::VoxelValueExt>* voxelspace() const;

    /*!
     * get pointer to the particle filter
     * @return
     */
    wombat::AnnealedParticleFilter<wombat::BodyStateVector>* particleFiler() const;

    bool isSleeping() const {return mTrackerSleeping;}
public slots:
	/*!
	 * set the body state-vector and configure mBody according to it.
	 */
    void setBodyState(const wombat::BodyStateVector *_state);

    /*!
     * resize body parts, used by bodyconfiguration widget
     */
    void resizeBodyPart(const QString _name, double _x, double _y, double _z);

    /*!
     * rebuild the body (caused by model-adapter changes)
     */
    void rebuildBody();

    /*!
     * test intersection of body and voxelspace (in current body pose)
     */
    void testIntersection();

    /*!
     * start tracking over multiple frames
     */
    void startTracking();

    /*!
     *  start tracking only for current frame
     */
    void startSingleStepTracking();

    /*!
     * stop tracking
     */
    void stopTracking();

    /*!
     * update (i.e. rebuild) tracker with project specific information
     */
    void updateByProject();

signals:
    void initDone();
    void bodyChanged();
    void stopped();

    void voxelspaceLoaded();

    void particleFilterCreated();
    void particleFilterDestroyed();

    void trackerRunning();
    void trackerSleeping();

protected:
    /*!
     * parse the currently opened project, and adapt all settings to it
     */
    bool parseAndCreateProject();

    /*!
     * delete the current tracker with all its members
     * @return true if tracker could be deleted, false otherwise
     */
    bool deleteTracker();

    /*!
     *	tracker main
     */
    void runTracker();

    void cleanUp();
//    bool readVoxelspaceMeta();

    bool mInitDone, mTrackSingleStep, mTrackerSleeping;

    // for now use only the matlab backend
    wombat::AbstractBodyConfigurator *mBodyConfigurator;
    wombat::Voxelspace<wombat::VoxelValueExt> *mVoxelspace;

    /*!
     * filter stuff
     */
	wombat::AnnealedParticleFilter<wombat::BodyStateVector> *mParticleFilter;
	wombat::BodyObservationModel *mBodyObservationModel;


    Eigen::Vector3i mVoxelspaceSize;
    size_t mVoxelspaceFrameId;

    wombat::Body *mBody;
    int mBodyPrimitiveType;

    wombat::AnnealedParticleFilterFactory *mFilterFactory;
};

#endif // MODELTHREAD_H
