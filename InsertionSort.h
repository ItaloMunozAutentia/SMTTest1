//============================================================================
// Name        : InsertionSort.h
// Author      : imunoz
// Version     : Jan, 2019
// Copyright   : Your copyright notice
// Description : Declaration of InsertionSort class
//============================================================================

#pragma once

/* INCLUDES ******************************************************************/

#include <CommonIncludes.h>
#include <SortAlgorithm.h>

/* CLASS DECLARATION *********************************************************/

/**
 * @brief InsertionSort ...
 *
 */
template <typename T>
class InsertionSort : public SortAlgorithm<T>
{
public:
	/**
	 * @brief Creates a new instance of InsertionSort
	 *
	 */
	explicit InsertionSort();

	/**
	 * @brief Destroy an instance of InsertionSort
	 *
	 */
	virtual ~InsertionSort();

	/**
	 * @brief
	 *
	 */
	virtual int Sort(VectorOf<T>& data);

};

/* TEMPLATE IMPLEMENTATION ***************************************************/

#include <InsertionSort.tpl.h>

