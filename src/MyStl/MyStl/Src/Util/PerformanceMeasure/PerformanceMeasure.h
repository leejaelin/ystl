#pragma once

#include <chrono>

namespace Util { namespace PerformanceMeasure {

using namespace std;
using namespace chrono;

class PerformanceMeasure
{
public:
	typedef duration<__int64, std::milli> milliseconds;
	PerformanceMeasure()
	{
	}
	~PerformanceMeasure()
	{
	}

	void Start()
	{
		m_StartTime = system_clock::now();
	}

	void End()
	{
		m_ElpaseTime = duration_cast<milliseconds>(system_clock::now() - m_StartTime);
	}

	__int64 GetEplaseTime()
	{
		return m_ElpaseTime.count();
	}

private:
	system_clock::time_point m_StartTime;
	milliseconds m_ElpaseTime;
};
}}