#include <string>

#define LINEAR_WHITESPACE " \t\v\f"

namespace utils
{
	std::string&	trim(std::string& s, const char *t = LINEAR_WHITESPACE);
	std::string&	sanitizeline(std::string& s);
}