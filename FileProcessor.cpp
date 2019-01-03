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
#include <functional>
#include <map>
#include <utility>

// c headers
#include <unistd.h> // sleep()

// project headers
#include <FileProcessor.h>
#include <MeasureElapsedTime.h>
#include <SMTTest1.h>
#include <ThreadPool.h>

/* DECLARATIONS **************************************************************/

void NonMemberSortFunctionExample(ArrayOfChars_t& arrayToInsertTo);

/* CLASS IMPLEMENTATION ******************************************************/

FileProcessor::FileProcessor(const std::string& inPath, const std::string& sortAlgorithm, const std::string& outPath)
	: m_inStream(inPath)
	, m_sortAlgorithm(sortAlgorithm)
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

	// select sort algorithm
	using namespace std::placeholders;
	m_sortCommand =
	{
		  { "insertion", std::bind(&FileProcessor::InsertionSort, this, _1) }
		, { "merge", std::bind(&FileProcessor::MergeSort, this, _1) }
		, { "quick", std::bind(&FileProcessor::QuickSort, this, _1) }
		, { "wwww", std::bind(NonMemberSortFunctionExample,  _1) }
	};
	m_selectedSort = m_sortCommand.find(m_sortAlgorithm);
	if (m_selectedSort == m_sortCommand.end())
	{
		throw std::invalid_argument("unsupported sort algorithm: <" + m_sortAlgorithm + ">");
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
				using uSEC = std::chrono::microseconds;
				auto usec = MeasureElapsedTime<uSEC>::Execution
				(
					std::bind(&FileProcessor::ProcessItem, this, std::move(item), lineNumber)
				);
				DEBUG_LOG << m_sortAlgorithm << " sort took " << usec/1000.0 << " ms" << std::endl;
			}
		);
	}

	DEBUG_LOG << "the end" << std::endl;
}

int FileProcessor::ProcessItem(const std::string& item, size_t lineNumber)
{
	DEBUG_LOG << " processing line " << lineNumber << std::endl;

	// execute sort
	ArrayOfChars_t sortedItem;
	for (auto& singleItem : item)
	{
		if (CanCharBeAdded(singleItem))
		{
			sortedItem.push_back(singleItem);
			m_selectedSort->second(sortedItem);
		}
	}

	StoreSortedItem(sortedItem);
	return 0;
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

void FileProcessor::InsertionSort(ArrayOfChars_t& arrayToInsertTo)
{
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

void FileProcessor::MergeSort(ArrayOfChars_t& arrayToInsertTo)
{
	MergeSortMain(arrayToInsertTo, 0, arrayToInsertTo.size() - 1);
}

void FileProcessor::QuickSort(ArrayOfChars_t& arrayToInsertTo)
{
	QuickSortMain(arrayToInsertTo, 0, arrayToInsertTo.size() - 1);
}

/* CLASS PRIVATE'S IMPLEMENTATION ********************************************/

// Sort arrayToSort[] between [left,right]
void FileProcessor::MergeSortMain(ArrayOfChars_t& arrayToSort, int left, int right)
{
	if (left < right)
	{
		int mid = left+(right-left)/2;
		MergeSortMain(arrayToSort, left, mid);
		MergeSortMain(arrayToSort, mid + 1, right);
		Merge(arrayToSort, left, mid, right);
	}
}

void FileProcessor::Merge(ArrayOfChars_t& arrayToSort, int left, int mid, int right)
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
void FileProcessor::QuickSortMain(ArrayOfChars_t& arrayToSort, int left, int right)
{
	if (left < right)
	{
		int pivot = QuickSortPartition(arrayToSort, left, right);
		QuickSortMain(arrayToSort, left, pivot - 1);
		QuickSortMain(arrayToSort, pivot + 1, right);
	}
}

int FileProcessor::QuickSortPartition (ArrayOfChars_t& arrayToSort, int left, int right)
{
	int pivot = arrayToSort[right]; // TODO: choose random?
	int i = (left - 1);
	for (int j = left; j <= right- 1; j++)
	{
		if (arrayToSort[j] <= pivot)
		{
			i++;
			std::swap(arrayToSort[i], arrayToSort[j]);
		}
	}

	std::swap(arrayToSort[i + 1], arrayToSort[right]);
	return (i + 1);
}

void NonMemberSortFunctionExample(ArrayOfChars_t& arrayToInsertTo)
{
	std::string error(std::string(__FUNCTION__) + "() not implemented yet");
	ERROR_LOG << error << std::endl;
	throw std::invalid_argument(error);
}

