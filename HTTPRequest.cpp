#include "HTTPRequest.hpp"
#include <iostream>
#include <sstream>

std::istream &operator>>(std::istream &is, char const *s);

HTTPRequest::HTTPRequest(std::string &input)
{
	std::cout << "HTTPRequest ctor" << std::endl;
	parse(input);
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


/* bad request exception */
const char *HTTPRequest::BadRequestException::what() const throw()
{
	return ("Bad HTTP request");
}

/* parser */

void HTTPRequest::parse(const std::string &input)
{
	std::string cpy;
	std::string line;

	cpy = input;
	line = getline(cpy);
	parseRequestLine(line);

	std::vector<std::string>	header_lines;
	line = getline(cpy);
	while (line != "")
	{
		header_lines.push_back(line);
		line = getline(cpy);
	}
	parseHeaders(header_lines);

}

std::string HTTPRequest::getline(std::string &input)
{
	std::string line;
	unsigned int i;

	for (i = 0; i < input.size(); i++)
	{
		if (input[i] == '\n')
			break;
		line += input[i];
	}

	if (input[i] == '\n')
		i++;

	input = input.substr(i, input.size() - i);

	/* remove any preceding \r */
	for (i = line.length() - 1; i >= 0 && line[i] == '\r'; i--)
		;
	line.resize(i + 1);

	/* replace bare cr with sp*/
	for (i = 0; i < line.size(); i++)
	{
		if (line[i] == '\r')
			line[i] = ' ';
	}

	return (line);
}

void	HTTPRequest::parseRequestLine(std::string line)
{
	std::istringstream input(line);

	input >> _method >> _uri >> "HTTP" >> "/" >> _version.major >> "." >> _version.minor;

	if (input.fail())
		throw BadRequestException();
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