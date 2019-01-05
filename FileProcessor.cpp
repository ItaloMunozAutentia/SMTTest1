//============================================================================
// Name        : FileProcessor.cpp
// Author      : imunoz
// Version     : Jan, 2019
// Copyright   : Your copyright notice
// Description : Implementation of FileProcessor class
//============================================================================

/* INCLUDES ******************************************************************/

#include <FileProcessor.h>
#include <MeasureElapsedTime.h>
#include <SortAlgorithm.h>
#include <SortAlgorithmFactory.h>
#include <SMTTest1.h>
#include <ThreadPool.h>

/* CLASS IMPLEMENTATION ******************************************************/

FileProcessor::FileProcessor(const std::string& inPath, const std::string& sortAlgorithm, const std::string& outPath)
	: m_inStream(inPath)
	, m_sortAlgorithmName(sortAlgorithm)
	, m_sortAlgorithm(SortAlgorithmFactory<char>().SortUsing(sortAlgorithm))
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
				DEBUG_LOG << m_sortAlgorithmName << " took " << usec/1000.0 << " ms" << std::endl;
			}
		);
	}

	DEBUG_LOG << "the end" << std::endl;
}

int FileProcessor::ProcessItem(const std::string& item, size_t lineNumber)
{
	DEBUG_LOG << " processing line " << lineNumber << std::endl;

	// execute sort
	Item sortedItem;
	for (auto& singleItem : item)
	{
		if (CanCharBeAdded(singleItem))
		{
			sortedItem.push_back(singleItem);
			if (m_sortAlgorithm)
				m_sortAlgorithm->Sort(sortedItem);
			else
				throw std::invalid_argument("no sort method to call");
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

void FileProcessor::StoreSortedItem(const Item& sortedItem, const std::string fieldSeparator)
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
