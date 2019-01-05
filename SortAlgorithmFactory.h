//============================================================================
// Name        : SortAlgorithmFactory.h
// Author      : imunoz
// Version     : Jan, 2019
// Copyright   : Your copyright notice
// Description : Declaration of SortAlgorithmFactory class
//============================================================================

#pragma once

/* INCLUDES ******************************************************************/

#include <CommonIncludes.h>
#include <SortAlgorithm.h>

/* DECLARATIONS **************************************************************/

template <typename T> using SortAlgorithmPtr = std::unique_ptr<SortAlgorithm<T>>;

/* CLASS DECLARATION *********************************************************/

/**
 * @brief SortAlgorithmFactory ...
 *
 */
template <typename T>
class SortAlgorithmFactory
{
public:
	/**
	 * @brief Creates a new instance of SortAlgorithmFactory
	 *
	 */
	explicit SortAlgorithmFactory();

	/**
	 * @brief Destroy an instance of SortAlgorithmFactory
	 *
	 */
	virtual ~SortAlgorithmFactory();

	/**
	 * @brief
	 *
	 */
	SortAlgorithmPtr<T> SortUsing(const std::string& sortAlgorithmName);
};

/* TEMPLATE IMPLEMENTATION ***************************************************/

#include <SortAlgorithmFactory.tpl.h>
