#include "publisher.hpp"

Publisher::Publisher(std::string _name, std::string _password, std::string _email, int _age, bool _publisher)
	: User(_name, _password, _email, _age, _publisher)
{
	cash = 0;
}

void Publisher::post_film(Film* film)
{
	published_films.push_back(film);
	film->set_publisher(this);
	send_notif_to_followers();
}

int Publisher::get_money()
{
	int last_cash = cash;
	cash = 0;
	return last_cash;
}

void Publisher::add_money(int amount)
{
	cash += amount;
}

void Publisher::add_follower(User* user)
{
	followers.push_back(user);
}

void Publisher::send_notif_to_followers()
{
	for(int i = 0; i < followers.size(); i++)
	{
		send_notif_to_follower(followers[i]);
	}
}

void Publisher::send_notif_to_follower(User* follower)
{
	std::string message;
	message = "Publisher " + name;
	message += " with id " + std::to_string(id);
	message += " register new film.";
	follower->add_unread_message(message);
}

Film* Publisher::search_published_film(int film_id)
{
	for(int i = 0; i < published_films.size(); i++)
	{
		if(published_films[i]->get_id() == film_id)
			return published_films[i];
	}
	throw Not_found();
}

int Publisher::get_position_of_element(int film_id)
{
	for(int i = 0; i < published_films.size(); i++)
	{
		if(published_films[i]->get_id() == film_id)
			return i;
	}
	throw Not_found();
}

void Publisher::delete_film(int film_id)
{
	int position = get_position_of_element(film_id);
	published_films.erase(published_films.begin() + position);
}

std::vector<User*> Publisher::get_followers()
{
	return followers;
}

std::vector<Film*> Publisher::get_published_films(std::string _name, std::string _price, std::string min_year, std::string max_year, std::string _director, std::string min_rate)
{
	std::vector<Film*> searched_films;
	searched_films = search_films_by_name(published_films, _name);
	searched_films = search_films_by_price(searched_films, _price);
	searched_films = search_films_by_min_year(searched_films, min_year);
	searched_films = search_films_by_max_year(searched_films, max_year);	
	searched_films = search_films_by_director(searched_films, _director);
	searched_films = search_films_by_min_rate(searched_films, min_rate);
	return searched_films;
}

std::vector<Film*> Publisher::search_films_by_min_rate(std::vector<Film*> films, std::string min_rate)
{
	if(is_null(min_rate))
		return films;
	float min = std::stof(min_rate);
	std::vector<Film*> searched;
	for(int i = 0; i < films.size(); i++)
	{
		if(films[i]->get_rate() >= min)
			searched.push_back(films[i]);
	}
	return searched;
}




