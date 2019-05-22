#ifndef REPOSITORY_OF_FILMS_H
#define REPOSITORY_OF_FILMS_H

#include "film.hpp"

class Repository_of_films
{
public:
	Repository_of_films();
	// ~Repository_of_films();
	void add_film(Film* film);
	Film* search_film_by_id(int id);
	int get_position_of_film(int id);
	void delete_film(int id);
	// void read_file(std::string);
	// void add_to_file(Film*);
private:
	std::vector<Film*> films;
	int id_counter;
};
#endif