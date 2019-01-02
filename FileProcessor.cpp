//============================================================================
// Name        : FileProcessor.cpp
// Author      : imunoz
// Version     : Jan, 2019
// Copyright   : Your copyright notice
// Description : Implementation of FileProcessor class
//============================================================================

/* INCLUDES ******************************************************************/

// c++ headers
#include <chrono>
#include <map>
#include <utility>

// c headers
#include <unistd.h> // sleep()

// project headers
#include <FileProcessor.h>
#include <SMTTest1.h>
#include <ThreadPool.h>

/* DECLARATIONS **************************************************************/

void InsertionSort(const char charToInsert, ArrayOfChars_t& arrayToInsertTo);
void MergeSort(const char charToInsert, ArrayOfChars_t& arrayToInsertTo);
void QuickSort(const char charToInsert, ArrayOfChars_t& arrayToInsertTo);

/* CLASS IMPLEMENTATION ******************************************************/

FileProcessor::FileProcessor(const std::string& inPath, const std::string& sortAlgorithm, const std::string& outPath)
	: m_inStream(inPath)
	, m_outStream(outPath)
{
	if (!m_inStream.is_open())
	{
		throw std::invalid_argument("can't read file: <" + inPath + ">");
	}

	if (!m_outStream.is_open())
	{
		throw std::invalid_argument("can't write file: <" + outPath + ">");
	}

	// select sort algorithm from param
	SortMethod_t sortMethods =
	{
		  { "insertion", InsertionSort }
		, { "merge", MergeSort }
		, { "quick", QuickSort }
	};
	m_sortAlgorithm = sortMethods.find(sortAlgorithm);
	if (m_sortAlgorithm == sortMethods.end())
	{
		m_sortAlgorithm = sortMethods.begin();
	}
}

FileProcessor::~FileProcessor()
{
}

void FileProcessor::Run()
{
	DEBUG_LOG << "starting..." << std::endl;
	ThreadPool pool(4);
	std::string item;
	for (size_t lineNumber = 0 ; std::getline(m_inStream, item); ++lineNumber)
	{
		pool.Enqueue
		(
			[this, item, lineNumber]()
			{
				ProcessItem(std::move(item), lineNumber);
			}
		);
	}

	DEBUG_LOG << "the end" << std::endl;
}

void FileProcessor::ProcessItem(const std::string& item, size_t lineNumber)
{
	DEBUG_LOG << " processing line " << lineNumber << std::endl;

	// execute sort
	using steady = std::chrono::steady_clock;
	auto start = steady::now();
	ArrayOfChars_t sortedItem;
	for (auto& singleItem : item)
	{
		if (CanCharBeAdded(singleItem))
			m_sortAlgorithm->second(singleItem, sortedItem);
	}

	// compute duration
	auto finish = steady::now();
	using ms = std::chrono::milliseconds;
	auto elapsed = std::chrono::duration_cast<ms>(finish - start);
	DEBUG_LOG << m_sortAlgorithm->first << "Sort took "
		<< elapsed.count() << " ms "
		<< "to sort" << std::endl;

	StoreSortedItem(sortedItem);
}

bool FileProcessor::CanCharBeAdded(const char& character)
{
	if (character == ' ')
	{
		DEBUG_LOG << "Sleeping..." << std::endl;
		::sleep(1);
		return false;
	}

	return true;
}

void FileProcessor::StoreSortedItem(const ArrayOfChars_t& sortedItem, const std::string fieldSeparator)
{
	std::unique_lock<std::mutex> lock(m_fileWriterMutex);
	if (!m_outStream.is_open())
	{
		throw std::invalid_argument("can't write to output file");
	}

	for (auto it = sortedItem.begin(); it != sortedItem.end(); ++it)
	{
		if (it + 1 == sortedItem.end())
			m_outStream << *it;
		else
			m_outStream << *it << fieldSeparator;
	}

	m_outStream << std::endl;
	m_outStream.flush();
}

void InsertionSort(const char charToInsert, ArrayOfChars_t& arrayToInsertTo)
{
	arrayToInsertTo.push_back(charToInsert);
	for (size_t i = 0 ; i < arrayToInsertTo.size(); ++i)
	{
		size_t indexOfMin = i;
		for (size_t j = i ; j < arrayToInsertTo.size(); ++j)
		{
			if (arrayToInsertTo.at(indexOfMin) > arrayToInsertTo.at(j))
			{
				indexOfMin = j;
			}
		}

		if (indexOfMin != i)
		{
			std::swap(arrayToInsertTo[indexOfMin], arrayToInsertTo[i]);
		}
	}
}

void MergeSort(const char charToInsert, ArrayOfChars_t& arrayToInsertTo)
{
	arrayToInsertTo.push_back(charToInsert);
	void MergeSort(ArrayOfChars_t& arrayToSort, int left, int right);
	MergeSort(arrayToInsertTo, 0, arrayToInsertTo.size() - 1);
}

void Merge(ArrayOfChars_t& arrayToSort, int left, int mid, int right)
{
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 =  right - mid;

	// Dup data into buffers
	ArrayOfChars_t leftDup (&arrayToSort[left], &arrayToSort[left + n1]);
	ArrayOfChars_t rightDup(&arrayToSort[mid + 1], &arrayToSort[mid + 1 + n2]);

	// Merge buffers back into arrayToSort[left, right]
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = left; // Initial index of merged subarray
	for ( ;i < n1 && j < n2; ++k)
	{
		if (leftDup[i] <= rightDup[j])
		{
			arrayToSort[k] = leftDup[i];
			i++;
		}
		else
		{
			arrayToSort[k] = rightDup[j];
			j++;
		}
	}

	// Copy remaining elements, if any
	for ( ;i < n1; ++i, ++k)
	{
		arrayToSort[k] = leftDup[i];
	}

	// Copy remaining elements, if any
	for (; j < n2 ; ++j, ++k)
	{
		arrayToSort[k] = rightDup[j];
	}
}

// Sort arrayToSort[] between [left,right]
void MergeSort(ArrayOfChars_t& arrayToSort, int left, int right)
{
	if (left < right)
	{
		int mid = left+(right-left)/2;
		MergeSort(arrayToSort, left, mid);
		MergeSort(arrayToSort, mid + 1, right);
		Merge(arrayToSort, left, mid, right);
	}
}

void QuickSort(const char charToInsert, ArrayOfChars_t& arrayToInsertTo)
{
	arrayToInsertTo.push_back(charToInsert);
	void QuickSort(ArrayOfChars_t& arr, int left, int right);
	QuickSort(arrayToInsertTo, 0, arrayToInsertTo.size() - 1);
}

int QuickSortPartition (ArrayOfChars_t& arr, int left, int right)
{
	int pivot = arr[right]; // TODO: choose random?
	int i = (left - 1);
	for (int j = left; j <= right- 1; j++)
	{
		if (arr[j] <= pivot)
		{
			i++;
			std::swap(arr[i], arr[j]);
		}
	}

	std::swap(arr[i + 1], arr[right]);
	return (i + 1);
}

void QuickSort(ArrayOfChars_t& arr, int left, int right)
{
	if (left < right)
	{
		int pivot = QuickSortPartition(arr, left, right);
		QuickSort(arr, left, pivot - 1);
		QuickSort(arr, pivot + 1, right);
	}
}

