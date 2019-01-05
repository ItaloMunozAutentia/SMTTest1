//============================================================================
// Name        : QuickSort.tpl
// Author      : imunoz
// Version     : Jan, 2019
// Copyright   : Your copyright notice
// Description : Implementation of QuickSort templates
//============================================================================

/* INCLUDES ******************************************************************/

#include <CommonIncludes.h>

/* TEMPLATE IMPLEMENTATION ***************************************************/

template <typename T>
QuickSort<T>::QuickSort()
{
}

template <typename T>
QuickSort<T>::~QuickSort()
{
}

template <typename T>
int QuickSort<T>::Sort(VectorOf<T>& data)
{
	QuickSortMain(data, 0, data.size() - 1);
	return 0;
}

template <typename T>
void QuickSort<T>::QuickSortMain(VectorOf<T>& data, int left, int right)
{
	if (left < right)
	{
		int pivot = QuickSortPartition(data, left, right);
		QuickSortMain(data, left, pivot - 1);
		QuickSortMain(data, pivot + 1, right);
	}
}

template <typename T>
int QuickSort<T>::QuickSortPartition(VectorOf<T>& data, int left, int right)
{
	int pivot = data[right]; // TODO: choose random?
	int i = (left - 1);
	for (int j = left; j <= right- 1; j++)
	{
		if (data[j] <= pivot)
		{
			i++;
			std::swap(data[i], data[j]);
		}
	}

	std::swap(data[i + 1], data[right]);
	return (i + 1);
}
