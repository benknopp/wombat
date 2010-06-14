/*
 * BodyNodes.h
 *
 *  Created on: 04.04.2010
 *      Author: bknopp
 */

#ifndef BODYNODES_H_
#define BODYNODES_H_

#include <string>
#include <vector>
#include <wombat/basetypes.h>
#include <Eigen/Core>
USING_PART_OF_NAMESPACE_EIGEN


namespace wombat
{
/*!
 * superclass of all nodes, contains graph-specific members
 */
struct Node
{
		Node() : parent(0){}
		virtual ~Node(){};
		/*!
		 * each node should have a unique name
		 */
		std::string name;
		/*!
		 * pointers to children
		 */
		std::vector<Node*> children;
		/*!
		 * a tree based structure is assumed, so only one parent
		 */
		Node* parent;
};

/*!
 * a joint of the body. the only node type with degrees of freedom
 */
struct BodyJointNode : public Node
{
		enum IndexFunction{rx = 0, ry = 1, rz = 2, tx = 3, ty = 4, tz = 5};

		/*!
		 * indices of the degrees of freedom (generalized coordinates) belonging to this joint
		 */
		std::vector<unsigned> indices;
		std::vector<unsigned> indexFunctions;
		Vector3d anchorTranslation;
		Matrix4d localTransform;
};

/*!
 * a ridgid body part.
 */
struct BodyPartNode : public Node
{
		// initialize with some meaningful values
		BodyPartNode()
		{
			size.setOnes(3);
			R.setIdentity();
			t.setZero(3);
		};

		Vector3d size;
		Matrix3d R;
		Vector3d t;
		Matrix4d originTransform; // how the origin of the geometry is transformed
};

std::ostream& operator<< (std::ostream& out, const BodyJointNode &_node);
std::ostream& operator<< (std::ostream& out, const BodyPartNode &_node);
std::ostream& operator<< (std::ostream& _out, const DegreeOfFreedom &_dof);

void printBodyJointNode(const BodyJointNode &_node);
void printBodyPartNode(const BodyPartNode &_node);

bool isBodyJoint(const Node *_node);
bool isBodyPart(const Node *_node);
bool isLeaf(const Node *_node);
bool isRoot(const Node *_node);

std::vector<unsigned> getBodyPartIndices(Node* _node);

const Node* findNode(const Node* _root, const std::string &_name);
BodyJointNode* findBodyJoint(const std::vector<BodyJointNode> &_nodes, const std::string &_name);
BodyPartNode* findBodyPart(const std::vector<BodyPartNode> &_nodes, const std::string &_name);

}

#endif /* BODYNODES_H_ */
