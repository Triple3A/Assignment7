#include "repository_of_films.hpp"

Repository_of_films::Repository_of_films()
{
	id_counter = 1;
}

void Repository_of_films::add_film(Film* film)
{
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
	// throw Not_found();
}