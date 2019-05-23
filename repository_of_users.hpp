#ifndef REPOSITORY_OF_USERS_H
#define REPOSITORY_OF_USERS_H

#include "user.hpp"

class User;

const std::string USERS_FILE_NAME = "Users.txt";

class Repository_of_users
{
public:
	Repository_of_users();
	void add_user(User*);
	User* search_user(std::string username, std::string password);
	User* search_publisher(int user_id);
	bool is_duplicate(User* user);
private:
	std::vector<User*> users;
	int id_counter;
};
#endif