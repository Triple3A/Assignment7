#include <iostream>
#include <vector>
#include "website_handler.hpp"

using namespace std;

int main()
{
	Website_handler web;
	string input;
	input = web.get_input();
	web.separator(input);
	web.processing_inputs();
}