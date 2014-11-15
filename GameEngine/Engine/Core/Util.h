#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

namespace Util
{
	void sleep(int milliseconds);
	std::vector<std::string> split(const std::string& s, char delim);
	void findAndReplace(std::string& subject, const std::string& search, const std::string& replace);
};

#endif