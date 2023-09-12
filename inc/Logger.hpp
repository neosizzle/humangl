#ifndef __LOGGER__H__
#define __LOGGER__H__
#include <iostream>

#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

namespace Logger
{
	void error(std::string message)
	{
		std::cout << RED << "[HGL ERROR] " << message << RESET << std::endl;
	}

	void warn(std::string message)
	{
		std::cout << YELLOW << "[HGL WARN] " << message << RESET << std::endl;
	}

	void info(std::string message)
	{
		std::cout << GREEN << "[HGL INFO] " << message << RESET << std::endl;
	}

	void debug(std::string message)
	{
		std::cout << WHITE << "[HGL DEBUG] " << message << RESET << std::endl;
	}
}//Logger


#endif  //!__LOGGER__H__