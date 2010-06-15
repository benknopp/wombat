/*
 * GLRenderWidget.h
 *
 *  Created on: 17.11.2009
 *      Author: bknopp
 */

#ifndef GLRENDERWIDGET_H_
#define GLRENDERWIDGET_H_

#include <wombat/basetypes.h>

#include <GL/gl.h>
#include <vector>


#include <QGLWidget>
#include <QMenu>
#include <QAction>
#include <QMap>
#include <QTimer>

namespace wombat
{

// forwards
class AbstractRenderEngine;



/*!
 * \brief OpenGL based widget, which renders content provided via multiple render engines
 */
class GLRenderWidget : public QGLWidget{
		Q_OBJECT;
	public:
		GLRenderWidget(QWidget *_parent = 0, const QGLWidget *_shareWidget = 0,
				Qt::WindowFlags _flags = 0);
		virtual ~GLRenderWidget();

		/*!
		 * add a renderengine derived from AbstractRenderEngine to the current opengl-render-loop
		 */
		virtual void addRenderEngine(AbstractRenderEngine *_engine);

		/*!
		 * count currently registred renderengines
		 */
		virtual int numRenderEngines() const;

		/*!
		 * get pointer to the renderengine referenced by _id
		 */
		virtual AbstractRenderEngine* renderEngine(unsigned _id) const;

		/*!
		 * removes a render engine from the render queue, engine is NOT deleted
		 */
		virtual bool removeRenderEngine(const AbstractRenderEngine *_engine);
		virtual bool removeRenderEngine(unsigned _id);

		virtual bool enableRenderEngine(AbstractRenderEngine *_engine, bool _state = true);
		virtual bool enableRenderEngine(unsigned _id, bool _state = true);

		/*!
		 * show context menu to setup rendering parameters
		 */
		QMenu* contextMenu() const{return mContextMenu;}

		/*!
		 * toggle wireframe mode
		 */
		void setWireframe(bool _state);
		bool wireframe() const;

		void enableShowMeta(bool _state);
		bool showMeta() const;

		void enableInvertedBackground(bool _state);
		bool invertedBackground() const;

		void setRepaintFrequency(double _framesPerSecond);
	public slots:
		/**
		 * called to make some renderengines (in)visible
		 */
		void toggleRenderEngines();
		void saveFrameBuffer();

		void pausePlayback(bool _pause = true);

	protected slots:
		void toggleWireframe(bool _state);
		void toggleBackgroundColor(bool _state);
		void toggleShowMeta(bool _state);
		void togglePause();

		void setLowQualityRendering();
		void setMediumQualityRendering();
		void setHighQualityRendering();
	protected:
		void init();
		void updateRenderEngines();
		void setupView();
		void createContextMenu();

		// opengl stuff
		virtual void resizeGL(int _width, int _height);
		virtual void paintGL();
		virtual void paintTextInfo();
		virtual void initializeGL();
		void releaseGL();

		virtual void mousePressEvent(QMouseEvent *_event);
		virtual void mouseMoveEvent(QMouseEvent *_event);
		virtual void keyPressEvent(QKeyEvent *_event);
		virtual void wheelEvent(QWheelEvent *_event);

		void createDefaultTextures();
		void showPauseTexture();

		struct{
				GLdouble minX, maxX;
				GLdouble minY, maxY;
				GLdouble minZ, maxZ;
				bool isValid;
		} mSpace;

		struct{
				GLdouble x, y, z;
				GLdouble xAngle, yAngle;
				GLdouble xAt, yAt, zAt;
				GLdouble xUp, yUp, zUp;
				GLdouble stepSizeX, stepSizeY, stepSizeZ, AngleSize;

		} mCam;

		struct{
//				bool useWireframe;
//				bool showAdvancedMeta;
//				bool invertBackground;
				bool equalScale;
				GLdouble scale, scaleMin, scaleMax, scaleStep;
		} mState;

		QPoint mLastMousePos;
		QMenu *mContextMenu, *mEnginesMenu, *mCamerasMenu, *mLightingsMenu;
		QAction *mHighQualityAction, *mLowQualityAction, *mMediumQualityAction,
				*mGrabBufferAction, *mActionWireframe, *mActionShowMeta, *mActionInvertBackground,
				*mPauseAction, *mLowShadingAction, *mMediumShadingAction, *mHighShadingAction;
		std::vector<AbstractRenderEngine*> mRenderEngines;
		std::vector<AbstractRenderEngine*> mRenderEnginesActive;

		QMap<QString, Viewpoint> mViewpoints;
		GLuint mDefaultTexture;
		GLuint mPauseTexture;
		bool mPausePlayback;

		QTimer mRepaintTimer;
		QFont mFont;
};

}
#endif /* GLRENDERWIDGET_H_ */
