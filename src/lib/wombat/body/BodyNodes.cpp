/*
 * BodyNodes.cpp
 *
 *  Created on: 04.04.2010
 *      Author: bknopp
 */

#include "BodyNodes.h"
#include <wombat/helpers.h>

namespace wombat
{

std::ostream& operator<< (std::ostream& _out, const BodyJointNode &_node)
{
	std::string name, parent, childs;

	for(unsigned i=0; i < _node.children.size(); i++)
	{
		childs += _node.children[i]->name;
		childs += " ";
	}

	name = _node.name;
	parent = (_node.parent != 0) ? _node.parent->name : "NO PARENT";

	std::string indices;
	for(unsigned i=0; i < _node.indices.size(); i++)
	{
		indices += toString(_node.indices[i]);
		indices += ";";
	}

	_out << "name:" << name << "   parent:" << parent <<
			"   childs:" << childs << "   indices:" << indices <<
			"   anchor:" << _node.anchorTranslation.transpose() << "\n";


	return _out;
}


std::ostream& operator<< (std::ostream& _out, const BodyPartNode &_node)
{
	std::string name, parent, childs;

	for(unsigned i=0; i < _node.children.size(); i++)
	{
		childs += _node.children[i]->name;
		childs += " ";
	}

	name = _node.name;
	parent = (_node.parent != 0) ? _node.parent->name : "NO PARENT";
	std::string size = fToString(_node.size.x()) + ", " + fToString(_node.size.y())
			+ ", " + fToString(_node.size.z());

	_out << "name:" << name << "   parent:" << parent <<
			"   childs:" << childs << "   sizes:" << size << "\n";
	return _out;
}

std::ostream& operator<< (std::ostream& _out, const DegreeOfFreedom &_dof)
{
	std::string type, range;

	switch(_dof.rangeType)
	{
	default:
	case DegreeOfFreedom::unlimitedRange:
		type = "unlimited";
		range = "";
		break;
	case DegreeOfFreedom::limitedRange:
		type = "limited  ";
		range = "min:" + toString(_dof.min) + " max:" + toString(_dof.max);
		break;
	case DegreeOfFreedom::circularRange:
		type = "circular ";
		range = "min:" + toString(_dof.min) + " max:" + toString(_dof.max);
		break;
	}

	_out << "name:" <<  _dof.name <<" type:" << type << " range:" << range <<
			" position:" << _dof.stateVecPosition << "\n";
	return _out;
}


void printBodyJointNode(const BodyJointNode &_node)
{
	std::cout << _node;
}

void printBodyPartNode(const BodyPartNode &_node)
{
	std::cout << _node;
}






bool isBodyJoint(const Node *_node)
{
    return (dynamic_cast<const BodyJointNode*>(_node) != 0);
}

bool isBodyPart(const Node *_node)
{
    return (dynamic_cast<const BodyPartNode*>(_node) != 0);
}

bool isLeaf(const Node *_node)
{
    return (_node->children.size() == 0);
}

bool isRoot(const Node *_node)
{
    return (_node->parent == 0);
}

std::vector<unsigned> getBodyPartIndices(Node* _node)
{
    std::vector<unsigned> result;

    // if root nothing can be found
    if(_node->parent==0) return result;

    if(isBodyJoint(_node->parent))
    {
        BodyJointNode* node = reinterpret_cast<BodyJointNode*>(_node->parent);
        result = node->indices;
    } else
    {
        result = getBodyPartIndices(_node->parent);
    }

    return result;
}

const Node* findNode(const Node* _root, const std::string &_name)
{
    // return nullpointer if root is invalid
    if(_root == 0) return 0;

    // if root has correct name
    if(_root->name == _name ) return _root;

    // check children
    for(unsigned i=0; i < _root->children.size(); i++)
    {
        //const Node* child = _root->children[i];
        const Node* result = findNode(_root->children[i], _name);
        if(result) return result;
    }

    //nothing found so far. return 0
    return 0;
}


BodyJointNode* findBodyJoint(const std::vector<BodyJointNode> &_nodes, const std::string &_name)
{
    BodyJointNode *result = 0;

    for(std::vector<BodyJointNode>::const_iterator it = _nodes.begin(); it != _nodes.end(); it++)
    {
        if(it->name == _name ) result = const_cast<BodyJointNode*>(&(*it));
    }

    return result;
}

BodyPartNode* findBodyPart(const std::vector<BodyPartNode> &_nodes, const std::string &_name)
{
    BodyPartNode *result = 0;

    for(std::vector<BodyPartNode>::const_iterator it = _nodes.begin(); it != _nodes.end(); it++)
    {
        if(it->name == _name ) result = const_cast<BodyPartNode*>(&(*it));
    }

    return result;

}



}
