#include "utils.hpp"

static std::string &rtrim(std::string &s, const char *t = LINEAR_WHITESPACE);
static std::string &ltrim(std::string &s, const char *t = LINEAR_WHITESPACE);

/*
	from stackoverflow: https://stackoverflow.com/questions/216823/how-to-trim-an-stdstring
	trim right and left whitespace from string
*/

std::string&	utils::trim(std::string &s, const char *t)
{
	return (ltrim(rtrim(s, t), t));
}

static std::string&	ltrim(std::string &s, const char *t)
{
	s.erase(0, s.find_first_not_of(t));
	return s;
}

static std::string&	rtrim(std::string &s, const char *t)
{
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}

/*
	remove ending cr if present. replace bare cr with sp

	This is to comply with the http specification.
	It says we must either reject bare CRs or replace them with SP.
	The specification also says we can use LF as line delimiter and ignore the CR that comes before.
*/
std::string&	utils::sanitizeline(std::string& s)
{
	if (s.length() > 0 && s[s.length() - 1] == '\r')
		s.resize(s.length() - 1);
	while (size_t pos = s.find("\r") != std::string::npos)
		s.replace(pos, 1, " ");
	return (s);
}