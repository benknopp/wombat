/*
 * PtcReaderThread.cpp
 *
 *  Created on: 30.04.2010
 *      Author: bknopp
 */

#include "PtcReaderThread.h"

#include <wombat/voxels.h>
#include <wombat/body.h>
#include <wombat/filters.h>
#include <wombat/helpers.h>
#include <wombatui_qt/wombatui_qt.h>


namespace wombat
{

PtcReaderThread::PtcReaderThread()
	: mVoxelspaceReader(0), mVoxelspace(0), mCurrentIndex(0)
{
}

PtcReaderThread::~PtcReaderThread()
{
}


bool PtcReaderThread::openProjectPtcFile()
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

	const QString ptcFileName = project->valueMap.value("ptc_file", "").toString();
	return openPtcFile(ptcFileName);
}

bool PtcReaderThread::openPtcFile(const QString &_filename)
{
	if(mVoxelspaceReader == 0)
	{
		TRACE("thread not running. can't open file");
		return false;
	}

	bool success = mVoxelspaceReader->open(_filename.toStdString());
	if(success)
	{
		mFileName = _filename;

		if(mVoxelspace != 0) delete mVoxelspace;
		readVoxelspaceMeta();
		mVoxelspace = new Voxelspace<VoxelValueExt>(mVoxelspaceSize.x(), mVoxelspaceSize.y(), mVoxelspaceSize.z());

		fileOpened(mFileName);
	}

	return success;
}

void PtcReaderThread::closePtcFile()
{
	if(mVoxelspaceReader == 0) return;
	mVoxelspaceReader->close();
}

QString PtcReaderThread::ptcFileName() const
{
	return mFileName;
}

void PtcReaderThread::run()
{
	mVoxelspaceReader = new VoxelspaceReader<VoxelValueExt>();

	mTerminateThread = false;

	TRACE("reading voxelspace 0");
	readVoxelspace(0);

	while(!mTerminateThread)
	{

	}

	exec();
}

void PtcReaderThread::stop()
{
	mTerminateThread = true;
	fileClosed();
}

size_t PtcReaderThread::currentVoxelspaceIndex() const
{
	return mCurrentIndex;
}

size_t PtcReaderThread::voxelspacesCount()
{
	if(mVoxelspaceReader == 0) return 0;
	return mVoxelspaceReader->size();
}

QMap<QString, VoxelspaceMeta> PtcReaderThread::voxelspaceMeta() const
{
	return mVoxelspaceMeta;
}

Eigen::Vector3i PtcReaderThread::voxelspaceSize() const
{
	return mVoxelspaceSize;
}

bool PtcReaderThread::readVoxelspace(size_t _index, VoxelspaceType &_voxelspace)
{
	std::cout << "reading voxelspace:" << _index << "\n";
	//bool success = mVoxelspaceReader->nextVoxelspace();
	bool success = mVoxelspaceReader->setVoxelspaceIndex(_index);
	if(!success) return false;

	success = mVoxelspaceReader->readVoxelspace(*mVoxelspace);
	if(!success) return false;
	_voxelspace = *mVoxelspace;
	return true;
}

wombat::Voxelspace<wombat::VoxelValueExt>* PtcReaderThread::voxelspace() const
{
	return mVoxelspace;
}


void PtcReaderThread::readVoxelspace(size_t _index)
{
	if( _index >= mVoxelspaceReader->size()) return;
//	bool success = mVoxelspaceReader->nextVoxelspace();
	bool success = mVoxelspaceReader->setVoxelspaceIndex(_index);

	if(!success) return;

	success = mVoxelspaceReader->readVoxelspace(*mVoxelspace);
	if(success)
	{
		voxelspaceLoaded(_index);
	}
}

void PtcReaderThread::readVoxelspaceMeta()
{
	mVoxelspaceMeta.clear();
	if(mVoxelspaceReader == 0) return;
	std::map<std::string, VoxelspaceMeta> meta = mVoxelspaceReader->meta();

	for(std::map<std::string, VoxelspaceMeta>::const_iterator it = meta.begin(); it != meta.end(); it++)
	{
		mVoxelspaceMeta[QString::fromStdString(it->first)] = it->second;
	}

	bool hasSizeMeta =(meta.find("VOXELSPACE_SIZE") != meta.end());

	if(hasSizeMeta)
	{
		const unsigned* size = reinterpret_cast<const unsigned*>(meta["VOXELSPACE_SIZE"].data);
		mVoxelspaceSize << size[0], size[1], size[2];
	} else
	{
		Logger::criticalErrorMessage("no voxelspace sizes found, assuming default (150^3");
		TRACE("no voxelspace sizes found, assuming default (150^3");
		mVoxelspaceSize << 150, 150, 150;
	}

	std::cout << "voxelspace size is " << mVoxelspaceSize.transpose() << "\n";

}


}
