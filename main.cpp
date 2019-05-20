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
		web.separator(input);
		web.processing_inputs();
	}
}