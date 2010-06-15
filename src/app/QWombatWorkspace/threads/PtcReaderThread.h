/*
 * PtcReaderThread.h
 *
 *  Created on: 30.04.2010
 *      Author: bknopp
 */

#ifndef PTCREADERTHREAD_H_
#define PTCREADERTHREAD_H_

#include <QThread>
#include <QMap>
#include <QString>

#include <wombat/voxels.h>
#include <wombat/basetypes.h>

namespace wombat
{

template<typename T> class VoxelspaceReader;
template<typename T> class Voxelspace;


class PtcReaderThread : public QThread
{
	Q_OBJECT
public:
	typedef wombat::Voxelspace<wombat::VoxelValueExt> VoxelspaceType;
	PtcReaderThread();
	virtual ~PtcReaderThread();

	bool openProjectPtcFile();
	bool openPtcFile(const QString &_filename);
	void closePtcFile();
	QString ptcFileName() const;

	void run();
	void stop();

	bool isReady() const{ return (mVoxelspaceReader != 0);}

	size_t currentVoxelspaceIndex() const;
	size_t voxelspacesCount();
	QMap<QString, VoxelspaceMeta> voxelspaceMeta() const;
	Eigen::Vector3i voxelspaceSize() const;

	bool readVoxelspace(size_t _index, VoxelspaceType &_voxelspace);
	wombat::Voxelspace<wombat::VoxelValueExt>* voxelspace() const;

public slots:
	void readVoxelspace(size_t _index);

signals:
	void fileOpened(QString _filename);
	void fileClosed();
	void voxelspaceLoaded(size_t _frameIndex);
protected:
	void readVoxelspaceMeta();

	QString mFileName;
	wombat::VoxelspaceReader<wombat::VoxelValueExt>*	mVoxelspaceReader;
    VoxelspaceType* 									mVoxelspace;
    Eigen::Vector3i 									mVoxelspaceSize;
    QMap<QString, VoxelspaceMeta>						mVoxelspaceMeta;

    size_t mCurrentIndex;
    bool mTerminateThread;
};

}

#endif /* PTCREADERTHREAD_H_ */
