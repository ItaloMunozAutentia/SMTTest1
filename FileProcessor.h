//============================================================================
// Name        : FileProcessor.h
// Author      : imunoz
// Version     : Jan, 2019
// Copyright   : Your copyright notice
// Description : Declaration of FileProcessor class
//============================================================================

#pragma once

/* INCLUDES ******************************************************************/

#include <CommonIncludes.h>
#include <SortAlgorithmFactory.h>

/* DECLARATIONS **************************************************************/

typedef VectorOf<char> Item;

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
	void StoreSortedItem(const Item& sortedItem, const std::string fieldSeparator = ",");

private:
	std::ifstream            m_inStream;
	std::string              m_sortAlgorithmName;
	SortAlgorithmPtr<char>   m_sortAlgorithm;
	std::ofstream            m_outStream;
	std::mutex               m_fileWriterMutex;
};
