#ifndef REPOSITORY_OF_USERS_H
#define REPOSITORY_OF_USERS_H

#include "user.hpp"

const std::string USERS_FILE_NAME = "Users.txt";

class Repository_of_users
{
public:
	Repository_of_users();
	~Repository_of_users();
	void add_user(User*);
	// void read_file(std::string);
	// void add_to_file();
private:
	std::vector<User*> users;
	int id_counter;
};
#endif