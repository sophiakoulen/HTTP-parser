#ifndef HTTP_REQUEST_H
# define HTTP_REQUEST_H

# include <string>
# include <ostream>
# include <exception>
# include <map>

typedef struct
{
	int	major;
	int	minor;
}	t_version;

class HTTPRequest
{
	public:

		HTTPRequest(std::string& input);
		HTTPRequest(const HTTPRequest& cpy);
		~HTTPRequest();
		HTTPRequest&	operator=(const HTTPRequest& rhs);

		/* getters */
		int			getStatus() const;
		t_version	getVersion() const;
		std::string	getURI() const;
		std::string	getMethod() const;

		/* serialize */
		std::string	serialize() const;

		/* bad request exception */
		class BadRequestException: public std::exception
		{
			virtual const char	*what() const throw();
		};

	private:

		/* status */
		int			_status;

		/* request line */
		t_version	_version;
		std::string	_uri;
		std::string	_method;

		/* headers */
		std::map<std::string, std::string>	_headers;
		/* body */

		/* default constructor */
		HTTPRequest();

		/* parser */
		void		parse(const std::string& input);
		void		parseRequestLine(std::string line);
		void		parseHeaders(std::vector<std::string> lines);
};

std::ostream&	operator<<(std::ostream& o, const HTTPRequest& req);

#endif /* HTTP_REQUEST_H */