#include "MainWindow.h"

#include"modules/ModelThread.h"
#include"threads/PtcReaderThread.h"

#include"dialogs/SettingsDialog.h"
#include"dialogs/TrackerProgressWidget.h"
#include"dialogs/NewProjectDialog.h"

#include<QtGui>
#include<wombat/body.h>
#include<wombat/helpers.h>
#include <wombatui_qt/wombatui_qt.h>

using namespace wombat;

MainWindow::MainWindow(QWidget *_parent, Qt::WindowFlags _flags) :
	QMainWindow(_parent, _flags), mPrimaryRenderWidget(0), 	mBodyConfiguratorWidget(0), mConfiguratorWidget(0),
			mPlaybackControl(0), mTrackerControl(0), mHistoryWidget(0),
			mBodySpacesRenderEngine(0), mBodyRenderEngine(0), mVoxelspaceRenderEngine(0), mReaderThread(0),
			mModelThread(0), mProgressWidget(0)
{
	qRegisterMetaType<Qt::Orientation> ("Qt::Orientation");
	setupUi(this);
	initUi();
}

MainWindow::~MainWindow()
{
	saveWindowStates();
}

void MainWindow::newProjectRequest()
{
	closeAndSaveProject();

	if(QGlobalState::instance()->currentProject)
	{
		QMessageBox::information(this, "create new project", "please save and/or close existing project BEFORE creating a new one");
		return;
	}
	QGlobalState::instance()->currentProject = new QWombatProject();
	NewProjectDialog *dialog = new NewProjectDialog(this);
	dialog->setProject(QGlobalState::instance()->currentProject);
	connect(dialog, SIGNAL(accepted()), this, SLOT(setupProject()));
	connect(dialog, SIGNAL(rejected()), this, SLOT(closeProject()));

	dialog->show();
}


void MainWindow::openProject()
{
	closeAndSaveProject();

	QSettings settings(QApplication::organizationName(),
			QApplication::applicationName());
	QString dirname = settings.value("general/lastDirName",
			QApplication::applicationDirPath()).toString();
	QString filename = QFileDialog::getOpenFileName(this,
			trUtf8("open project"), dirname, trUtf8("Project Files (*.xml)"));
	if (filename.isEmpty())
		return;
	QFileInfo info(filename);
	QString path = info.dir().absolutePath();
	settings.setValue("general/lastDirName", path);

	QWombatProject *project = new QWombatProject();
	bool loadSuccess = project->loadFromFile(filename);
	if (!loadSuccess)
	{
		QMessageBox::critical(this, trUtf8("load existing project"), trUtf8(
				"xml file is invalid. aborting"));
		Logger::criticalErrorMessage("invalid xml file. project loading aborted.");
		delete project;
		return;
	} else
	{
		QGlobalState::instance()->currentProject = project;
		setupProject();
	}
}

void MainWindow::setupProject()
{
	QWombatProject* project = QGlobalState::instance()->currentProject;

	if (project == 0)
	{
		Logger::statusMessage("hmm. there 's something wrong. setup project can't find a project.");
		return;
	}

	initRenderEngines();
	startProjectThreads(); // start the model thread
	projectOpened();

	/*
	 * update widgets
	 */
	mTrackerControl->readProjectData();
}


void MainWindow::closeAndSaveProject()
{
	QWombatProject* project = QGlobalState::instance()->currentProject;

	if (project != 0)
	{
		QMessageBox messageBox;
		messageBox.setText(trUtf8("The document has been modified."));
		messageBox.setInformativeText("Do you want to save your changes?");
		messageBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard
				| QMessageBox::Cancel);
		messageBox.setDefaultButton(QMessageBox::Save);
		int ret = messageBox.exec();

		switch (ret)
		{
		case QMessageBox::Save:
			if (project->filename().isEmpty())
			{
				saveProjectAs();
			}
			else
			{
				saveProject();
			}
			closeProject();
			break;

		case QMessageBox::Discard:
			closeProject();
			break;

		default:
		case QMessageBox::Cancel:
			// do nothing
			break;
		}
	}
}


