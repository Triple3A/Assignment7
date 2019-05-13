#ifndef REPOSITORY_OF_FILMS_H
#define REPOSITORY_OF_FILMS_H

#include "film.hpp"

class Repository_of_films
{
public:
	Repository_of_films();
	~Repository_of_films();
	void add_film();
	void read_file(std::string);
	void add_to_file(Film*);
private:
	std::vector<Film*> films;
	int counter;
};