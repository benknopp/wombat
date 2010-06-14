#include "Timer.h"

namespace wombat
{

double Timer::start()
{
	mTimer.restart();
	return mTimer.elapsed();
}


double Timer::stop()
{
	return mTimer.elapsed();
}


double Timer::restart()
{
	double result = mTimer.elapsed();
	mTimer.restart();
	return result;

}


double Timer::ellapsed()
{
	return mTimer.elapsed();
}



//void Timer::start()
//{
//	mTimer.restart();
////	gettimeofday(&mStart, 0);
//}
//
//unsigned long Timer::stop()
//{
//	gettimeofday(&mStop, 0);
//	calcDiffTime();
//	return mDiffTime;
//}
//
//unsigned long Timer::restart()
//{
//	gettimeofday(&mStop, 0);
//	calcDiffTime();
//	gettimeofday(&mStart, 0);
//	return mDiffTime;
//}
//
//unsigned long Timer::ellapsed()
//{
//	gettimeofday(&mStop, 0);
//	calcDiffTime();
//	return mDiffTime;
//
//}
//
//void Timer::calcDiffTime()
//{
//	mDiffTime = (mStop.tv_sec - mStart.tv_sec) * 1000000 + (mStop.tv_usec
//			- mStart.tv_usec);
//}

}
