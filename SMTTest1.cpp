//============================================================================
// Name        : SMTTest1.cpp
// Author      : imunoz
// Version     : Jan, 2019
// Copyright   : Your copyright notice
// Description :
//============================================================================

/* INCLUDES ******************************************************************/

// c++ headers
#include <iostream>
#include <stdexcept>
#include <string>

// project headers
#include <FileProcessor.h>
#include <SMTTest1.h>

/* IMPLEMENTATION ************************************************************/

int main(int argc, char** argv)
{
	try
	{
		if (argc != 4)
		{
			throw std::invalid_argument("Usage: " + std::string(argv[0]) + " inPath outPath sortAlgorithm:{insertion(default), merge, or quick}");
		}

		FileProcessor fileProcessor(argv[1], argv[3], argv[2]);
		fileProcessor.Run();
		return EXIT_SUCCESS;
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Unknown error" << std::endl;
	}

	return EXIT_FAILURE;
}

