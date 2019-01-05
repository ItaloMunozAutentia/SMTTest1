//============================================================================
// Name        : InsertionSort.tpl
// Author      : imunoz
// Version     : Jan, 2019
// Copyright   : Your copyright notice
// Description : Implementation of InsertionSort templates
//============================================================================

/* INCLUDES ******************************************************************/

#include <CommonIncludes.h>

/* TEMPLATE IMPLEMENTATION ***************************************************/

template <typename T>
InsertionSort<T>::InsertionSort()
{
}

template <typename T>
InsertionSort<T>::~InsertionSort()
{
}

template <typename T>
int InsertionSort<T>::Sort(VectorOf<T>& data)
{
	for (size_t i = 0 ; i < data.size(); ++i)
	{
		size_t indexOfMin = i;
		for (size_t j = i ; j < data.size(); ++j)
		{
			if (data.at(indexOfMin) > data.at(j))
			{
				indexOfMin = j;
			}
		}

		if (indexOfMin != i)
		{
			std::swap(data[indexOfMin], data[i]);
		}
	}

	return 0;
}
