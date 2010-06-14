#include "Body.h"
#include <wombat/helpers.h>

namespace wombat
{

    bool Body::configure(const BodyConfiguration &_configuration)
    {
        bool success = false;
        typedef std::vector<AbstractBodyPart*>::iterator BodyPartIt;

        if((_configuration.rotations.size() < mBodyParts.size()) | (_configuration.translations.size() < mBodyParts.size()))
        {
        	Logger::criticalErrorMessage("configuration vector to short. aborting body configuration.");
        	return success;
        }

        unsigned pos = 0;
        for(BodyPartIt it = mBodyParts.begin(); it != mBodyParts.end(); it++)
        {
        	(*it)->transform(_configuration.rotations[pos], _configuration.translations[pos]);
        	pos++;
        }

        return success;
    }


    const AbstractBodyPart& Body::bodyPart(size_t pos) const
    {
    	//if(pos >= mBodyParts.size())
    	return *(mBodyParts[pos]);
    }


    void Body::rasterize()
    {
        for(unsigned i=0; i  < mBodyParts.size(); i++)
        {
        	AbstractBodyPart *part = mBodyParts.at(i);
            part->rasterize();
            part->transform(part->rotation(), part->translation());
        }
    }

    bool Body::isRasterized() const
    {
    	bool result = true;
        for(unsigned i=0; i  < mBodyParts.size(); i++)
        {
            result = result & (mBodyParts.at(i)->voxelspace() != 0);
        }
        return result;
    }

    AbstractBodyPart* Body::bodyPart(const std::string &_name, bool *_found) const
    {
        if(_found) *_found = true;

        for(unsigned i=0; i < mBodyParts.size(); i++)
        {
            if(mBodyParts.at(i)->name == _name) return (mBodyParts.at(i));
        }
        if(_found) *_found = false;
        return (mBodyParts.at(mBodyParts.size()-1));
    }

    Body::Body()
    {
    	mBodyParts.clear();

    }


    Body::Body(const Body &_body)
    {
        mBodyParts = _body.mBodyParts;
    }


    Body::~Body()
    {

    }


    void readJointPositions(const Body &_body, std::vector<Vector3d> &_positions,
    		std::vector<std::string> &_names)
    {
    	_positions.clear();
    	_names.clear();

    	for(size_t i=0; i < _body.size(); i++)
    	{
    		Matrix4d m = Matrix4d::Identity();

    		m.corner(Eigen::TopLeft, 3, 3) =_body.bodyPart(i).rotation();
    		m.corner(Eigen::TopRight, 3, 1) = _body.bodyPart(i).translation();

    		Vector4d v;
    		v << 0, 0, 0, 1;

    		Vector4d vt = m * v;

    		if(vt.w())
    		{
    			vt = vt / vt.w();
    		} else
    		{
    			vt << 0, 0, 0, 1;
    		}
    		Vector3d position;
    		position << vt.x(), vt.y(), vt.z();
    		_positions.push_back(position);
    		_names.push_back(_body.bodyPart(i).partName());
    	}
    }


}


