#include <iostream>
#include "HTTPRequest.hpp"

using namespace std;

int main()
{
	string str1 = "GET /truc_bidule HTTP /42.43\r\nfield-name:field,value    	\n";
	string str2 = "POST / HTTP/2.0\r\nhello: truc\r\nHost: truc-bidule\r\nhello: world\r\n";
	string str3 = "POST / HTTP/1.1\r\nhost:";
	string str4 = "POST / HTTP/1.1";
	string str5 = "";

	try
	{
		HTTPRequest req1(str2);
		cout<<req1;
	}
	catch (HTTPRequest::BadRequestException& e)
	{
		cout<<"parsing error"<<endl;
	}
/*
	string str2 = "\r\nDELETE /truc_bidule HTTP/1.0";
	HTTPRequest req2(str2);
	cout<<req2;

	string str3 = "DELETE \t *     \r HTTP/1.0";
	HTTPRequest req3(str2);
	cout<<req2;
*/
	return 0;
}