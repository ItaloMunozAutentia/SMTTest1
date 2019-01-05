//============================================================================
// Name        : SortAlgorithm.h
// Author      : imunoz
// Version     : Jan, 2019
// Copyright   : Your copyright notice
// Description : Declaration of SortAlgorithm class
//============================================================================

#pragma once

/* INCLUDES ******************************************************************/

#include <CommonIncludes.h>

/* DECLARATIONS **************************************************************/

template <typename T> using VectorOf = std::vector<T>;

/* CLASS DECLARATION *********************************************************/

/**
 * @brief SortAlgorithm ...
 *
 */
template <typename T>
class SortAlgorithm
{
public:
	/**
	 * @brief Creates a new instance of SortAlgorithm
	 *
	 */
	explicit SortAlgorithm();

	/**
	 * @brief Destroy an instance of SortAlgorithm
	 *
	 */
	virtual ~SortAlgorithm();

	/**
	 * @brief
	 *
	 */
	virtual int Sort(VectorOf<T>& data) = 0;
};

/* TEMPLATE IMPLEMENTATION ***************************************************/

#include <SortAlgorithm.tpl.h>
