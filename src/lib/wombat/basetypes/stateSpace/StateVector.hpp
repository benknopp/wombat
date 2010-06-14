/*
 * StateVector.hpp
 *
 *  Created on: 07.03.2010
 *      Author: bknopp
 */

#ifndef STATEVECTOR_HPP_
#define STATEVECTOR_HPP_

#include <vector>
#include <wombat/helpers.h>

#include <Eigen/Core>
USING_PART_OF_NAMESPACE_EIGEN


namespace wombat
{

/*!
 * provides a vector-like interface, storing
 */
template<typename ValueType>
class StateVector
{
	public:
		StateVector();

		/*!
		 * perhaps should be protected, cloning of pointers is probably not
		 * what you want
		 */
		StateVector(const StateVector &_stateVector);
		virtual ~StateVector();

		ValueType& operator[](size_t _index);
		const ValueType& operator[](size_t _index) const;

		size_t size() const;
		size_t max_size() const;

		ValueType& at(size_t _index);
		const ValueType& at(size_t _index) const;

		void push_back(const ValueType &_ref);
		void push_back(const ValueType *_ptr);

		/*!
		 * create a DEEP! copy of the StateVector AND its elements
		 */
		StateVector clone() const;

		virtual StateVector& operator=(const StateVector &);
		virtual StateVector& operator+=(const StateVector &);
		virtual StateVector& operator-=(const StateVector &);
		virtual StateVector& operator*=(const StateVector &);
		virtual StateVector& operator/=(const StateVector &);

		virtual StateVector& operator=(double _value);
		virtual StateVector& operator+=(double _value);
		virtual StateVector& operator-=(double _value);
		virtual StateVector& operator*=(double _value);
		virtual StateVector& operator/=(double _value);


		std::vector<double> toDoubles() const;
		VectorXd toVectorXd() const;

		bool assign(const VectorXd &_vector);

		/*!
		 * assignement to and from Eigen::Vectors
		 */
//		operator VectorXd() const;
//		StateVector& operator=(const VectorXd &);
	protected:

