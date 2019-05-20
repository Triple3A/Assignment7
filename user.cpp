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

// User User::operator=(User& user)
// {
// 	return user;
// }

std::string User::get_name()
{
	return name;
}

std::string User::get_password()
{
	return password;
}

bool User::is_publisher()
{
	return publisher;
}

void User::charge_money(int amount)
{
	account += amount;
}

void User::buy(Film* film)
{
	purchased_films.push_back(film);
	int price = film->get_price();
	account -= price; 
}

void User::add_unread_message(std::string message)
{
	unread_messages.push_back(message);
}