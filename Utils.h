//============================================================================
// Name        : Utils.h
// Author      : imunoz
// Version     : Jan, 2019
// Copyright   : Your copyright notice
// Description : Utilities used all over the project
//============================================================================

#pragma once

/* INCLUDES ******************************************************************/

#include <CommonIncludes.h>

/* DECLARATIONS **************************************************************/

namespace Utils
{
	/**
	 * @brief Returns 0 if both strings are equal ignoring their case
	 *
	 */
	int StringCaseCmp(const std::string& str1, const std::string& str2);
}
