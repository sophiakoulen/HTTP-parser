#include <iostream>
#include "HTTPRequest.hpp"

using namespace std;

int main()
{
	string str1 = "GET /truc_bidule HTTp /42.43\r\n";

	try
	{
		HTTPRequest req1(str1);
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