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


	HTTPRequest req1(str1);

	cout<<endl;

	if (req1.getHasValidSyntax())
		cout<<req1;
	else
		cout<<"Invalid syntax"<<endl;

	cout<<endl;

	return 0;
}