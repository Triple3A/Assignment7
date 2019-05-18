#include "user.hpp"

User::User(std::string _name, std::string _password, std::string _email, int _age, bool _publisher)
	: name(_name), password(_password), email(_email), age(_age), publisher(_publisher) 
{
	account = 0;
}

void User::set_id(int _id)
{
	id = _id;
}

int User::get_id()
{
	return id;
}