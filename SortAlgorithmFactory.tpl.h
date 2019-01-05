//============================================================================
// Name        : KLASS.tpl
// Author      : imunoz
// Version     : Jan, 2019
// Copyright   : Your copyright notice
// Description : Implementation of KLASS templates
//============================================================================

/* INCLUDES ******************************************************************/

#include <CommonIncludes.h>
#include <InsertionSort.h>
#include <MergeSort.h>
#include <QuickSort.h>

/* TEMPLATE IMPLEMENTATION ***************************************************/

template <typename T>
SortAlgorithmFactory<T>::SortAlgorithmFactory()
{
}

template <typename T>
SortAlgorithmFactory<T>::~SortAlgorithmFactory()
{
}

template <typename T>
SortAlgorithmPtr<T> SortAlgorithmFactory<T>::SortUsing(const std::string& sortAlgorithmName)
{
	if (sortAlgorithmName == "InsertionSort")
	{
		return std::make_unique<InsertionSort<T>>();
	}

	if (sortAlgorithmName == "MergeSort")
	{
		return std::make_unique<MergeSort<T>>();
	}

	if (sortAlgorithmName == "QuickSort")
	{
		return std::make_unique<QuickSort<T>>();
	}

	throw std::invalid_argument(sortAlgorithmName + ": not a known sort algorithm");
}
