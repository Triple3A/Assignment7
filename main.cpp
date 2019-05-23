#include <iostream>
#include <vector>
#include "website_handler.hpp"

using namespace std;

int main()
{
	Website_handler web;
	string input;
	while(getline(cin, input))
	{
		try
		{
			web.separator(input);
			web.processing_inputs();
		}
		catch(exception &ex)
		{
			cout << ex.what() << endl;
		}
	}
}