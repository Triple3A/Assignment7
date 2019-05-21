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

User* Repository_of_users::search_user(std::string username, std::string password)
{
	for(int i = 0; i < users.size(); i++)
	{
		if(users[i]->get_name() == username && users[i]->get_password() == password)
			return users[i];
	}
	throw Bad_request();
}

User* Repository_of_users::search_publisher(int user_id)
{
	for(int i = 0; i < users.size(); i++)
	{
		if(users[i]->get_id() == user_id && users[i]->is_publisher())
			return users[i];
	}
	throw Not_found();
}