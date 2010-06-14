/*
 * StateVectorLimiter.hpp
 *
 *  Created on: 28.04.2010
 *      Author: bknopp
 */

#ifndef STATEVECTORLIMITER_HPP_
#define STATEVECTORLIMITER_HPP_

#include "StateVector.hpp"
#include <Eigen/Core>
USING_PART_OF_NAMESPACE_EIGEN


namespace wombat
{

template<typename StateType>
class StateVectorLimiter
{
public:
	void setLimits(const VectorXd &_lower, const VectorXd &_upper);
	VectorXd lower() const;
	VectorXd upper() const;

	bool operator()(StateVector<StateType> &_stateVec) const;
	bool testState(const StateVector<StateType> &_stateVec) const;
protected:
	VectorXd mLower, mUpper;
};


template<typename StateType>
void StateVectorLimiter<StateType>::setLimits(const VectorXd &_lower, const VectorXd &_upper)
{
	mLower = _lower;
	mUpper = _upper;
}


template<typename StateType>
VectorXd StateVectorLimiter<StateType>::lower() const
{
	return mLower;
}


template<typename StateType>
VectorXd StateVectorLimiter<StateType>::upper() const
{
	return mUpper;
}


template<typename StateType>
bool StateVectorLimiter<StateType>::operator()(StateVector<StateType> &_stateVec) const
{
	if((_stateVec.size() != mUpper.size()) |(_stateVec.size() != mLower.size()))
	{
		std::cout << "incompatible dimensions. can't evaluate state limits\n";
		return false;
	}
}


template<typename StateType>
bool StateVectorLimiter<StateType>::testState(const StateVector<StateType> &_stateVec) const
{
	bool result = true;

	if((_stateVec.size() != mUpper.size()) |(_stateVec.size() != mLower.size()))
	{
		std::cout << "incompatible dimensions. can't evaluate state limits\n";
		return false;
	}

	for(unsigned i=0; i < _stateVec.size(); i++)
	{
		bool valid = ((mLower(i) <= _stateVec[i]) & (mUpper(i) >= _stateVec[i]));
		result &= valid;
		std::string msg = valid ? "ok" : "error";
		std::cout << i << ". value=" << _stateVec[i] << "[" << mLower(i) << " ; " << mUpper(i)
				  << msg << "\n";

	}
	return result;
}




}


#endif /* STATEVECTORLIMITER_HPP_ */
