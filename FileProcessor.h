//============================================================================
// Name        : FileProcessor.h
// Author      : imunoz
// Version     : Jan, 2019
// Copyright   : Your copyright notice
// Description : Declaration of FileProcessor class
//============================================================================

#pragma once

/* INCLUDES ******************************************************************/

#include <fstream>
#include <functional>
#include <map>
#include <mutex>
#include <stdexcept>
#include <string>
#include <vector>

/* DECLARATIONS **************************************************************/

typedef std::vector<char> ArrayOfChars_t;
typedef std::function<void(ArrayOfChars_t& arrayToInsertTo)> SortFx_t;
typedef std::map<std::string, SortFx_t> SortCommand_t;

/* CLASS DECLARATION *********************************************************/

class FileProcessor
{
public:
	/**
	 * @brief TODO
	 *
	 */
	explicit FileProcessor(const std::string& inPath, const std::string& sortAlgorithm, const std::string& outPath);

	/**
	 * @brief TODO
	 *
	 */
	virtual ~FileProcessor();

	/**
	 * @brief TODO
	 *
	 */
	void Run();

protected:
	/**
	 * @brief TODO
	 *
	 */
	int ProcessItem(const std::string& item, size_t lineNumber);

	/**
	 * @brief TODO
	 *
	 */
	bool CanCharBeAdded(const char& character);

	/**
	 * @brief TODO
	 *
	 */
	void StoreSortedItem(const ArrayOfChars_t& sortedItem, const std::string fieldSeparator = ",");

	/**
	 * @brief TODO
	 *
	 */
	void InsertionSort(ArrayOfChars_t& arrayToInsertTo);

	/**
	 * @brief TODO
	 *
	 */
	void MergeSort(ArrayOfChars_t& arrayToInsertTo);

	/**
	 * @brief TODO
	 *
	 */
	void QuickSort(ArrayOfChars_t& arrayToInsertTo);

private:
	/**
	 * @brief MergeSort internal stuff
	 *
	 */
	void MergeSortMain(ArrayOfChars_t& arrayToSort, int left, int right);
	void Merge(ArrayOfChars_t& arrayToSort, int left, int mid, int right);

	/**
	 * @brief QuickSort  internal stuff
	 *
	 */
	void QuickSortMain(ArrayOfChars_t& arrayToSort, int left, int right);
	int  QuickSortPartition (ArrayOfChars_t& arrayToSort, int left, int right);

	std::ifstream            m_inStream;
	std::string              m_sortAlgorithm;
	SortCommand_t            m_sortCommand;
	SortCommand_t::iterator  m_selectedSort;
	std::ofstream            m_outStream;
	std::mutex               m_fileWriterMutex;
};