void MainWindow::saveProject()
{
	QWombatProject* project = QGlobalState::instance()->currentProject;

	// exit if nothing can be saved
	if (project == 0)
		return;

	writeBodyStateToCurrentProject();

	// ask for filename if project has not beeen saved before
	if (project->filename().isEmpty())
	{
		saveProjectAs();
	}
	else
	{
		project->saveToFile(project->filename());
	}
}


void MainWindow::saveProjectAs()
{
	QWombatProject* project = QGlobalState::instance()->currentProject;
	if (project == 0)
		return;

	QSettings settings(QApplication::organizationName(),
			QApplication::applicationName());
	QString dirname = settings.value("general/lastDirName",
			QApplication::applicationDirPath()).toString();

	QString filename = QFileDialog::getSaveFileName(this,
			trUtf8("save project"), dirname, trUtf8("Project Files (*.xml)"));
	project->setFilename(filename);
	saveProject();
}


void MainWindow::closeProject()
{
	QWombatProject* project = QGlobalState::instance()->currentProject;
	if (project == 0) return;

	project->close();
	delete project;
	QGlobalState::instance()->currentProject = 0;
	projectClosed();
}


void MainWindow::toggleFullscreen()
{
	if(actionFullScreen->isChecked())
	{
		this->setWindowState(Qt::WindowFullScreen);
	} else
	{
		this->setWindowState(Qt::WindowNoState);
	}
}


void MainWindow::toggleLogger()
{
	statusDockWidget->setVisible(actionLoggerToggle->isChecked());
}


void MainWindow::showPreferences()
{
	SettingsDialog *dialog = new SettingsDialog(this);
	dialog->show();
}


void MainWindow::showAbout()
{
	QApplication::aboutQt();
}


void MainWindow::updateWindowTitle()
{
	QWombatProject* project = QGlobalState::instance()->currentProject;
	QString name;

	if (project == 0)
	{
		name = "";
	}
	else
	{
		name = " - ";
		name.append(project->filename().isEmpty() ? trUtf8("unnamed project")
				: project->filename());
	}

	QString title = trUtf8("Pose Estimation Workbench");
	title.append(name);
	setWindowTitle(title);
}


void MainWindow::updateWindowState()
{
	QWombatProject* project = QGlobalState::instance()->currentProject;

	if (project == 0) // no project loaded
	{
		actionProjectNew->setEnabled(true);
		actionProjectOpen->setEnabled(true);
		actionProjectClose->setEnabled(false);
		actionProjectSave->setEnabled(false);
		actionProjectSaveAs->setEnabled(false);
		mPrimaryRenderWidget->enableInvertedBackground(true);
	}
	else
	{ // project loaded
		if (project->modified())
		{
			actionProjectNew->setEnabled(false);
			actionProjectOpen->setEnabled(false);
			actionProjectClose->setEnabled(true);

			if (project->filename().isEmpty())
			{
				actionProjectSave->setEnabled(false);
			}
			else
			{
				actionProjectSave->setEnabled(true);
			}

			actionProjectSaveAs->setEnabled(true);
		}
		else
		{
			actionProjectNew->setEnabled(false);
			actionProjectOpen->setEnabled(false);
			actionProjectClose->setEnabled(true);
			actionProjectSave->setEnabled(false);
			actionProjectSaveAs->setEnabled(false);
		}
		mPrimaryRenderWidget->enableInvertedBackground(true);
	}
}


void MainWindow::writeBodyStateToCurrentProject()
{
	QWombatProject *project = QGlobalState::instance()->currentProject;
	if (project == 0)
	{
		Logger::criticalErrorMessage("can't save body states to project. no project.");
		return;
	}

//	/*
//	 * save all bodystates
//	 */
//	QMultiMap<QString, QVariant>::iterator it = project->valueMap.find("state");
//	for (; it != project->valueMap.end(); it++)
//	{
//		project->valueMap.erase(it);
//	}
//
//	for (unsigned i = 0; i < mBodyConfiguratorWidget->statesCount(); i++)
//	{
//		wombat::BodyStateVector state = mBodyConfiguratorWidget->state(i);
//		QString serialized = QString::fromStdString(toString(state));
//		project->valueMap.insert("state", serialized);
//	}

	/*
	 * body sizes
	 */
	project->valueMap.replace("model_sizes",
			mBodyConfiguratorWidget->lastBodyPartFile());
}


