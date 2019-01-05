//============================================================================
// Name        : QuickSort.h
// Author      : imunoz
// Version     : Jan, 2019
// Copyright   : Your copyright notice
// Description : Declaration of QuickSort class
//============================================================================

#pragma once

/* INCLUDES ******************************************************************/

#include <CommonIncludes.h>
#include <SortAlgorithm.h>

/* CLASS DECLARATION *********************************************************/

/**
 * @brief QuickSort ...
 *
 */
template <typename T>
class QuickSort : public SortAlgorithm<T>
{
public:
	/**
	 * @brief Creates a new instance of QuickSort
	 *
	 */
	explicit QuickSort();

	/**
	 * @brief Destroy an instance of QuickSort
	 *
	 */
	virtual ~QuickSort();

	/**
	 * @brief QuickSort implementation
	 *
	 */
	virtual int Sort(VectorOf<T>& data);

protected:
	/**
	 * @brief QuickSort internals
	 *
	 */
	void QuickSortMain(VectorOf<T>& data, int left, int right);
	int  QuickSortPartition (VectorOf<T>& data, int left, int right);
};

/* TEMPLATE IMPLEMENTATION ***************************************************/

#include <QuickSort.tpl.h>

