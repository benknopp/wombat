/*
 * NativeBodyConfigurator.h
 *
 *  Created on: 11.03.2010
 *      Author: bknopp
 */

#ifndef NATIVEBODYCONFIGURATOR_H_
#define NATIVEBODYCONFIGURATOR_H_

#include "../AbstractBodyConfigurator.h"

#include <vector>
#include <string>

/*
 *
 */
namespace wombat
{

struct JointInfo
{
	std::string name, parent, parentAnchor, childs, indices, indexFunc;
};


struct PartInfo
{
	std::string name, parent, childs, sizes, originTransform;
};

struct DofInfo
{
	std::string type, values, index;
};


class NativeBodyConfigurator : public AbstractBodyConfigurator
{
	public:
		NativeBodyConfigurator();
		virtual ~NativeBodyConfigurator();

	    bool configure(const BodyStateVector &_state, BodyConfiguration &_config);
	    bool configure(const std::vector<BodyStateVector> &_states, std::vector<BodyConfiguration> &_configs);

	    void addJoint(const JointInfo &_info);
	    void addJoint(const std::string &_name,
					  const std::string &_parent,
					  const std::string &_parentAnchor,
					  const std::string &_childs,
					  const std::string &_indices,
					  const std::string &_indecFunc);

	    void addPart(const PartInfo &_info);
	    void addPart(const std::string &_name,
					  const std::string &_parent,
					  const std::string &_childs,
					  const std::string &_sizes,
					  const std::string &_originTransform);

	    void addDof(const DofInfo &_info);
	    void addDof(const std::string &_type,
					  const std::string &_values,
					  const std::string &_index);


	    bool generate();

	    bool isReady() const{return mIsReady;}
	protected:

	    /*!
	     * read out dofs and apply them to the corresponding joints
	     */
	    void updateJoints(const BodyStateVector &_vector);

	    /*!
	     * compute global transform
	     */
	    void updateParts();

	    std::vector<JointInfo> mJointInfoVec;
	    std::vector<PartInfo> mPartInfoVec;
	    std::vector<DofInfo> mDofInfoVec;

	    bool mIsReady;
};

void printJoint(const JointInfo &_joint);
void printPart(const PartInfo &_part);
void printDof(const DofInfo &_dof);


}

#endif /* NATIVEBODYCONFIGURATOR_H_ */