void MainWindow::startProjectThreads()
{
	// do nothing if NO project is active
	if(QGlobalState::instance()->currentProject == 0)
	{
		Logger::criticalErrorMessage("can't run project threads. no project active");
		return;
	}
	stopProjectThreads();

	mReaderThread = new PtcReaderThread();
	mReaderThread->start();

	/*
	 * mReaderThread -> ...
	 */
	connect(mReaderThread, SIGNAL(fileOpened(QString)), this, SLOT(handlePtcFileChanged()), Qt::DirectConnection);
	connect(mReaderThread, SIGNAL(voxelspaceLoaded(size_t)), this, SLOT(handleVoxelspaceLoaded(size_t)), Qt::DirectConnection);

	/*
	 * ... -> mReaderThread
	 */
	connect(mPlaybackControl, SIGNAL(frameRequested(size_t)), this, SLOT(requestVoxelspace(size_t)), Qt::DirectConnection);


	while(! (mReaderThread->isReady() & mReaderThread->isRunning()))
	{
		std::cout << "waiting for reader thread." << std::endl;
		sleep(1);
	}

	bool fileOpened = mReaderThread->openProjectPtcFile();

	if(!fileOpened)
	{
		QMessageBox::warning(this, "open project,", "can't open project, ptc-file not found");
		mReaderThread->stop();
		closeProject();
		return;
	}

	mModelThread = new ModelThread();
	/*
	 *  mModelThread -> ...
	 */
	connect(mModelThread, SIGNAL(initDone()), this, SLOT(initModelControllerDone()), Qt::QueuedConnection);
	connect(mModelThread, SIGNAL(bodyChanged()), mPrimaryRenderWidget, SLOT(repaint()));
	connect(mModelThread, SIGNAL(voxelspaceLoaded()), this, SLOT(updateVoxelspace()), Qt::QueuedConnection);
	connect(mModelThread, SIGNAL(trackerRunning()), this, SLOT(handleTrackerRunning()));
	connect(mModelThread, SIGNAL(trackerSleeping()), this, SLOT(handleTrackerSleeping()));
	connect(mModelThread, SIGNAL(particleFilterCreated()), this, SLOT(handleParticleFilterCreated()));
	connect(mModelThread, SIGNAL(particleFilterDestroyed()), this, SLOT(handleParticleFilterDestroyed()));

	/*
	 * ... -> mModelThread
	 */
	connect(mBodyConfiguratorWidget, SIGNAL(stateChanged(const wombat::BodyStateVector*)),
			mModelThread, SLOT(setBodyState(const wombat::BodyStateVector*)), Qt::DirectConnection);
	connect(mBodyConfiguratorWidget, SIGNAL(bodyPartResized(QString,double,double,double)),
			mModelThread, SLOT(resizeBodyPart(QString,double,double,double)), Qt::DirectConnection);
	connect(mTrackerControl, SIGNAL(runClicked()), mModelThread, SLOT(startTracking()));
	connect(mTrackerControl, SIGNAL(oneStepClicked()), mModelThread, SLOT(startSingleStepTracking()));
	connect(mTrackerControl, SIGNAL(stopClicked()), mModelThread, SLOT(stopTracking()));
	connect(mBodyConfiguratorWidget, SIGNAL(seedChanged()), mModelThread, SLOT(updateByProject()));
	connect(mTrackerControl, SIGNAL(updateParticleFilter()), mModelThread, SLOT(updateByProject()));
	connect(mHistoryWidget, SIGNAL(requestBodyConfiguration(const wombat::BodyStateVector*)),
			mModelThread, SLOT(setBodyState(const wombat::BodyStateVector*)), Qt::DirectConnection);

	/*
	 *
	 */
	connect(mConfiguratorWidget, SIGNAL(bodyScaleChanged(double)), this, SLOT(handleBodyScaleChanged()));

	mModelThread->start();
}


void MainWindow::stopProjectThreads()
{
	if (mModelThread)
	{
		mModelThread->terminate();

		while(mModelThread->isRunning())
		{
			sleep(1);
			TRACE("waiting for model thread termination");
		}

		delete mModelThread;
	}
	mModelThread = 0;
}


