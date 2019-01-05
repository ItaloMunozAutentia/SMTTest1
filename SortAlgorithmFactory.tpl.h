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
#include <Utils.h>

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
	if (Utils::StringCaseCmp(sortAlgorithmName, "InsertionSort") == 0)
	{
		return std::make_unique<InsertionSort<T>>();
	}

	if (Utils::StringCaseCmp(sortAlgorithmName, "MergeSort") == 0)
	{
		return std::make_unique<MergeSort<T>>();
	}

	if (Utils::StringCaseCmp(sortAlgorithmName, "QuickSort") == 0)
	{
		return std::make_unique<QuickSort<T>>();
	}

	throw std::invalid_argument(sortAlgorithmName + ": not a known sort algorithm");
}
