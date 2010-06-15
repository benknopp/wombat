/*
 * AbstractRenderEngine.h
 *
 *  Created on: 17.11.2009
 *      Author: bknopp
 */

#ifndef ABSTRACTRENDERENGINE_H_
#define ABSTRACTRENDERENGINE_H_

#include <qgl.h>
#include <QString>
#include <QMutex>
#include <wombat/basetypes.h>

namespace wombat
{

/*!
 * \brief base-class for all renderengines, which could be added to \see GLRenderWidget
 */
class AbstractRenderEngine
{
public:
	//EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	AbstractRenderEngine();
	virtual ~AbstractRenderEngine();

	virtual void paintGL() = 0;
	virtual void initializeGL() = 0;
	virtual void releaseGL() = 0;

	QString name() const
	{
		return mName;
	}

	void setName(const QString &_name)
	{
		mName = _name;
	}

	void setScale(double _scale)
	{
		mScale = _scale;
	}
	double scale() const
	{
		return mScale;
	}

	void paintMetaGL();

	AxisAlignedBoundingBox bbox;
	Pose pose;
	QMutex mutex;
protected:
	QString mName;
	GLdouble mScale;

};

}

#endif /* ABSTRACTRENDERENGINE_H_ */
