#ifndef USER_H
#define USER_H
#include <iostream>
#include <vector>

class Permission_denied {};
class Not_found {};
class Film;

class User
{
public:
	User(std::string _name, std::string _password, std::string _email, int _age, bool _publisher);
	// ~User();
	std::string get_name();
	std::string get_password();
	std::string get_email();
	int get_age();
	int get_id();
	int get_account();
	// User operator=(User& user);
	std::vector<Film*> get_films();
	std::vector<std::string> get_and_read_unread_messages();
	std::vector<std::string> get_read_messages();
	void set_id(int _id);
	
	void add_unread_message(std::string);
	void show_purchased();
	void post_comment(int film_id, std::string);
	void post_rate(Film* film, float score);
	Film* search_film(int film_id);
	void buy(Film* film);
	void add_film_to_purchased(Film* film);
	void get_details_of_film(int film_id);
	bool is_purchased(int film_id);
	void charge_money(int amount);
	bool is_publisher();
	virtual void post_film(Film* film) {};
	virtual int get_money() {};
	virtual void add_follower(User* user) {};
	virtual Film* search_published_film(int film_id) {};
	virtual void delete_film(int film_id) {};
	virtual int get_position_of_element(int film_id) {};
	virtual std::vector<User*> get_followers() {};
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