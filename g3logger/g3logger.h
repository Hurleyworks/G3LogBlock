#pragma once

#include "g2log.hpp"

// time
typedef std::chrono::high_resolution_clock timePiece;
typedef std::chrono::microseconds microseconds;
typedef std::chrono::milliseconds milliseconds;

namespace
{
	timePiece::time_point now(){ return timePiece::now(); }

	microseconds intervalUs(const timePiece::time_point& t1, const timePiece::time_point& t0)
	{
		return std::chrono::duration_cast<microseconds>(t1 - t0);
	}

	milliseconds intervalMs(const timePiece::time_point& t1, const timePiece::time_point& t0)
	{
		return std::chrono::duration_cast<milliseconds>(t1 - t0);
	}
}


class StopWatch
{

public:
	StopWatch()
		: start_(timePiece::now())
	{}
	timePiece::time_point restart()
	{
		start_ = timePiece::now(); return start_;
	}
	microseconds elapsedUs()    { return intervalUs(now(), start_); }
	milliseconds elapsedMs()    { return intervalMs(now(), start_); }

private:
	timePiece::time_point start_;
};

struct ScopedStopWatch
{
	ScopedStopWatch(const char function[] = "unknown function")
		: func(function),
		  measure()
	{

	}

	~ScopedStopWatch()
	{
		double secs = (double)measure.elapsedUs().count();
		secs *= .000001;
		LOG(DBUG) << func << " took " << secs << " seconds";
	}
	const char * func;
	StopWatch measure;
};
