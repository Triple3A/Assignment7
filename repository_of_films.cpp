#include "repository_of_films.hpp"

Repository_of_films::Repository_of_films()
{
	id_counter = 1;
}

void Repository_of_films::add_film(Film* film)
{
	 if(is_duplicate(film))
		throw Bad_request();
    film->purchased();
	film->set_id(id_counter);
	id_counter++;
	films.push_back(film);
}

Film* Repository_of_films::search_film_by_id(int id)
{
	for(int i = 0; i < films.size(); i++)
	{
		if(films[i]->get_id() == id)
			return films[i];
	}
	throw Not_found();
}

int Repository_of_films::get_position_of_film(int id)
{
	for(int i = 0; i < films.size(); i++)
	{
		if(films[i]->get_id() == id)
			return i;
	}
	throw Not_found();
}

void Repository_of_films::delete_film(int id)
{
	int position = get_position_of_film(id);
    Film* film = search_film_by_id(id);
    film->deleted();
	films.erase(films.begin() + position);
}

std::vector<Film*> Repository_of_films::get_films(std::string _name, std::string _price, std::string min_year, std::string max_year, std::string _director, std::string min_rate)
{
	std::vector<Film*> searched_films;
	searched_films = search_films_by_name(films, _name);
	searched_films = search_films_by_price(searched_films, _price);
	searched_films = search_films_by_min_year(searched_films, min_year);
	searched_films = search_films_by_max_year(searched_films, max_year);	
	searched_films = search_films_by_director(searched_films, _director);
	searched_films = search_films_by_min_rate(searched_films, min_rate);
	return searched_films;
}

std::vector<Film*> Repository_of_films::search_films_by_name(std::vector<Film*> _films, std::string _name)
{
	if(is_null(_name))
		return _films;
	std::vector<Film*> searched;
	for(int i = 0; i < _films.size(); i++)
	{
		if(_films[i]->get_name() == _name)
			searched.push_back(_films[i]);
	}
	return searched;
}

std::vector<Film*> Repository_of_films::search_films_by_price(std::vector<Film*> _films, std::string _price)
{
	if(is_null(_price))
		return _films;
	int price = std::stoi(_price);
	std::vector<Film*> searched;
	for(int i = 0; i < _films.size(); i++)
	{
		if(_films[i]->get_price() == price)
			searched.push_back(_films[i]);
	}
	return searched;
}

std::vector<Film*> Repository_of_films::search_films_by_min_year(std::vector<Film*> _films, std::string min_year)
{
	if(is_null(min_year))
		return _films;
	int min = std::stoi(min_year);
	std::vector<Film*> searched;
	for(int i = 0; i < _films.size(); i++)
	{
		if(_films[i]->get_year() >= min)
			searched.push_back(_films[i]);
	}
	return searched;
}

std::vector<Film*> Repository_of_films::search_films_by_max_year(std::vector<Film*> _films, std::string max_year)
{
	if(is_null(max_year))
		return _films;
	int max = std::stoi(max_year);
	std::vector<Film*> searched;
	for(int i = 0; i < _films.size(); i++)
	{
		if(_films[i]->get_year() <= max)
			searched.push_back(_films[i]);
	}
	return searched;
}

std::vector<Film*> Repository_of_films::search_films_by_director(std::vector<Film*> _films, std::string _director)
{
	if(is_null(_director))
		return _films;
	std::vector<Film*> searched;
	for(int i = 0; i < _films.size(); i++)
	{
		if(_films[i]->get_director() == _director)
			searched.push_back(_films[i]);
	}
	return searched;
}

std::vector<Film*> Repository_of_films::search_films_by_min_rate(std::vector<Film*> _films, std::string min_rate)
{
	if(is_null(min_rate))
		return _films;
	float min = std::stof(min_rate);
	std::vector<Film*> searched;
	for(int i = 0; i < _films.size(); i++)
	{
		if(_films[i]->get_rate() >= min)
			searched.push_back(_films[i]);
	}
	return searched;
}

bool Repository_of_films::is_null(std::string s)
{
	if(s == "")
		return true;
	return false;
}

std::vector<Film*> Repository_of_films::get_all_films()
{
	return films;
}


bool Repository_of_films::is_duplicate(Film* film)
{
	for(int i = 0; i < films.size(); i++)
	{
		if(films[i] == film)
			return true;
	}
	return false;
}

std::vector<Film*> Repository_of_films::user_can_buy(User* user)
{
    std::vector<Film*> films_can_buy;
    for(int i = 0; i < films.size(); i++)
    {
        if(films[i]->get_price() <= user->get_account())
            films_can_buy.push_back(films[i]);
    }
    return films_can_buy;
}