		std::vector<ValueType*> mValues;
};

template<typename ValueType>
StateVector<ValueType>::StateVector()
{
	mValues.resize(0);
}


template<typename ValueType>
StateVector<ValueType>::StateVector(const StateVector &_stateVector)
{
	operator=(_stateVector);
}

template<typename ValueType>
StateVector<ValueType>::~StateVector()
{

}

template<typename ValueType>
ValueType&  StateVector<ValueType>::operator[](size_t _index)
{
	return *(mValues[_index]);
}


template<typename ValueType>
const ValueType& StateVector<ValueType>::operator[](size_t _index) const
{
	return *(mValues[_index]);
}


template<typename ValueType>
size_t StateVector<ValueType>::size() const
{
	return mValues.size();
}


template<typename ValueType>
size_t StateVector<ValueType>::max_size() const
{
	return mValues.max_size();
}


template<typename ValueType>
ValueType& StateVector<ValueType>::at(size_t _index)
{
	return *(mValues.at(_index));
}


template<typename ValueType>
const ValueType& StateVector<ValueType>::at(size_t _index) const
{
	return *(mValues.at(_index));
}


template<typename ValueType>
void StateVector<ValueType>::push_back(const ValueType &_ref)
{
	mValues.push_back(const_cast<ValueType*>(&_ref));
}


template<typename ValueType>
void StateVector<ValueType>::push_back(const ValueType *_ptr)
{
	// never add null-pointers!
	if(_ptr==0) return;
	mValues.push_back(const_cast<ValueType*>(_ptr));
}


template<typename ValueType>
StateVector<ValueType> StateVector<ValueType>::clone() const
{
	StateVector<ValueType> vector;
	for(typename std::vector<ValueType*>::const_iterator it = mValues.begin();
			it != mValues.end(); it++)
	{
		mValues.push_back((*it)->clone());
	}

	return vector;
}


template<typename ValueType>
StateVector<ValueType>& StateVector<ValueType>::operator=(const StateVector &_vec)
{
	mValues.clear();

	for(typename std::vector<ValueType*>::const_iterator it = _vec.mValues.begin();
			it != _vec.mValues.end(); it++)
	{
		mValues.push_back((*it)->clone());
	}

	return *this;
}


template<typename ValueType>
StateVector<ValueType>& StateVector<ValueType>::operator+=(const StateVector &_vec)
{
	for(unsigned i=0; i < this->size(); i++)
	{
		*(mValues[i]) += _vec[i];
	}

	return *this;
}


template<typename ValueType>
StateVector<ValueType>& StateVector<ValueType>::operator-=(const StateVector &_vec)
{
	for(unsigned i=0; i < this->size(); i++)
	{
		*(mValues[i]) -= _vec[i];
	}

	return *this;
}


template<typename ValueType>
StateVector<ValueType>& StateVector<ValueType>::operator*=(const StateVector &_vec)
{
	for(unsigned i=0; i < this->size(); i++)
	{
		*(mValues[i]) *= _vec[i];
	}

	return *this;
}


template<typename ValueType>
StateVector<ValueType>& StateVector<ValueType>::operator/=(const StateVector &_vec)
{
	for(unsigned i=0; i < this->size(); i++)
	{
		*(mValues[i]) /= _vec[i];
	}

	return *this;
}

template<typename ValueType>
StateVector<ValueType>& StateVector<ValueType>::operator=(double _value)
{
	typename std::vector<ValueType*>::iterator it;
	for(it = mValues.begin(); it != mValues.end(); it++)
	{
		(**it) = _value;
	}

	return *this;
}


template<typename ValueType>
StateVector<ValueType>& StateVector<ValueType>::operator+=(double _value)
{
	typename std::vector<ValueType*>::iterator it;
	for(it = mValues.begin(); it != mValues.end(); it++)
	{
		(**it) += _value;
	}

	return *this;
}


template<typename ValueType>
StateVector<ValueType>& StateVector<ValueType>::operator-=(double _value)
{
	typename std::vector<ValueType*>::iterator it;
	for(it = mValues.begin(); it != mValues.end(); it++)
	{
		(**it) -= _value;
	}

	return *this;
}


template<typename ValueType>
StateVector<ValueType>& StateVector<ValueType>::operator*=(double _value)
{
	typename std::vector<ValueType*>::iterator it;
	for(it = mValues.begin(); it != mValues.end(); it++)
	{
		(**it) *= _value;
	}

	return *this;
}


template<typename ValueType>
StateVector<ValueType>& StateVector<ValueType>::operator/=(double _value)
{
	typename std::vector<ValueType*>::iterator it;
	for(it = mValues.begin(); it != mValues.end(); it++)
	{
		(**it) /= _value;
	}

	return *this;
}


template<typename ValueType>
std::vector<double> StateVector<ValueType>::toDoubles() const
{
	std::vector<double> result;
	typename std::vector<ValueType*>::const_iterator it;

	for(it = mValues.begin(); it != mValues.end(); it++)
	{
		result.push_back((double)**it);
	}

	return result;
}



template<typename ValueType>
VectorXd StateVector<ValueType>::toVectorXd() const
{
	VectorXd result = VectorXd::Ones(mValues.size());
	double value = 0;

	for(unsigned i=0; i < mValues.size(); i++)
	{
		value = *(mValues[i]);
		result(i) = value;
	}

	return result;
}


template<typename ValueType>
bool StateVector<ValueType>::assign(const VectorXd &_vector)
{
	if(_vector.size() != (int) mValues.size()) return false;

	for(unsigned i=0; i < mValues.size(); i++)
	{
		*(mValues[i]) = _vector(i);
	}

	return true;
}

//**************************************************************************

template<typename ValueType>
StateVector<ValueType> operator+(const StateVector<ValueType> &_lhs, const StateVector<ValueType> &_rhs)
{
	StateVector<ValueType> result(_lhs);
	for(unsigned i=0; i < result.size(); i++)
	{
		result[i] += _rhs[i];
	}
	return result;
}


template<typename ValueType>
StateVector<ValueType> operator-(const StateVector<ValueType> &_lhs, const StateVector<ValueType> &_rhs)
{
	StateVector<ValueType> result(_lhs);
	for(unsigned i=0; i < result.size(); i++)
	{
		result[i] -= _rhs[i];
	}
	return result;
}


template<typename ValueType>
StateVector<ValueType> operator*(const StateVector<ValueType> &_lhs, const StateVector<ValueType> &_rhs)
{
	StateVector<ValueType> result(_lhs);
	for(unsigned i=0; i < result.size(); i++)
	{
		result[i] *= _rhs[i];
	}
	return result;
}


template<typename ValueType>
StateVector<ValueType> operator/(const StateVector<ValueType> &_lhs, const StateVector<ValueType> &_rhs)
{
	StateVector<ValueType> result(_lhs);
	for(unsigned i=0; i < result.size(); i++)
	{
		result[i] /= _rhs[i];
	}
	return result;
}


template<typename ValueType>
StateVector<ValueType> operator==(const StateVector<ValueType> &_lhs, const StateVector<ValueType> &_rhs)
{
	StateVector<ValueType> result(_lhs);
	for(unsigned i=0; i < result.size(); i++)
	{
		result[i] += _lhs[i] == _rhs[i];
	}
	return result;
}


template<typename ValueType>
StateVector<ValueType> operator!=(const StateVector<ValueType> &_lhs, const StateVector<ValueType> &_rhs)
{
	StateVector<ValueType> result(_lhs);
	for(unsigned i=0; i < result.size(); i++)
	{
		result[i] += _lhs[i] != _rhs[i];
	}
	return result;
}




}

#endif /* STATEVECTOR_HPP_ */
