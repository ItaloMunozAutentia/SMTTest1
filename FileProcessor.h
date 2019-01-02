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
#include <map>
#include <mutex>
#include <stdexcept>
#include <string>
#include <vector>

/* DECLARATIONS **************************************************************/

typedef std::vector<char> ArrayOfChars_t;
typedef void (*InsertAndSortFx_t)(const char charToInsert, ArrayOfChars_t& arrayToInsertTo);
typedef std::map<std::string, InsertAndSortFx_t> SortMethod_t;

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
	void ProcessItem(const std::string& item, size_t lineNumber);

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

private:
	std::ifstream           m_inStream;
	std::ofstream           m_outStream;
	SortMethod_t::iterator  m_sortAlgorithm;
	std::mutex              m_fileWriterMutex;

};