void MainWindow::initModelControllerDone()
{
	TRACE("model initialization done");
	Logger::statusMessage("model initialization done");

	// tell body configut
	mBodyConfiguratorWidget->setBodyConfigurator(
			mModelThread->bodyConfigurator());

	mBodyRenderEngine = new BodyRenderEngine();
	connect(mModelThread, SIGNAL(bodyChanged()),
			this, SLOT(handleBodyChanged()));

	mPrimaryRenderWidget->addRenderEngine(mBodyRenderEngine);
	mPrimaryRenderWidget->repaint();

	mBodySpacesRenderEngine = new BodySpacesRenderEngine();
	mBodySpacesRenderEngine->setName("Buddie's Voxelspaces");
	mPrimaryRenderWidget->addRenderEngine(mBodySpacesRenderEngine);

	mBodyConfiguratorWidget->readProjectData();

	mConfiguratorWidget->setConfigurator(mModelThread->bodyConfigurator());
	handleBodyChanged();

	requestVoxelspace(0);
}


void MainWindow::drawBodyVoxels()
{
	if (mBodySpacesRenderEngine == 0) return;

	Body *body = mModelThread->body();
	if (body == 0) return;
	body->rasterize();

	mBodySpacesRenderEngine->setBody(body);
	mBodySpacesRenderEngine->genLists();

	mPrimaryRenderWidget->repaint();
}


void MainWindow::calculateWeights()
{
	Logger::statusMessage("calculating weights");
	if (mModelThread == 0)
		return;

	mModelThread->testIntersection();
}

// TODO: remove
void MainWindow::updateVoxelspace()
{
	if (!mVoxelspaceRenderEngine)
	{
		return;
	}

	mVoxelspaceRenderEngine->setVoxelspace(mModelThread->voxelspace());
}


void MainWindow::handleParticleFilterCreated()
{
	if(mModelThread == 0) return;
	//mProgressWidget->setObservedFilter(mModelThread->particleFiler());
	mProgressWidget->setModelThread(mModelThread);
}


void MainWindow::handleParticleFilterDestroyed()
{
	if(mModelThread == 0) return;
	//mProgressWidget->setObservedFilter(0);
	mProgressWidget->setModelThread(0);
}


void MainWindow::handleTrackerRunning()
{
	mPrimaryRenderWidget->setRepaintFrequency(25);
}


void MainWindow::handleTrackerSleeping()
{
	mPrimaryRenderWidget->setRepaintFrequency(0);
}


void MainWindow::handleBodyScaleChanged()
{
	// stop usage of body for rendering
	mPrimaryRenderWidget->enableRenderEngine(mBodyRenderEngine, false);

	// rebuild body
	mModelThread->rebuildBody();

	// tell widget that body changed
	handleBodyChanged();

	// display body again
	mPrimaryRenderWidget->enableRenderEngine(mBodyRenderEngine, true);
	mPrimaryRenderWidget->updateGL();
}


void MainWindow::handleBodyChanged()
{
	// exit, if no render engine available
	if(mBodyRenderEngine == 0) return;

	Body *body = mModelThread->body();
	if(body)
	{
		mBodyRenderEngine->setBody(body);
	} else
	{
		mBodyRenderEngine->unsetBody();
	}

	if(mModelThread->particleFiler())
	{
		mHistoryWidget->setParticleStorage(mModelThread->particleFiler()->particleStorage());
	}

	AbstractBodyConfigurator *configurator = mModelThread->bodyConfigurator();
	if(configurator)
	{
	    mTrackerControl->partitionWidget->setBodyNodeTree(configurator->getBodyNodeTree());
	}
}


void MainWindow::handlePtcFileChanged()
{
	if(mReaderThread == 0) return;

	TRACE("*******************************************************************************************");
	mPlaybackControl->setNumFrames(mReaderThread->voxelspacesCount());
	mPlaybackControl->gotoFrame(0);
}


