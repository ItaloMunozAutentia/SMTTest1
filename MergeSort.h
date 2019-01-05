//============================================================================
// Name        : MergeSort.h
// Author      : imunoz
// Version     : Jan, 2019
// Copyright   : Your copyright notice
// Description : Declaration of MergeSort class
//============================================================================

#pragma once

/* INCLUDES ******************************************************************/

#include <CommonIncludes.h>
#include <SortAlgorithm.h>

/* CLASS DECLARATION *********************************************************/

/**
 * @brief MergeSort ...
 *
 */
template <typename T>
class MergeSort : public SortAlgorithm<T>
{
public:
	/**
	 * @brief Creates a new instance of MergeSort
	 *
	 */
	explicit MergeSort();

	/**
	 * @brief Destroy an instance of MergeSort
	 *
	 */
	virtual ~MergeSort();

	/**
	 * @brief MergeSort implementation
	 *
	 */
	virtual int Sort(VectorOf<T>& data);

protected:
	/**
	 * @brief MergeSort internals
	 *
	 */
	void MergeSortMain(VectorOf<T>& data, int left, int right);
	void Merge(VectorOf<T>& data, int left, int mid, int right);
};

/* TEMPLATE IMPLEMENTATION ***************************************************/

#include <MergeSort.tpl.h>

