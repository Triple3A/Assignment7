#include "publisher.hpp"

Publisher::Publisher(std::string _name, std::string _password, std::string _email, int _age, bool _publisher)
	: User(_name, _password, _email, _age, _publisher)
{
	cash = 0;
}

void Publisher::post_film(Film* film)
{
	published_films.push_back(film);
}