/*
 * BodyNodeTree.h
 *
 *  Created on: 04.04.2010
 *      Author: bknopp
 */

#ifndef BODYNODETREE_H_
#define BODYNODETREE_H_

#include "BodyNodes.h"

/*
 *
 */
namespace wombat
{

class BodyNodeTree
{
	public:
		BodyNodeTree();
		virtual ~BodyNodeTree();

	    std::vector<BodyJointNode> jointNodes;
	    std::vector<BodyPartNode> partNodes;
	    std::vector<DegreeOfFreedom> dofs;
	    Node* root;

	    void findRoot();
	    void scale(double _scaleFactor);
	    double scaleFactor();

	    std::string getIndexName(unsigned _index) const;
	protected:
	    double mScaleFactor;
};

std::ostream& operator<< (std::ostream& out, const BodyNodeTree &_tree);
void printBodyNodeTree(const BodyNodeTree &_tree);


}

#endif /* BODYNODETREE_H_ */
