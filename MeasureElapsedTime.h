//============================================================================
// Name        :
// Author      : https://stackoverflow.com/questions/2808398/easily-measure-elapsed-time
// Version     :
// Copyright   :
// Description :
//============================================================================

#pragma once

/* INCLUDES ******************************************************************/

#include <CommonIncludes.h>

/* IMPLEMENTATION ************************************************************/

template<typename TimeT = std::chrono::milliseconds>
struct MeasureElapsedTime
{
	template<typename F, typename ...Args>
	static typename TimeT::rep Execution(F&& func, Args&&... args)
	{
		auto start = std::chrono::steady_clock::now();
		std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
		auto duration = std::chrono::duration_cast< TimeT>
			(std::chrono::steady_clock::now() - start);
		return duration.count();
	}
};
