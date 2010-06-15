/*
 * GLRenderWidget.cpp
 *
 *  Created on: 17.11.2009
 *      Author: bknopp
 */

#include "GLRenderWidget.h"
#include "AbstractRenderEngine.h"

#include <QtGui>
#include <QtOpenGL>

#include <math.h>
#include <limits.h>
#include <algorithm>

#include <wombat/helpers.h>

namespace wombat {

GLdouble max(GLdouble a, GLdouble b, GLdouble c)
{
	GLdouble m = a;
	if(b>m) m = b;
	if(c>m) m = c;
	return m;
}

GLdouble min(GLdouble a, GLdouble b, GLdouble c)
{
	GLdouble m = a;
	if(b<m) m = b;
	if(c<m) m = c;
	return m;
}


GLRenderWidget::GLRenderWidget(QWidget *_parent, const QGLWidget *_shareWidget,	Qt::WindowFlags _flags)
: QGLWidget(_parent, _shareWidget, _flags), mPauseTexture(0), mPausePlayback(false)
{
	setFocusPolicy(Qt::WheelFocus);
	createContextMenu();
	setMinimumSize(100,100);
	setBackgroundRole(QPalette::Dark);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	init();
}

GLRenderWidget::~GLRenderWidget()
{
	releaseGL();
}


void GLRenderWidget::addRenderEngine(AbstractRenderEngine *_engine)
{
	_engine->initializeGL();
	mRenderEngines.push_back(_engine);
	mRenderEnginesActive.push_back(_engine);
	updateRenderEngines();
	setupView();
	repaint();
}

int GLRenderWidget::numRenderEngines() const
{
	return mRenderEngines.size();
}

AbstractRenderEngine* GLRenderWidget::renderEngine(unsigned _id) const
{
	if(_id < mRenderEngines.size())
	{
		return mRenderEngines.at(_id);
	}
	return 0;
}

bool GLRenderWidget::removeRenderEngine(const AbstractRenderEngine *_engine)
{
	bool state = true;
	typedef std::vector<AbstractRenderEngine*>::iterator itType;

	itType reIt = std::find(mRenderEngines.begin(), mRenderEngines.end(), _engine);
	itType reActIt = std::find(mRenderEnginesActive.begin(), mRenderEnginesActive.end(), _engine);

	if(reIt != mRenderEngines.end())
	{
		mRenderEngines.erase(reIt);
	} else
	{
		state = false;
	}

	if(reActIt != mRenderEnginesActive.end())
	{
		mRenderEnginesActive.erase(reActIt);
	} else
	{
		state = false;
	}

	updateRenderEngines();
	return state;
}


bool GLRenderWidget::removeRenderEngine(unsigned _id)
{
	if(_id >= mRenderEngines.size()) return false;
	return removeRenderEngine(mRenderEngines.at(_id));
}


bool GLRenderWidget::enableRenderEngine(AbstractRenderEngine *_engine, bool _state)
{

	if(_state)
	{
		mRenderEnginesActive.push_back(_engine);
	} else
	{
		typedef std::vector<AbstractRenderEngine*>::iterator itType;
		itType reActIt = std::find(mRenderEnginesActive.begin(), mRenderEnginesActive.end(), _engine);
		if(reActIt != mRenderEnginesActive.end())
		{
			mRenderEnginesActive.erase(reActIt);
		} else
		{
			return false;
		}
	}
	return true;
}

bool GLRenderWidget::enableRenderEngine(unsigned _id, bool _state)
{
	if(_id >= mRenderEngines.size()) return false;
	return enableRenderEngine(mRenderEngines.at(_id), _state);
}

void GLRenderWidget::setWireframe(bool _state)
{
	mActionWireframe->setChecked(_state);
	setupView();
}


bool GLRenderWidget::wireframe() const
{
	return mActionWireframe->isChecked();
}


void GLRenderWidget::enableShowMeta(bool _state)
{
	mActionShowMeta->setChecked(_state);
	setupView();
}


bool GLRenderWidget::showMeta() const
{
	return mActionShowMeta->isChecked();
}


void GLRenderWidget::enableInvertedBackground(bool _state)
{
	mActionInvertBackground->setChecked(_state);
	setupView();
}


bool GLRenderWidget::invertedBackground() const
{
	return mActionInvertBackground->isChecked();
}

void GLRenderWidget::setRepaintFrequency(double _framesPerSecond)
{
	if(_framesPerSecond <= 0)
	{
		mRepaintTimer.stop();
		return;
	}

	const double msecs = 1000 / _framesPerSecond;
	mRepaintTimer.setInterval(msecs);
	mRepaintTimer.start();

}

void GLRenderWidget::setupView()
{
	double aspectRatio = (double) width() / (double) height();

	glMatrixMode(GL_PROJECTION); // manipulate projection matrix
	{
		glLoadIdentity();

		GLdouble minx, maxx, miny, maxy, minz, maxz;
		if(mSpace.isValid)
		{
			GLdouble s = sqrt(2);
			minz = mSpace.maxZ*-s;
			maxz = mSpace.maxZ*s;

			minx = mSpace.minX*s;
			maxx = mSpace.maxX*s;
			miny = mSpace.minY*s;
			maxy = mSpace.maxY*s;
		} else
		{
			minx = -80;
			maxx = 80;
			miny = -80;
			maxy = 80;
			minz = -80;
			maxz = 80;
		}

		//
		if(mState.equalScale)
		{
			GLdouble tmp1 = max(maxx, maxy, maxz);
			GLdouble tmp2 = min(minx, miny, minz);

			maxx = tmp1;
			maxy = tmp1;
			maxz = tmp1;

			minx = tmp2;
			miny = tmp2;
			minz = tmp2;
		}

		minz *= 5;
		maxz *= 5;


		if(aspectRatio > 1.0)
		{
			// width is greater than height
			minx *= aspectRatio;
			maxx *= aspectRatio;
		} else
		{
			miny *= aspectRatio;
			maxy *= aspectRatio;
		}

		glOrtho(minx, maxx, miny, maxy, minz, maxz);

		if(!mPausePlayback)
		{
			glRotatef(mCam.xAngle, 1, 0, 0);
			glRotatef(mCam.yAngle, 0, 1, 0);
			glTranslatef(mCam.x, mCam.y, mCam.z);
		}
	}

	toggleBackgroundColor(mActionInvertBackground->isChecked());
}


void GLRenderWidget::createContextMenu()
{
	mContextMenu = new QMenu("Rendering", this);

	QMenu *openglMenu = new QMenu(tr("OpenGL settings"));
	mActionWireframe = new QAction("wireframe-mode",this);
	mActionWireframe->setCheckable(true);
	connect(mActionWireframe, SIGNAL(toggled(bool)), this, SLOT(toggleWireframe(bool)));

	mActionShowMeta = new QAction("show voxelspace meta", this);
	mActionShowMeta->setCheckable(true);
	connect(mActionShowMeta, SIGNAL(toggled(bool)), this, SLOT(toggleShowMeta(bool)));

	mActionInvertBackground = new QAction("invert background", this);
	mActionInvertBackground->setCheckable(true);
	connect(mActionInvertBackground, SIGNAL(toggled(bool)), this, SLOT(toggleBackgroundColor(bool)));

	mGrabBufferAction = new QAction(QIcon(":/icons/24/camera-video.png"), trUtf8("grab framebuffer"), this);
	connect(mGrabBufferAction, SIGNAL(triggered()), this, SLOT(saveFrameBuffer()));
	mContextMenu->addAction(mGrabBufferAction);

	mPauseAction = new QAction(QIcon(":/icons/24/media-playback-pause.png"), trUtf8("pause rendering"), this);
	mPauseAction->setCheckable(true);
	connect(mPauseAction, SIGNAL(triggered()), this, SLOT(togglePause()));
	mContextMenu->addAction(mPauseAction);

	openglMenu->addAction(mActionWireframe);
	openglMenu->addAction(mActionShowMeta);
	openglMenu->addAction(mActionInvertBackground);

	// ************************** RENDERING ************************************
	mLowShadingAction  = new QAction("low quality", this);
	mLowShadingAction->setCheckable(true);
	connect(mLowShadingAction, SIGNAL(triggered()), this, SLOT(setLowQualityRendering()));

	mMediumShadingAction  = new QAction("medium quality", this);
	mMediumShadingAction->setCheckable(true);
	connect(mMediumShadingAction, SIGNAL(triggered()), this, SLOT(setMediumQualityRendering()));

	mHighShadingAction  = new QAction("high quality", this);
	mHighShadingAction->setCheckable(true);
	connect(mHighShadingAction, SIGNAL(triggered()), this, SLOT(setHighQualityRendering()));

	QActionGroup *qualityGroup = new QActionGroup(this);
	qualityGroup->addAction(mLowShadingAction);
	qualityGroup->addAction(mMediumShadingAction);
	qualityGroup->addAction(mHighShadingAction);

	openglMenu->addSeparator()->setText(trUtf8("quality"));
	openglMenu->addAction(mLowShadingAction);
	openglMenu->addAction(mMediumShadingAction);
	openglMenu->addAction(mHighShadingAction);
	openglMenu->addSeparator();

	mHighShadingAction->setChecked(true);
	//*************************************************************************
	mCamerasMenu = new QMenu(tr("Viewpoints"));
	mLightingsMenu = new QMenu(tr("Lightings"));
	mEnginesMenu = new QMenu(tr("render engines"));

	mContextMenu->addMenu(openglMenu);
	mContextMenu->addMenu(mCamerasMenu);
	mContextMenu->addMenu(mLightingsMenu);
	mContextMenu->addMenu(mEnginesMenu);

}

void GLRenderWidget::toggleRenderEngines(){

	QList<QAction*> actions = mEnginesMenu->actions();

	mRenderEnginesActive.clear();
	unsigned count = 0;

	for(QList<QAction*>::iterator it = actions.begin(); it != actions.end(); it++)
	{
		if((*it)->isChecked())
		{
			mRenderEnginesActive.push_back(mRenderEngines.at(count));
		}
		count++;
	}
}


void GLRenderWidget::saveFrameBuffer()
{
	QSettings settings(QApplication::organizationName(), QApplication::applicationName());
	QString dirname = settings.value("general/lastDirName", QApplication::applicationDirPath()).toString();
	QDir dir;

	QImage image = this->grabFrameBuffer(true);
	QString filename = QFileDialog::getSaveFileName(this, trUtf8("save image"), dir.absoluteFilePath(dirname), trUtf8("Images (*.png *.jpg *.tiff *.bmp)"));

	if(filename.isEmpty()) return;
	image.save(filename);

	settings.setValue("general/lastDirName", dir.absoluteFilePath(filename));
}


void GLRenderWidget::pausePlayback(bool _pause)
{
	if(_pause)
	{
		mPausePlayback = true;
	} else
	{
		mPausePlayback = false;
	}

}


void GLRenderWidget::toggleWireframe(bool _state)
{
	mActionWireframe->setChecked(_state);
	repaint();
}


void GLRenderWidget::toggleBackgroundColor(bool _state)
{
	mActionInvertBackground->setChecked(_state);

	if(mActionInvertBackground->isChecked())
	{
		glClearColor(1, 1, 1, 0);
	} else
	{
		glClearColor(0, 0, 0, 0);
	}

	repaint();
}


void GLRenderWidget::toggleShowMeta(bool _state)
{
	mActionShowMeta->setChecked(_state);
	repaint();
}

void GLRenderWidget::togglePause()
{
	pausePlayback(mPauseAction->isChecked());
}


void GLRenderWidget::setLowQualityRendering()
{
	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);	// Enable Material color tracking
	glShadeModel( GL_SMOOTH );

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

void GLRenderWidget::setMediumQualityRendering()
{
//	GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };
//	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//	GLfloat light_position[] = { 100.0, 100.0, 100.0, 0.0 };
//
//	glClearColor (0.0, 0.0, 0.0, 0.0);
//	glShadeModel (GL_SMOOTH);
//	glEnable(GL_DEPTH_TEST);
//	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseMaterial);
//	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
//	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 25.0);
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//
//	glColorMaterial(GL_FRONT, GL_DIFFUSE);
//	glEnable(GL_COLOR_MATERIAL);

//	glEnable(GL_COLOR_MATERIAL);	// Enable Material color tracking
//	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
//
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//	glEnable(GL_BLEND);
//
//	glShadeModel( GL_SMOOTH );
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
//	GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
//	GLfloat mat_ambient[] = { 0.6, 0.6, 0.6, 1.0 };
//	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//
//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,	mat_ambient);
//	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,	mat_diffuse);
//	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//
//	GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
//	GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
//	GLfloat light_specular[] = { 0.6, 0.6, 0.6, 1.0 };
//	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
//
//	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
}

void GLRenderWidget::setHighQualityRendering()
{
	GLfloat light_ambient[]={0.5, 0.5, 0.5, 1.0};
	GLfloat light_diffuse[]={1.0, 1.0, 1.0, 1.0};
	GLfloat light_specular[]={0.0, 0.0, 0.0, 1.0};
	GLfloat light_position[] = { 100.0, 100.0, 100.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	GLfloat mat_specular[]={0.0, 0.0, 0.0, 1.0};
	GLfloat mat_diffuse[]={0.8, 0.6, 0.4, 1.0};
	GLfloat mat_ambient[]={0.8, 0.6, 0.4, 1.0};
	GLfloat mat_shininess={20.0};
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	glShadeModel(GL_SMOOTH); /*enable smooth shading */
	glEnable(GL_LIGHTING); /* enable lighting */
	glEnable(GL_LIGHT0); /* enable light 0 */
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

}

void GLRenderWidget::init()
{
	mSpace.isValid = false;
	mState.scale = 1.0;
	mState.equalScale = true;
	mState.scaleMin = 0.1;
	mState.scaleMax = 10.0;
	mState.scaleStep = 0.25;

	connect(&mRepaintTimer, SIGNAL(timeout()), this, SLOT(updateGL()));

	mFont = QFont("Fixed", 12, QFont::Bold);

}

void GLRenderWidget::updateRenderEngines()
{
	GLdouble minX=std::numeric_limits<double>::max(),
			 minY=std::numeric_limits<double>::max(),
			 minZ=std::numeric_limits<double>::max();
	GLdouble maxX=std::numeric_limits<double>::min(),
			 maxY=std::numeric_limits<double>::min(),
			 maxZ=std::numeric_limits<double>::min();

	GLdouble x1, x2, y1, y2, z1, z2;
	mEnginesMenu->clear();

	for(std::vector<AbstractRenderEngine*>::iterator it = mRenderEngines.begin();
			it != mRenderEngines.end(); it++)
	{
		//mEnginesMenu->addAction((*it)->name());
		QAction *action = new QAction((*it)->name(), this);
		action->setCheckable(true);
		action->setChecked(true);
		mEnginesMenu->addAction(action);
		connect(action, SIGNAL(changed()), this, SLOT(toggleRenderEngines()));
	}

	for(std::vector<AbstractRenderEngine*>::iterator it = mRenderEnginesActive.begin();
			it != mRenderEnginesActive.end(); it++)
	{

		Vector3d min = (*it)->bbox.min();
		Vector3d max = (*it)->bbox.max();
		x1 = min.x();
		y1 = min.y();
		z1 = min.z();
		x2 = max.x();
		y2 = max.y();
		z2 = max.z();

		if(x1 < minX) minX = x1;
		if(y1 < minY) minY = y1;
		if(z1 < minZ) minZ = z1;
		if(x2 > maxX) maxX = x2;
		if(y2 > maxY) maxY = y2;
		if(z2 > maxZ) maxZ = z2;
	}

	mSpace.minX = minX;
	mSpace.minY = minY;
	mSpace.minZ = minZ;
	mSpace.maxX = maxX;
	mSpace.maxY = maxY;
	mSpace.maxZ = maxZ;
	mSpace.isValid = true;

	mCam.stepSizeX = (mSpace.maxX - mSpace.minX) / 20;
	mCam.stepSizeY = (mSpace.maxY - mSpace.minY) / 20;
	mCam.stepSizeZ = (mSpace.maxZ - mSpace.minZ) / 20;

//	GLfloat light_position[] = {0.5* (mSpace.minX + mSpace.maxX),
//			mSpace.maxY,
//			0.5* (mSpace.minZ + mSpace.maxZ) };
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}


void GLRenderWidget::resizeGL(int _width, int _height)
{
	glViewport(0, 0, (GLint)_width, (GLint)_height);
	setupView();
}


void GLRenderWidget::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(mPausePlayback)
	{
		showPauseTexture();
		return;
	}

	// set wireframe mode
	if(mActionWireframe->isChecked())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glScaled(mState.scale, mState.scale, mState.scale);

	if(mRenderEnginesActive.size())
	{
		// render engines
		for(std::vector<AbstractRenderEngine*>::iterator it = mRenderEnginesActive.begin();
				it != mRenderEnginesActive.end(); it++)
		{
			// add new matrix to stack, to avoid side effects on other renderengines
			glPushMatrix();
			{
				(*it)->paintGL();
				if(mActionShowMeta->isChecked()) (*it)->paintMetaGL();
			}
			glPopMatrix();
		}
	} else
	{
		glDisable(GL_LIGHTING);
		glRotatef(-mCam.yAngle, 0, 1, 0);
		glRotatef(-mCam.xAngle, 1, 0, 0);
		QRectF r(-40.0, -40.0, 80.0, 80.0);
		drawTexture(r, mDefaultTexture);
		glEnable(GL_LIGHTING);
	}


	paintTextInfo();
}


void GLRenderWidget::paintTextInfo()
{
	int x = width() - 200;
	int y = height() - 50;

	QString text1 = "Position: [";
	text1.append(QString::number(mCam.x));
	text1.append("; ");
	text1.append(QString::number(mCam.y));
	text1.append("; ");
	text1.append(QString::number(mCam.z));
	text1.append("]");

	QString text2 = "Zoom: ";
	text2.append(QString::number(mState.scale * 100));
	text2.append(" %");

	glColor4d(0.5, 0.5, 0.5, 0.8);
	renderText(x, y, text1, mFont);
	renderText(x, y+12, text2, mFont);

	if(mActionInvertBackground->isChecked())
	{
		glColor4d(0.2, 0.2, 0.2, 0.8);
	} else
	{
		glColor4d(0.8, 0.8, 0.8, 0.8);
	}

	renderText(x+1, y+1, text1, mFont);
	renderText(x+1, y+13, text2, mFont);

	glColor4d(1, 1, 1, 1);
}


void GLRenderWidget::initializeGL()
{
	//TRACE("initialize GL");

	mCam.x  = 0; mCam.y  = 0; mCam.z  = 0;
	mCam.xUp = 0; mCam.yUp = 1;  mCam.zUp = 0;
	mCam.xAt = 0; mCam.yAt = 0; mCam.zAt = -1;
	mCam.xAngle = 30;
	mCam.yAngle = 45;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//setLowQualityRendering();
	setHighQualityRendering();
	createDefaultTextures();
}


void GLRenderWidget::releaseGL()
{

}


void GLRenderWidget::mousePressEvent(QMouseEvent *_event)
{
	mLastMousePos = _event->pos();

	if(_event->buttons() & Qt::RightButton)
	{
		mContextMenu->popup( _event->globalPos() );
	}
}

void GLRenderWidget::mouseMoveEvent(QMouseEvent *_event)
{
	if(_event->buttons() & Qt::LeftButton)
	{
		QPoint delta = _event->pos() - mLastMousePos;
		mLastMousePos = _event->pos();

		// one degree is equal to one pixel
		mCam.yAngle += delta.x();
		mCam.xAngle += delta.y();
	}

	if(_event->buttons() & Qt::MidButton)
	{
		QPoint delta = _event->pos() - mLastMousePos;
		mLastMousePos = _event->pos();

		mCam.x += (delta.x() * mCam.stepSizeX * 0.5);
		mCam.y -= (delta.y() * mCam.stepSizeY * 0.5);
	}

	setupView();
	repaint();
}

void GLRenderWidget::keyPressEvent(QKeyEvent *_event)
{
	if(mPausePlayback) return;

	switch(_event->key())
	{
	case Qt::Key_Left:
		mCam.x -= mCam.stepSizeX;
		break;
	case Qt::Key_Right:
		mCam.x += mCam.stepSizeX;
		break;
	case Qt::Key_Up:
		mCam.y -= mCam.stepSizeY;
		break;
	case Qt::Key_Down:
		mCam.y += mCam.stepSizeY;
		break;
	case Qt::Key_Plus:
		if (mState.scale <= mState.scaleMax) mState.scale += mState.scaleStep;
		break;
	case Qt::Key_Minus:
		if (mState.scale >= mState.scaleMin) mState.scale -= mState.scaleStep;
		break;
	default:
		//TRACE("nothing todo for:%i", _event->key());
		break;
	}

	setupView();
	repaint();
}

void GLRenderWidget::wheelEvent(QWheelEvent *_event)
{
	double delta = _event->delta();

	if(delta > 0)
	{
		if (mState.scale <= mState.scaleMax) mState.scale += mState.scaleStep;
	} else
	{
		if (mState.scale >= mState.scaleMin) mState.scale -= mState.scaleStep;
	}

	setupView();
	repaint();
}



void GLRenderWidget::createDefaultTextures()
{
	QImage orig(":/images/opengl_logo.jpg");
	QImage image = orig.mirrored(false, true);

	QImage pause(":/images/pause.png");

	mDefaultTexture = bindTexture(image);
	mPauseTexture = bindTexture(pause);
}


void GLRenderWidget::showPauseTexture()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	QRectF r(- width() / 2 , - height() / 2, width(), height());
	drawTexture(r, mPauseTexture);
}
}
