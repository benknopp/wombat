/*
 * NativeBodyConfigurator.cpp
 *
 *  Created on: 11.03.2010
 *      Author: bknopp
 */

#include "NativeBodyConfigurator.h"
#include <wombat/helpers.h>
#include <wombat/math.h>

namespace wombat
{


NativeBodyConfigurator::NativeBodyConfigurator()
	: mIsReady(false)
{

}


NativeBodyConfigurator::~NativeBodyConfigurator()
{
	delete mBodyNodeTree;
}


void NativeBodyConfigurator::addJoint(const JointInfo &_info)
{
	addJoint(_info.name, _info.parent, _info.parentAnchor, _info.childs, _info.indices,
			_info.indexFunc);
}


void NativeBodyConfigurator::addJoint(const std::string &_name,
			  const std::string &_parent,
			  const std::string &_parentAnchor,
			  const std::string &_childs,
			  const std::string &_indices,
			  const std::string &_indecFunc)
{
	JointInfo info;
	info.name = _name;
	info.parent = _parent;
	info.parentAnchor = _parentAnchor;
	info.childs = _childs;
	info.indices = _indices;
	info.indexFunc = _indecFunc;
	mJointInfoVec.push_back(info);
}


void NativeBodyConfigurator::addPart(const PartInfo &_info)
{
	addPart(_info.name, _info.parent, _info.childs, _info.sizes, _info.originTransform);
}


void NativeBodyConfigurator::addPart(const std::string &_name,
			  const std::string &_parent,
			  const std::string &_childs,
			  const std::string &_sizes,
			  const std::string &_originTransform)
{
	PartInfo info;
	info.name = _name;
	info.parent = _parent;
	info.childs = _childs;
	info.sizes = _sizes;
	info.originTransform = _originTransform;
	mPartInfoVec.push_back(info);
}


void NativeBodyConfigurator::addDof(const DofInfo &_info)
{
	addDof(_info.type, _info.values, _info.index);
}


void NativeBodyConfigurator::addDof(const std::string &_type,
			  const std::string &_values,
			  const std::string &_index)
{
	DofInfo info;
	info.type = _type;
	info.values = _values;
	info.index = _index;
	mDofInfoVec.push_back(info);
}


bool NativeBodyConfigurator::generate()
{
	if(mBodyNodeTree) return false; // can only be called once!
	mBodyNodeTree = new BodyNodeTree();
	std::vector<std::string> tokens;

	/**************************************************************************
	 * 									PARTS
	 **************************************************************************/
	for(unsigned i=0; i < mPartInfoVec.size(); i++)
	{
		PartInfo &part = mPartInfoVec[i];
		BodyPartNode node;
		// name
		node.name = part.name;

		// size
		Vector3d size;
		tokens.clear();
		tokens = splitString(part.sizes, ";");
		if(tokens.size() == 3)
		{
			size << atof(tokens[0].c_str()), atof(tokens[1].c_str()), atof(tokens[2].c_str());
		} else
		{
			size << 0,0,0;
			//std::cout << "insufficient sizes for " << node.name << "\n";
		}
		node.size = size;

		tokens.clear();
		tokens = splitString(part.originTransform, ";");
		if(tokens.size() == 3)
		{
			node.originTransform(0,3) = atof(tokens[0].c_str());
			node.originTransform(1,3) = atof(tokens[1].c_str());
			node.originTransform(2,3) = atof(tokens[2].c_str());
		}

		mBodyNodeTree->partNodes.push_back(node);

		if(node.name == "root")
		{
			mBodyNodeTree->root = &(mBodyNodeTree->partNodes[mBodyNodeTree->partNodes.size()-1]);
		}
	}
	// not! set so far: parent, child(s), rotation, translation

	/**************************************************************************
	 * 									JOINTS
	 **************************************************************************/
	for(unsigned i=0; i < mJointInfoVec.size(); i++)
	{
		JointInfo &info = mJointInfoVec[i];
		BodyJointNode node;

		node.name = info.name;

		BodyPartNode *parent = findBodyPart(mBodyNodeTree->partNodes, info.parent);
		if(parent)
		{
			node.parent = parent;
		} else
		{
			node.parent = 0;
		}

		tokens.clear();
		tokens = splitString(info.childs, ";");

		for(unsigned k=0; k < tokens.size(); k++)
		{
			std::string childName = tokens[k];
			BodyPartNode *child = findBodyPart(mBodyNodeTree->partNodes, childName);
			if(child) node.children.push_back(child);
		}

		tokens.clear();
		tokens = splitString(info.indices, ";");

		for(unsigned k=0; k < tokens.size(); k++)
		{
			node.indices.push_back(atoi(tokens[k].c_str()));
		}

		tokens.clear();
		tokens = splitString(info.indexFunc, ";");

		for(unsigned k=0; k < tokens.size(); k++)
		{
			std::string v = tokens[k];
			int val = 0;
			if(v == "rx") val = BodyJointNode::rx;
			if(v == "ry") val = BodyJointNode::ry;
			if(v == "rz") val = BodyJointNode::rz;
			if(v == "tx") val = BodyJointNode::tx;
			if(v == "ty") val = BodyJointNode::ty;
			if(v == "tz") val = BodyJointNode::tz;
			node.indexFunctions.push_back(val);
		}

		Vector3d trans;
		tokens.clear();
		tokens = splitString(info.parentAnchor, ";");
		if(tokens.size() == 3)
		{
			trans << atof(tokens[0].c_str()), atof(tokens[1].c_str()), atof(tokens[2].c_str());
		} else
		{
			trans << 0,0,0;
		}
		node.anchorTranslation = trans;

		mBodyNodeTree->jointNodes.push_back(node);
	}

	/**************************************************************************
	 * 									PARTS - 2nd lap
	 **************************************************************************/
	// iterate again over all bodyparts and set joint info
	for(unsigned i=0; i < mBodyNodeTree->partNodes.size(); i++)
	{
		BodyPartNode &node = mBodyNodeTree->partNodes[i];

		if(mPartInfoVec.size() > i)
		{
			std::string name = mPartInfoVec.at(i).parent;
			BodyJointNode *parent = findBodyJoint(mBodyNodeTree->jointNodes, name);

			if(parent)
			{
				node.parent = parent;
			} else
			{
				node.parent = 0;
			}
		} // name present

		std::vector<std::string> names = splitString(mPartInfoVec.at(i).childs, ";");
		for(unsigned k=0; k < names.size(); k++)
		{
			BodyJointNode *child = findBodyJoint(mBodyNodeTree->jointNodes, names[k]);
			if(child)
			{
				node.children.push_back(child);
			}
		}
	}
	// not! set so far: rotation, translation
	// not! used: origin_transform

	/*************************************************************************
	 *  	DEGRESS OF FREEDOM
	 *************************************************************************/
	for(unsigned i=0; i < mDofInfoVec.size(); i++)
	{
		DofInfo &info = mDofInfoVec[i];
		int index = atoi(info.index.c_str());
		DegreeOfFreedom dof;
		dof.name = mBodyNodeTree->getIndexName(index);

		dof.rangeType = DegreeOfFreedom::unlimitedRange; // set as default
		if(info.type == "limited") dof.rangeType = DegreeOfFreedom::limitedRange;
		if(info.type == "circular") dof.rangeType = DegreeOfFreedom::circularRange;

		tokens.clear();
		tokens = splitString(info.values, ";");

		if(tokens.size() == 1)
		{
			dof.init = atof(tokens[0].c_str());
		}

		if(tokens.size() == 3)
		{
			dof.min = atof(tokens[0].c_str());
			dof.init = atof(tokens[1].c_str());
			dof.max = atof(tokens[2].c_str());
		}

		dof.stateVecPosition = index;
		mBodyNodeTree->dofs.push_back(dof);
	}

	mBodyNodeTree->findRoot();

	createStateVectorAndConfiguration();
	updateJoints(*mBodyStateVector);
	updateParts();

	mIsReady = true;
	return true;
}


void NativeBodyConfigurator::updateJoints(const BodyStateVector &_vector)
{
	// itertate over all joints
	for(unsigned i=0; i < mBodyNodeTree->jointNodes.size(); i++)
	{
		// get reference to current
		BodyJointNode &node = mBodyNodeTree->jointNodes[i];

		// possible dofs
		double alpha=0, beta=0, gamma=0, value = 0;
		Vector3d trans = Vector3d::Zero();

		if(node.indices.size() != node.indexFunctions.size())
		{
			Logger::criticalErrorMessage("WARNING: number of indices does NOT match number of index functions");
		}

		// check all indices
		for(unsigned k=0; k < node.indices.size(); k++)
		{
			value = _vector[node.indices[k]];

			if(k < node.indexFunctions.size())
			{
				switch(node.indexFunctions[k])
				{
				default:
					break;
				case BodyJointNode::rx:
					alpha = value;
					break;
				case BodyJointNode::ry:
					beta = value;
					break;
				case BodyJointNode::rz:
					gamma = value;
					break;
				case BodyJointNode::tx:
					trans.x() = value;
					break;
				case BodyJointNode::ty:
					trans.y() = value;
					break;
				case BodyJointNode::tz:
					trans.z() = value;
					break;
				} // end switch
			} // end index ok
		} // end indices

		// rotate z,y,z (DIN 9300)
		Matrix4d m_rotate = rotateX(gamma) * rotateY(beta) * rotateZ(alpha);
		//Matrix4d m_rotate = rotateX(alpha) * rotateY(beta) * rotateZ(gamma);
		Matrix4d m_translate =  translate(trans);
		Matrix4d m_translate_anchor = translate(node.anchorTranslation);

		node.localTransform = m_translate_anchor * m_translate * m_rotate;
	}
}

void NativeBodyConfigurator::updateParts()
{
	// iterate over all body parts
	for(unsigned i=0; i < mBodyNodeTree->partNodes.size(); i++)
	{
		// get pointer to current
		Node *node = &(mBodyNodeTree->partNodes[i]);

		BodyJointNode *joint = 0;
		Node *parent = node->parent;
		Matrix4d transform = Matrix4d::Identity();

		while(parent != 0)
		{
			joint = dynamic_cast<BodyJointNode*>(node);
			if(joint)
			{
				transform = joint->localTransform * transform;
			}
			node = parent;
			parent = node->parent;
		}

		BodyPartNode &part = mBodyNodeTree->partNodes[i];
		part.R = transform.corner(Eigen::TopLeft, 3, 3);
		part.t = transform.corner(Eigen::TopRight, 3, 1);
	}
}


bool NativeBodyConfigurator::configure(const BodyStateVector &_state, BodyConfiguration &_config)
{
	if(_state.size() != mBodyStateVector->size())
	{
		Logger::criticalErrorMessage("tried to configure model with state vector of wrong dimensionality.");
		return false;
	}

	if((_config.rotations.size() != mBodyNodeTree->partNodes.size()) || (_config.translations.size() != mBodyNodeTree->partNodes.size()))
	{
//		TRACE("_config.rotations.size() != mBodyNodeTree->partNodes.size()), %i != %i", _config.rotations.size(), mBodyNodeTree->partNodes.size());
//		TRACE("_config.translations.size() != mBodyNodeTree->partNodes.size() %i != %i", _config.translations.size(), mBodyNodeTree->partNodes.size());

		Logger::uncriticalErrorMessage("you should ONLY pass configuration vectors of the correct dimensionality to the configurator");
		_config.rotations.resize(mBodyNodeTree->partNodes.size());
		_config.translations.resize(mBodyNodeTree->partNodes.size());
	}

	updateJoints(_state);
	updateParts();

	/*!
	 * write all transforms to configuration object
	 */
	for(unsigned i=0; i < mBodyNodeTree->partNodes.size(); i++)
	{
		BodyPartNode &part = mBodyNodeTree->partNodes[i];
		_config.rotations[i] =  part.R;
		_config.translations[i] =  part.t;
	}

	return true;
}


bool NativeBodyConfigurator::configure(const std::vector<BodyStateVector> &_states, std::vector<BodyConfiguration> &_configs)
{
	if(_configs.size() != _states.size())
	{
		_configs.resize(_states.size());
	}

	for(unsigned i=0; i < _configs.size(); i++)
	{
		configure(_states[i], _configs[i]);
	}

	return true;
}


void printJoint(const JointInfo &_joint)
{
	std::cout << "name:" << _joint.name <<
			" parent:" << _joint.parent <<
			" anchor:" << _joint.parentAnchor <<
			" childs:" << _joint.childs <<
			" indices:" << _joint.indices <<
			" indexFunc:" << _joint.indexFunc << "\n";
}


void printPart(const PartInfo &_part)
{
	std::cout << "name:" << _part.name <<
		" parent:" << _part.parent <<
		" childs:" << _part.childs <<
		" sizes:" << _part.sizes <<
		" originT:" << _part.originTransform << "\n";
}


void printDof(const DofInfo &_dof)
{
	std::cout << "index:" <<_dof.index << " type:" << _dof.type << " values:" << _dof.values << "\n";
}



}
