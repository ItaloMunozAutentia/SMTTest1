//============================================================================
// Name        : Utils.cpp
// Author      : imunoz
// Version     : Jan, 2019
// Copyright   : Your copyright notice
// Description : Implementation of Utils namespace
//============================================================================

/* INCLUDES ******************************************************************/

// c headers
#include <strings.h>

// project headers
#include <Utils.h>

/* IMPLEMENTATION ************************************************************/

int Utils::StringCaseCmp(const std::string& str1, const std::string& str2)
{
	return strcasecmp(str1.c_str(), str2.c_str());
}
