#include "repository_of_users.hpp"

Repository_of_users::Repository_of_users()
{
	id_counter = 1;
}

void Repository_of_users::add_user(User* user)
{
	user->set_id(id_counter);
	id_counter++;
	users.push_back(user);
}