//============================================================================
// Name        : SMTTest1.h
// Author      : imunoz
// Version     : Jan, 2019
// Copyright   : Your copyright notice
// Description :
//============================================================================

#pragma once

/* INCLUDES ******************************************************************/

#include <iostream>
#include <thread>

/* DEFINES *******************************************************************/

#define INFO_LOG     std::cout << std::endl << std::this_thread::get_id() << " "
#define WARNING_LOG  std::cerr << std::endl << std::this_thread::get_id() << " "
#define ERROR_LOG    std::cerr << std::endl << std::this_thread::get_id() << " "
#define DEBUG_LOG    std::cerr << std::endl << std::this_thread::get_id() << " "

#define DUMP(xx)     #xx "=<" << xx << "> "