void MainWindow::initUi()
{
	setWindowTitle(trUtf8("Pose Estimation Workbench"));
	setWindowIcon(QIcon(":/icons/24/cylinder.png"));

	connect(actionAppClose, SIGNAL(triggered()), this, SLOT(close()));
	connect(actionProjectNew, SIGNAL(triggered()), this, SLOT(newProjectRequest()));
	connect(actionProjectOpen, SIGNAL(triggered()), this, SLOT(openProject()));
	connect(actionProjectClose, SIGNAL(triggered()), this, SLOT(closeProject()));
	connect(actionProjectSave, SIGNAL(triggered()), this, SLOT(saveProject()));
	connect(actionProjectSaveAs, SIGNAL(triggered()), this,
			SLOT(saveProjectAs()));
	connect(actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
	connect(actionPreferences, SIGNAL(triggered()), this,
			SLOT(showPreferences()));
	connect(actionLoggerToggle, SIGNAL(triggered()), this, SLOT(toggleLogger()));
	connect(actionFullScreen, SIGNAL(triggered()), this, SLOT(toggleFullscreen()));

	connect(this, SIGNAL(projectClosed()), this, SLOT(updateWindowTitle()));
	connect(this, SIGNAL(projectOpened()), this, SLOT(updateWindowTitle()));
	connect(this, SIGNAL(projectClosed()), this, SLOT(updateWindowState()));
	connect(this, SIGNAL(projectOpened()), this, SLOT(updateWindowState()));
	connect(this, SIGNAL(projectModified()), this, SLOT(updateWindowState()));

	connect(this, SIGNAL(projectClosed()), this, SLOT(updateMdiWindowState()));
	connect(this, SIGNAL(projectOpened()), this, SLOT(updateMdiWindowState()));
	connect(this, SIGNAL(projectModified()), this, SLOT(updateMdiWindowState()));

	initLogger();
	initRenderWidgets();
	initSidebars();
	createConfiguratorWidget();
	//initMatlabModelController();

	mProgressWidget = new TrackerProgressWidget(this);
	statusbar->addWidget(mProgressWidget);

	mPlaybackControl = new QPlaybackControl(this);
	mPlaybackControl->setWindowTitle(trUtf8("Playback Control"));
	mPlaybackControl->setMaximumHeight(80);
	mdiArea->addSubWindow(mPlaybackControl, Qt::CustomizeWindowHint
			| Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::Tool);

	mTrackerControl = new TrackerControlWidget(this);
	mTrackerControl->setWindowTitle(trUtf8("Tracker Settings"));
	mdiArea->addSubWindow(mTrackerControl, Qt::CustomizeWindowHint
			| Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::Tool);

	connect(mTrackerControl, SIGNAL(rasterizeRequested()), this,
			SLOT(drawBodyVoxels()));
	connect(mTrackerControl, SIGNAL(weightingRequested()), this,
			SLOT(calculateWeights()));

	mHistoryWidget = new AnnealedParticleFilterHistoryWidget(this);
	mHistoryWidget->setWindowTitle(trUtf8("Tracker History"));
	mdiArea->addSubWindow(mHistoryWidget, Qt::CustomizeWindowHint
			| Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::Tool);

	loadWindowStates();
	createMdiMenu();
	toggleLogger();
	projectClosed();
}


void MainWindow::initLogger()
{
	Logger::getInstanceOf()->addMessageWriter(messageWidget);
	Logger::statusMessage("logger successfully initialized.");
}


void MainWindow::initRenderWidgets()
{
	if (mPrimaryRenderWidget)
		return;
	mPrimaryRenderWidget = new GLRenderWidget(this);
	mPrimaryRenderWidget->setWindowTitle("Primary Preview Window");
	mPrimaryRenderWidget->setWindowIcon(QIcon(":/icons/24/3d.png"));
	mPrimaryRenderWidget->enableInvertedBackground(true);

	connect(actionSaveScreenshot, SIGNAL(triggered()), mPrimaryRenderWidget, SLOT(saveFrameBuffer()));

	mdiArea->addSubWindow(mPrimaryRenderWidget, Qt::CustomizeWindowHint
			| Qt::WindowTitleHint | Qt::WindowMaximizeButtonHint
			| Qt::WindowMinMaxButtonsHint | Qt::WindowMinimizeButtonHint
			| Qt::Tool);
	mPrimaryRenderWidget->resize(640, 480);

	menuRendering->addMenu(mPrimaryRenderWidget->contextMenu());
}


void MainWindow::initRenderEngines()
{
	const double xsize = 300;
	//const double ysize = 300;
	const double zsize = 300;
	const double numGridLines = 8;

	//GridRenderEngine *ge = new GridRenderEngine(xsize, ysize, zsize, xsize
	//		/ numGridLines, ysize / numGridLines, zsize / numGridLines);
	//mPrimaryRenderWidget->addRenderEngine(ge);

	GroundRenderEngine *ge = new GroundRenderEngine(xsize, zsize, xsize / numGridLines, zsize / numGridLines);
	mPrimaryRenderWidget->addRenderEngine(ge);

	CoordAxisRenderEngine *ce = new CoordAxisRenderEngine(20, 1);
	mPrimaryRenderWidget->addRenderEngine(ce);

	mVoxelspaceRenderEngine = new VoxelspaceRenderEngine<VoxelValueExt> ();
	mPrimaryRenderWidget->addRenderEngine(mVoxelspaceRenderEngine);
}


void MainWindow::createConfiguratorWidget()
{
	mConfiguratorWidget = new ConfiguratorWidget(this);
	mConfiguratorWidget->setWindowTitle(trUtf8("Body Configurator Settings"));

	if(mModelThread)
	{
		connect(mConfiguratorWidget, SIGNAL(bodyScaleChanged(double)),
			this, SLOT(handleBodyScaleChanged()));
	} else
	{
	}

	mdiArea->addSubWindow(mConfiguratorWidget, Qt::CustomizeWindowHint
			| Qt::WindowTitleHint | Qt::WindowMaximizeButtonHint
			| Qt::WindowMinMaxButtonsHint | Qt::WindowMinimizeButtonHint
			| Qt::Tool);
}


void MainWindow::deleteConfiguratorWidget()
{

}


void MainWindow::initSidebars()
{
	leftFrame->hide();
	mBodyConfiguratorWidget = new BodyConfiguratorWidget(this);
	//connect(mConfiguratorWidget, SIGNAL(bodyScaleChanged(double)), this, SLOT(handleBodyScaleChanged()));

	if (!rightFrame->layout())
	{
		rightFrame->setLayout(new QGridLayout());
	}

	rightFrame->layout()->setSpacing(0);
	rightFrame->layout()->setMargin(0);
	rightFrame->layout()->addWidget(mBodyConfiguratorWidget);
}

//void MainWindow::addMatlabModelController()
//{
//	MatlabControlWidget* matlabControlWidget = new MatlabControlWidget(this);
//	matlabControlWidget->setWindowTitle("matlab model controller");
//	mdiArea->addSubWindow(matlabControlWidget, Qt::CustomizeWindowHint
//			| Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::Tool);
//
////	connect(matlabControlWidget, SIGNAL(requestConnect(QString)), this,
////			SLOT(startProjectThreads()));
////	connect(this, SIGNAL(matlabModelLoaded()), matlabControlWidget,
////			SLOT(setConnected()));
////	connect(this, SIGNAL(matlabConnectionClosed()), matlabControlWidget,
////			SLOT(setDisconnected()));
//}
//
//void MainWindow::removeMatlabModelController()
//{
//	MatlabControlWidget* matlabControlWidget = mdiArea->findChild<MatlabControlWidget*>();
//	if(matlabControlWidget)
//	{
//		mdiArea->removeSubWindow(matlabControlWidget);
//		matlabControlWidget->close();
//		delete matlabControlWidget;
//	}
//}


void MainWindow::saveWindowStates()
{
	QList<QMdiSubWindow*> wins = mdiArea->subWindowList();
	QSettings settings(QApplication::organizationName(),
			QApplication::applicationName());

	for (int i = 0; i < wins.size(); i++)
	{
		QMdiSubWindow* win = wins.at(i);
		QString name = win->windowTitle();
		QPoint pos = win->pos();
		QSize size = win->size();

		settings.setValue("windows/" + name + "/pos", pos);
		settings.setValue("windows/" + name + "/size", size);
	}

	QString name = this->windowTitle();
	QPoint pos = this->pos();
	QSize size = this->size();

	settings.setValue("windows/main/pos", pos);
	settings.setValue("windows/main/size", size);

}

void MainWindow::loadWindowStates()
{
	QList<QMdiSubWindow*> wins = mdiArea->subWindowList();
	QSettings settings(QApplication::organizationName(),
			QApplication::applicationName());

	for (int i = 0; i < wins.size(); i++)
	{
		QMdiSubWindow* win = wins.at(i);
		QString name = win->windowTitle();
		QPoint pos = settings.value("windows/" + name + "/pos", win->pos()).toPoint();
		QSize size = settings.value("windows/" + name + "/size", win->size()).toSize();

		win->move(pos);
		win->resize(size);
	}

	QString name = this->windowTitle();
	QPoint pos = settings.value("windows/main/pos", this->pos()).toPoint();
	QSize size = settings.value("windows/main/size", this->size()).toSize();

	move(pos);
	resize(size);
}


void MainWindow::createMdiMenu()
{
	actionPreMdi = new QAction(trUtf8("previous window"), this);
	actionNextMdi = new QAction(trUtf8("next window"), this);
	actionTileMdi = new QAction(trUtf8("tile windows"), this);
	actionCascadeMdi = new QAction(trUtf8("cascade windows"), this);

	connect(actionPreMdi, SIGNAL(triggered()), mdiArea,
			SLOT(activatePreviousSubWindow()));
	connect(actionNextMdi, SIGNAL(triggered()), mdiArea,
			SLOT(activateNextSubWindow()));
	connect(actionTileMdi, SIGNAL(triggered()), mdiArea, SLOT(tileSubWindows()));
	connect(actionCascadeMdi, SIGNAL(triggered()), mdiArea,
			SLOT(cascadeSubWindows()));

	updateMdiMenu();
}


void MainWindow::updateMdiMenu()
{
	menu_Windows->clear();
	menu_Windows->addAction(actionPreMdi);
	menu_Windows->addAction(actionNextMdi);
	menu_Windows->addSeparator();

	menu_Windows->addAction(actionTileMdi);
	menu_Windows->addAction(actionCascadeMdi);
	menu_Windows->addSeparator();

	QList<QMdiSubWindow *> windows = mdiArea->subWindowList();

	for (int i = 0; i < windows.size(); ++i)
	{
		QMdiSubWindow *window = windows.at(i);
		QString title = QString::number(i + 1);
		title.append(". ");
		title.append(window->windowTitle());
		QAction *action = menu_Windows->addAction(title);
		connect(action, SIGNAL(triggered()), window, SLOT(setFocus()));
	}
}


void MainWindow::updateMdiWindowState()
{
	// set to default state
	int state = QWombatProject::projectClosed;

	if(QGlobalState::instance()->currentProject != 0)
	{
		state = QWombatProject::projectOpened;
	}

	if(state == QWombatProject::projectClosed)
	{
		mPrimaryRenderWidget->setEnabled(false);
		mPlaybackControl->setEnabled(false);
		mTrackerControl->setEnabled(false);
		mConfiguratorWidget->setEnabled(false);
	}

	if((state == QWombatProject::projectOpened) |
	   (state == QWombatProject::projectModified))
	{
		mPrimaryRenderWidget->setEnabled(true);
		mPlaybackControl->setEnabled(true);
		mTrackerControl->setEnabled(true);
		mConfiguratorWidget->setEnabled(true);
	}

	if(state | QWombatProject::projectModified)
	{
	}

}

void MainWindow::handleVoxelspaceLoaded(size_t _voxelspaceIndex)
//void MainWindow::handleVoxelspaceLoaded(size_t)
{
	// get pointer to current voxelspace
	Voxelspace<VoxelValueExt> *space = mReaderThread->voxelspace();
	if(space)
	{
		mVoxelspaceRenderEngine->setVoxelspace(space);
		mPrimaryRenderWidget->updateGL();
		mModelThread->setVoxelspace(*space, _voxelspaceIndex);
	} else
	{
		QMessageBox::critical(this, "voxelspace loading", "loading of voxelspace failed, file broken");
	}
}


void MainWindow::requestVoxelspace(size_t _voxelspaceIndex)
{
	mReaderThread->readVoxelspace(_voxelspaceIndex);
}


void MainWindow::closeEvent(QCloseEvent *_event)
{

	int button = QMessageBox::question(this, trUtf8("close MyPET"), trUtf8(
			"are you shure, that you want to close this application?"),
			QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

	if (button == QMessageBox::Yes)
	{
		_event->accept();
	}
	else
	{
		_event->ignore();
	}
}

