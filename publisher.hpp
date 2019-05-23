#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "user.hpp"
#include "film.hpp"

class Film;

class Publisher : public User
{
public:
	Publisher(std::string _name, std::string _password, std::string _email, int _age, bool _publisher);
	int get_cash();
	std::vector<Film*> get_published_films();
	virtual std::vector<User*> get_followers();
	
	void add_money(int amount);
	virtual void add_follower(User* user);
	void delete_comment(int film_id, int comment_id);
	void post_replies(int film_id, int comment_id, std::string);
	
	virtual std::vector<Film*> get_published_films(std::string _name, std::string price, std::string min_year, std::string max_year, std::string _director, std::string min_rate);
	virtual int get_money();
	virtual int get_position_of_element(int film_id);
	
	virtual void delete_film(int film_id);
	void edit_film(int film_id, std::vector<std::string> edits);
	virtual void post_film(Film* film);
	virtual Film* search_published_film(int film_id);
	void send_notif_to_followers();
	void send_notif_to_follower(User*);
	
	std::vector<Film*> search_films_by_min_rate(std::vector<Film*>, std::string min_rate);
private:
	int cash;
	std::vector<Film*> published_films;
	std::vector<User*> followers;
};
#endif