#ifndef USER_H
#define USER_H
#include <iostream>
#include <vector>
#include "exceptions.hpp"

class Film;

class User
{
public:
	User(std::string _name, std::string _password, std::string _email, int _age, bool _publisher);
	std::string get_name();
	std::string get_password();
	std::string get_email();
	int get_age();
	int get_id();
	int get_account();
	std::vector<Film*> get_films();
	std::vector<std::string> get_and_read_unread_messages();
	std::vector<std::string> get_read_messages();
	void set_id(int _id);
	
	void add_unread_message(std::string);
	std::vector<Film*> get_purchased(std::string _name, std::string price, std::string min_year, std::string max_year, std::string _director);
	void post_comment(int film_id, std::string);
	void post_rate(Film* film, float score);
	Film* search_film(int film_id);
	void buy(Film* film);
	void add_film_to_purchased(Film* film);
	void get_details_of_film(int film_id);
	void charge_money(int amount);
	
	bool is_purchased(Film* film);
	bool is_publisher();
	bool is_null(std::string s);
	
	std::vector<Film*> search_films_by_name(std::vector<Film*>, std::string _name);
	std::vector<Film*> search_films_by_price(std::vector<Film*>, std::string _price);
	std::vector<Film*> search_films_by_min_year(std::vector<Film*>, std::string min_year);
	std::vector<Film*> search_films_by_max_year(std::vector<Film*>, std::string max_year);
	std::vector<Film*> search_films_by_director(std::vector<Film*>, std::string _director);
		
		
	virtual void post_film(Film* film) {};
	virtual int get_money() {};
	virtual void add_follower(User* user) {};
	virtual Film* search_published_film(int film_id) {};
	virtual void delete_film(int film_id) {};
	virtual int get_position_of_element(int film_id) {};
	virtual std::vector<User*> get_followers() {};
	virtual std::vector<Film*> get_published_films(std::string _name, std::string price, std::string min_year, std::string max_year, std::string _director, std::string min_rate) {};
protected:
	std::string name;
	std::string password;
	std::string email;
	int age;
	bool publisher;
	int id;
	int account;
	std::vector<Film*> purchased_films;
	std::vector<std::string> unread_messages;
	std::vector<std::string> read_messages;
};

#include "film.hpp"
#endif