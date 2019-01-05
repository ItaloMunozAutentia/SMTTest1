//============================================================================
// Name        : MergeSort.tpl
// Author      : imunoz
// Version     : Jan, 2019
// Copyright   : Your copyright notice
// Description : Implementation of MergeSort templates
//============================================================================

/* INCLUDES ******************************************************************/

#include <CommonIncludes.h>

/* TEMPLATE IMPLEMENTATION ***************************************************/

template <typename T>
MergeSort<T>::MergeSort()
{
}

template <typename T>
MergeSort<T>::~MergeSort()
{
}

template <typename T>
int MergeSort<T>::Sort(VectorOf<T>& data)
{
	MergeSortMain(data, 0, data.size() - 1);
	return 0;
}

template <typename T>
void MergeSort<T>::MergeSortMain(VectorOf<T>& data, int left, int right)
{
	if (left < right)
	{
		int mid = left + (right - left)/2;
		MergeSortMain(data, left, mid);
		MergeSortMain(data, mid + 1, right);
		Merge(data, left, mid, right);
	}
}

template <typename T>
void MergeSort<T>::Merge(VectorOf<T>& data, int left, int mid, int right)
{
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 =  right - mid;

	// Dup data into buffers
	VectorOf<T> leftDup (&data[left], &data[left + n1]);
	VectorOf<T> rightDup(&data[mid + 1], &data[mid + 1 + n2]);

	// Merge buffers back into data[left, right]
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = left; // Initial index of merged subarray
	for ( ;i < n1 && j < n2; ++k)
	{
		if (leftDup[i] <= rightDup[j])
		{
			data[k] = leftDup[i];
			i++;
		}
		else
		{
			data[k] = rightDup[j];
			j++;
		}
	}

	// Copy remaining elements, if any
	for ( ;i < n1; ++i, ++k)
	{
		data[k] = leftDup[i];
	}

	// Copy remaining elements, if any
	for (; j < n2 ; ++j, ++k)
	{
		data[k] = rightDup[j];
	}
}
