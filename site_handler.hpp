#ifndef SITE_HANDLER_H
#define SITE_HANDLER_H

#include "repository_of_users.hpp"
#include "repository_films.hpp"

class Site_Handler
{
public:
	std::string get_input();
	std::vector<std::string> seperator(std::string);
	void processing_inputs(std::vector<std::string>);
	void read_files();
	void add_to_files();
	void add_money(int amount);
private:
	int cash;
	Repository_of_films* films;
	Repository_of_users* users;
};
#endif