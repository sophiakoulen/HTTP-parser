#include "HTTPRequest.hpp"
#include "utils.hpp"
#include <iostream>
#include <sstream>
#include <map>

std::istream &operator>>(std::istream &is, char const *s);

HTTPRequest::HTTPRequest(std::string &input)
{
	std::cout << "HTTPRequest ctor" << std::endl;
	parse(input);

	/* print the headers */
	for (std::map<std::string, std::string>::iterator it = _headers.begin(); it != _headers.end(); it++)
	{
		std::cout<<it->first<<": "<<it->second<<std::endl;
	}
}

HTTPRequest::HTTPRequest(const HTTPRequest &cpy)
{
	(void)cpy;
}

HTTPRequest::~HTTPRequest()
{
}

HTTPRequest &HTTPRequest::operator=(const HTTPRequest &rhs)
{
	(void)rhs;
	return (*this);
}

/* getters */
int			HTTPRequest::getStatus() const { return _status; }
t_version	HTTPRequest::getVersion() const { return _version; }
std::string	HTTPRequest::getURI() const { return _uri; }
std::string	HTTPRequest::getMethod() const { return _method; }

/* serialize */



/* bad request exception */
const char *HTTPRequest::BadRequestException::what() const throw()
{
	return ("Bad HTTP request");
}

/* parser */

#include <vector>
#include <string>

void HTTPRequest::parse(const std::string &input)
{
	std::istringstream	iss(input);
	std::string			line;

	std::getline(iss, line);
	utils::sanitizeline(line); /* need to do these to operations in one line for the sake of elegance! */

	parseRequestLine(line);

	std::vector<std::string>	header_lines;
	std::getline(iss, line);
	utils::sanitizeline(line);

	while (line != "")
	{
		if (iss.eof())
			throw BadRequestException();
		header_lines.push_back(line);
		std::getline(iss, line);
		utils::sanitizeline(line);
	}
	parseHeaders(header_lines);

}

void	HTTPRequest::parseRequestLine(std::string line)
{
	std::istringstream input(line);

	input >> _method >> _uri >> "HTTP" >> "/" >> _version.major >> "." >> _version.minor;

	if (input.fail())
		throw BadRequestException();
}

void	HTTPRequest::parseHeaders(std::vector<std::string> lines)
{
	for (unsigned int i = 0; i < lines.size(); i++)
	{
		std::string	fieldname;
		std::string	fieldvalue;

		size_t pos = lines[i].find(':');
		if (pos == std::string::npos)
			throw BadRequestException();

		fieldname = lines[i].substr(0, pos);
		if (fieldname.find_first_of(LINEAR_WHITESPACE) != std::string::npos) /* reject if there is whitespace in the fieldname */
			throw BadRequestException();

		fieldvalue = lines[i].substr(pos + 1, lines[i].size() - pos - 1); /* trim right and left optional whitespace */
		utils::trim(fieldvalue);

		/*
			if field-name is not present in map, insert the values
			else if it is already present, append the values

			fieldname is case-insensitive!
		*/
		std::string&	content = _headers[fieldname];
		if (content == "")
			content = fieldvalue;
		else
			content += ", " + fieldvalue;
	}
}

std::ostream &operator<<(std::ostream &o, const HTTPRequest &req)
{
	o << "method: " << req.getMethod() << ", target: " << req.getURI() << ", HTTP-version: " << req.getVersion().major << "." << req.getVersion().minor << std::endl;

	return (o);
}

/*
	this code below is copied from stackoverflow. It allows to match strings
	like with scanf but better!
	Source: https://stackoverflow.com/questions/71325940/how-to-translate-scanf-exact-matching-into-modern-c-stringstream-reading
*/
#include <cctype>

std::istream &operator>>(std::istream &is, char const *s)
{

	if (s == nullptr)
		return is;

	if (is.flags() & std::ios::skipws)
	{
		while (std::isspace(is.peek()))
			is.ignore(1);

		while (std::isspace((unsigned char)*s))
			++s;
	}

	while (*s && is.peek() == *s)
	{
		is.ignore(1);
		++s;
	}
	if (*s)
		is.setstate(std::ios::failbit);
	return is;
}