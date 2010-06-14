/*
 * Timer.h
 *
 *  Created on: 02.11.2008
 *      Author: bknopp
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <boost/timer.hpp>

namespace wombat {
/**
 * \brief a simple timer
 *
 * A simple timer, providing runtime timing information
 */
class Timer
{
public:
	double start();
	double stop();
	double restart();
	double ellapsed();
protected:
	boost::timer mTimer;
};

//class Timer {
//public:
//	/**
//	 * start timer
//	 */
//	void start();
//
//	/**
//	 * stop timer and return time
//	 * \return time in msecs
//	 */
//	unsigned long stop();
//
//	/**
//	 * stop timer and return time
//	 * \return time in msecs
//	 */
//	unsigned long restart();
//
//	/**
//	 * \return ellapsed time in msecs
//	 */
//	unsigned long ellapsed();
//
//protected:
//	void calcDiffTime();
//	timeval mStart, mStop;
//	unsigned long mDiffTime;
//};
//
//inline double calcFPS(unsigned _numFrames, unsigned long _diffTime) {
//	return (((double) _numFrames * 1000000) / (double) _diffTime);
//}

}

#endif /* TIMER_H_ */
