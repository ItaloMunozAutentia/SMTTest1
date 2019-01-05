//============================================================================
// Name        : SMTTest1.cpp
// Author      : imunoz
// Version     : Jan, 2019
// Copyright   : Your copyright notice
// Description :
//============================================================================

/* INCLUDES ******************************************************************/

#include <FileProcessor.h>
#include <MeasureElapsedTime.h>
#include <SMTTest1.h>

/* DECLARATIONS **************************************************************/

int Main(char** argv);

/* IMPLEMENTATION ************************************************************/

int main(int argc, char** argv)
{
	try
	{
		if (argc != 4)
		{
			throw std::invalid_argument("Usage: " + std::string(argv[0]) + " inPath outPath sortAlgorithm:{InsertionSort, MergeSort, QuickSort}");
		}

		auto elapsed = MeasureElapsedTime<>::Execution(Main, argv);
		INFO_LOG << "The whole " << argv[3] << " sort process took " << elapsed << " ms " << std::endl;

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

int Main(char** argv)
{
	FileProcessor fileProcessor(argv[1], argv[3], argv[2]);
	fileProcessor.Run();
	return EXIT_SUCCESS;
}
