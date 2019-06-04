#ifndef REPOSITORY_OF_FILMS_H
#define REPOSITORY_OF_FILMS_H

#include "film.hpp"

class Repository_of_films
{
public:
	Repository_of_films();
	
	bool is_null(std::string s);
	bool is_duplicate(Film* film);
	
	void add_film(Film* film);
	Film* search_film_by_id(int id);
	int get_position_of_film(int id);
	void delete_film(int id);
	std::vector<Film*> get_films(std::string _name, std::string _price, std::string min_year, std::string max_year, std::string _director, std::string min_rate);
	std::vector<Film*> get_all_films();
    
	std::vector<Film*> search_films_by_name(std::vector<Film*>, std::string _name);
	std::vector<Film*> search_films_by_price(std::vector<Film*>, std::string _price);
	std::vector<Film*> search_films_by_min_year(std::vector<Film*>, std::string min_year);
	std::vector<Film*> search_films_by_max_year(std::vector<Film*>, std::string max_year);
	std::vector<Film*> search_films_by_director(std::vector<Film*>, std::string _director);
	std::vector<Film*> search_films_by_min_rate(std::vector<Film*>, std::string min_rate);
    
    std::vector<Film*> user_can_buy(User* user);
private:
	std::vector<Film*> films;
	int id_counter;
};
#endif
