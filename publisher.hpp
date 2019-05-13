#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "user.hpp"
#include "film.hpp"

class User;
class Film;

class Publisher : public User
{
public:
	~Publisher();
	int get_cash();
	std::vector<Film*> get_published_films();
	std::vector<User*> get_followers();
	
	void add_money(int amount);
	void delete_comment(int film_id, int comment_id);
	void post_replies(int film_id, int comment_id, std::string);
	void get_publish_films();
	void get_money();
	void get_followers();
	void delete_film(int film_id);
	void edit_film(int film_id, std::vector<std::string> edits);
	void post_film(Film* film);
private:
	int cash;
	std::vector<Film*> published_films;
	std::vector<User*> followers;
};
#endif