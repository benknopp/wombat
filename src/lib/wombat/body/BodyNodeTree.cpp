/*
 * BodyNodeTree.cpp
 *
 *  Created on: 04.04.2010
 *      Author: bknopp
 */

#include "BodyNodeTree.h"
#include <wombat/helpers.h>

namespace wombat
{

BodyNodeTree::BodyNodeTree()
	: root(0), mScaleFactor(1.0)
{

}

BodyNodeTree::~BodyNodeTree()
{

}

void BodyNodeTree::findRoot()
{
    for(std::vector<BodyPartNode>::iterator it =  partNodes.begin();
        it != partNodes.end(); it++)
    {
        if(isRoot(&(*it)))
        {
            root = &(*it);
        }
    }
}

void BodyNodeTree::scale(double _scaleFactor)
{
	const double oldScale = mScaleFactor;
	const double scale = _scaleFactor / oldScale;

	if (scale <= 0)
	{
		Logger::criticalErrorMessage("negative scale factor. aborting model scaling");
	}

	for(std::vector<BodyJointNode>::iterator jointIt = jointNodes.begin(); jointIt != jointNodes.end(); jointIt++)
	{
		// scale anchor translation point
		jointIt->anchorTranslation *= scale;
		// scale translation part of local transform matrix
		jointIt->localTransform.corner(Eigen::TopLeft, 3, 1) *= scale;
	}

	for(std::vector<BodyPartNode>::iterator partIt = partNodes.begin(); partIt != partNodes.end(); partIt++)
	{
		// scale size
		partIt->size *= scale;
		// scale translation
		partIt->t *= scale;
		// scale translation part of origin transformation
		partIt->originTransform.corner(Eigen::TopLeft, 3, 1) *= scale;
	}

	mScaleFactor = _scaleFactor;
}

double BodyNodeTree::scaleFactor()
{
	return mScaleFactor;
}

std::string BodyNodeTree::getIndexName(unsigned _index) const
{
	for(unsigned i=0; i < jointNodes.size(); i++)
	{
		for(unsigned k=0; k < jointNodes[i].indices.size(); k++)
		{
			if(jointNodes[i].indices[k] == _index)
			{
				std::string appendix;
				switch(jointNodes[i].indexFunctions[k])
				{
				default:
					appendix = "_unknown";
					break;

				case BodyJointNode::rx:
					appendix = "_rx";
					break;

				case BodyJointNode::ry:
					appendix = "_ry";
					break;

				case BodyJointNode::rz:
					appendix = "_rz";
					break;

				case BodyJointNode::tx:
					appendix = "_tx";
					break;

				case BodyJointNode::ty:
					appendix = "_ty";
					break;

				case BodyJointNode::tz:
					appendix = "_tz";
					break;
				}

				std::string result = jointNodes[i].name  + appendix;
				return result;
			}
		}
	}
	return "unknown";
}


std::ostream& operator<< (std::ostream& _out, const BodyNodeTree &_tree)
{
	std::string seperator, rootName;
	for(unsigned i=0; i< 80; i++) seperator += "=";

	_out << seperator << "\n";
	_out << "root-name:" << rootName << "\n";

	_out << seperator << "\n";
	_out <<"Joints:\n\n";

	for(unsigned i=0; i < _tree.jointNodes.size(); i++)
	{
		_out << _tree.jointNodes.at(i);
	}

	_out << seperator << "\n";
	_out <<"Parts:\n\n";

	for(unsigned i=0; i < _tree.partNodes.size(); i++)
	{
		_out << _tree.partNodes.at(i);
	}

	_out << seperator << "\n";
	_out <<"Degrees of freedom:\n\n";

	for(unsigned i=0; i < _tree.dofs.size(); i++)
	{
		_out << _tree.dofs.at(i);
	}

	return _out;
}

void printBodyNodeTree(const BodyNodeTree &_tree)
{
	std::cout << _tree << std::endl;
}


}
