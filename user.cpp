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

std::string User::get_name()
{
	return name;
}

std::string User::get_password()
{
	return password;
}

std::string User::get_email()
{
	return email;
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

Film* User::search_film(int film_id)
{
	for(int i = 0; i < purchased_films.size(); i++)
	{
		if(purchased_films[i]->get_id() == film_id)
			return purchased_films[i];
	}
	throw Permission_denied();
}

void User::post_rate(Film* film, float score)
{
	film->add_score(score);
}

std::vector<std::string> User::get_and_read_unread_messages()
{
	std::vector<std::string> messages = unread_messages;
	unread_messages.clear();
	for(int i = 0; i < messages.size(); i++)
		read_messages.push_back(messages[i]);
	return messages;
}

std::vector<std::string> User::get_read_messages()
{
	return read_messages;
}

bool User::is_null(std::string s)
{
	if(s == "")
		return true;
	return false;
}

std::vector<Film*> User::get_purchased(std::string _name, std::string _price, std::string min_year, std::string max_year, std::string _director)
{
	std::vector<Film*> searched_films;
	searched_films = search_films_by_name(purchased_films, _name);
	searched_films = search_films_by_price(searched_films, _price);
	searched_films = search_films_by_min_year(searched_films, min_year);
	searched_films = search_films_by_max_year(searched_films, max_year);	
	searched_films = search_films_by_director(searched_films, _director);
	return searched_films;
}

std::vector<Film*> User::search_films_by_name(std::vector<Film*> films, std::string _name)
{
	if(is_null(_name))
		return films;
	std::vector<Film*> searched;
	for(int i = 0; i < films.size(); i++)
	{
		if(films[i]->get_name() == _name)
			searched.push_back(films[i]);
	}
	return searched;
}

std::vector<Film*> User::search_films_by_price(std::vector<Film*> films, std::string _price)
{
	if(is_null(_price))
		return films;
	int price = std::stoi(_price);
	std::vector<Film*> searched;
	for(int i = 0; i < films.size(); i++)
	{
		if(films[i]->get_price() == price)
			searched.push_back(films[i]);
	}
	return searched;
}

std::vector<Film*> User::search_films_by_min_year(std::vector<Film*> films, std::string min_year)
{
	if(is_null(min_year))
		return films;
	int min = std::stoi(min_year);
	std::vector<Film*> searched;
	for(int i = 0; i < films.size(); i++)
	{
		if(films[i]->get_year() >= min)
			searched.push_back(films[i]);
	}
	return searched;
}

std::vector<Film*> User::search_films_by_max_year(std::vector<Film*> films, std::string max_year)
{
	if(is_null(max_year))
		return films;
	int max = std::stoi(max_year);
	std::vector<Film*> searched;
	for(int i = 0; i < films.size(); i++)
	{
		if(films[i]->get_year() <= max)
			searched.push_back(films[i]);
	}
	return searched;
}

std::vector<Film*> User::search_films_by_director(std::vector<Film*> films, std::string _director)
{
	if(is_null(_director))
		return films;
	std::vector<Film*> searched;
	for(int i = 0; i < films.size(); i++)
	{
		if(films[i]->get_director() == _director)
			searched.push_back(films[i]);
	}
	return searched;
}

bool User::is_purchased(Film* film)
{
	for(int i = 0; i < purchased_films.size(); i++)
	{
		if(purchased_films[i] == film)
			return true;
	}
	return false;
}


