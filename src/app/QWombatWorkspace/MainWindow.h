#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_MainWindowBase.h"

#include <wombat/basetypes.h>
#include <wombat/helpers.h>
#include <wombat/voxels.h>
/*
 * 	FORWARDS
 */
namespace wombat
{
	class QMessageWriter;
	class GLRenderWidget;
	class BodyConfiguratorWidget;
	class ConfiguratorWidget;
	class QPlaybackControl;
	class AnnealedParticleFilterHistoryWidget;
	class TrackerControlWidget;
	class BodySpacesRenderEngine;
	class BodyRenderEngine;
	template<typename T> class VoxelspaceRenderEngine;

	class PtcReaderThread;
}

class ModelThread;
class TrackerProgressWidget;

class MainWindow: public QMainWindow, public Ui::MainWindowBase
{
Q_OBJECT
public:
	MainWindow(QWidget *_parent = 0, Qt::WindowFlags _flags = 0);
	virtual ~MainWindow();

public slots:

signals:
	void projectOpened();
	void projectClosed();
	void projectModified();

protected slots:
	/*!
	 * request creation of a new project
	 */
	void newProjectRequest();

	/*!
	 * open an existing project
	 */
	void openProject();

	/*!
	 * setup the workspace to work with the project currently active
	 */
	void setupProject();

	/*!
	 * check if an open project exists and save it if required
	 */
	void closeAndSaveProject();

	/*!
	 * save project
	 */
	void saveProject();

	/*!
	 *	save project with new filename
	 */
	void saveProjectAs();

	/*!
	 * close project
	 */
	void closeProject();


	void toggleFullscreen();
	void toggleLogger();
	void showPreferences();
	void showAbout();

	/*!
	 *  adapt window title to current project
	 */
	void updateWindowTitle();

	/*!
	 * adapt gui state to project state
	 */
	void updateWindowState();

	void writeBodyStateToCurrentProject();

	void startProjectThreads();
	void stopProjectThreads();

	/*!
	 * this function is called AFTER the modell thread has finished initilization
	 */
	void initModelControllerDone();

	void drawBodyVoxels();
	void calculateWeights();
	void updateVoxelspace();

    void handleParticleFilterCreated();
    void handleParticleFilterDestroyed();

    void handleTrackerRunning();
    void handleTrackerSleeping();

    void handleBodyScaleChanged();
    // should be called when a body has been created OR destroyed by the model thread
    void handleBodyChanged();

    void handlePtcFileChanged();

	void updateMdiWindowState();

	void handleVoxelspaceLoaded(size_t _voxelspaceIndex);
	void requestVoxelspace(size_t _voxelspaceIndex);
protected:
	void initUi();
	void initLogger();
	void initRenderWidgets();
	void initRenderEngines();

	void createConfiguratorWidget();
	void deleteConfiguratorWidget();

	void initSidebars();

	void saveWindowStates();
	void loadWindowStates();

	void createMdiMenu();
	void updateMdiMenu();

	void closeEvent(QCloseEvent *_event);


	QAction *actionPreMdi, *actionNextMdi, *actionTileMdi, *actionCascadeMdi;

	// mdi widgets
	wombat::GLRenderWidget *mPrimaryRenderWidget;
	wombat::BodyConfiguratorWidget *mBodyConfiguratorWidget;
	wombat::ConfiguratorWidget *mConfiguratorWidget;
	wombat::QPlaybackControl *mPlaybackControl;
	wombat::TrackerControlWidget *mTrackerControl;
	wombat::AnnealedParticleFilterHistoryWidget *mHistoryWidget;

	wombat::BodySpacesRenderEngine *mBodySpacesRenderEngine;
	wombat::BodyRenderEngine *mBodyRenderEngine;
	wombat::VoxelspaceRenderEngine<wombat::VoxelValueExt> *mVoxelspaceRenderEngine;

	wombat::PtcReaderThread *mReaderThread;
	ModelThread *mModelThread;
	TrackerProgressWidget *mProgressWidget;


};

#endif // MAINWINDOW_H
