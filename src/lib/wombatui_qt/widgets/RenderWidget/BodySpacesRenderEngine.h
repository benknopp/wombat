/*
 * BodySpacesRenderEngine.h
 *
 *  Created on: 01.03.2010
 *      Author: bknopp
 */

#ifndef BODYSPACESRENDERENGINE_H_
#define BODYSPACESRENDERENGINE_H_

#include "AbstractRenderEngine.h"
#include <wombat/body.h>

namespace wombat
{

class BodySpacesRenderEngine: public wombat::AbstractRenderEngine
{
public:
	BodySpacesRenderEngine();
	virtual ~BodySpacesRenderEngine();

	void paintGL();
	void initializeGL();
	void releaseGL();

	void setBody(const Body* _body);
	const Body* body() const;

	void genLists();

	void setQuadSize(double _quadsize){mQuadSize = _quadsize;}
	double quadSize() const {return mQuadSize;}
protected:
	void clearDisplayLists();

	typedef std::pair<GLuint, const AbstractBodyPart*> BodyPartMeta;

	std::vector<BodyPartMeta> mBodyPartList;
	const Body* mBody;
	double mQuadSize;
};

}

#endif /* BODYSPACESRENDERENGINE_H_ */
