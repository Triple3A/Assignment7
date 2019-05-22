#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "user.hpp"
#include "film.hpp"

class Film;

class Publisher : public User
{
public:
	Publisher(std::string _name, std::string _password, std::string _email, int _age, bool _publisher);
	// ~Publisher();
	int get_cash();
	std::vector<Film*> get_published_films();
	std::vector<User*> get_followers();
	
	void add_money(int amount);
	virtual void add_follower(User* user);
	void delete_comment(int film_id, int comment_id);
	void post_replies(int film_id, int comment_id, std::string);
	void get_publish_films();
	virtual int get_money();
	// void get_followers();
	virtual void delete_film(int film_id);
	void edit_film(int film_id, std::vector<std::string> edits);
	virtual void post_film(Film* film);
	virtual Film* search_published_film(int film_id);
	virtual int get_position_of_element(int film_id);
	void send_notif_to_followers();
	void send_notif_to_follower(User*);
private:
	int cash;
	std::vector<Film*> published_films;
	std::vector<User*> followers;
};
#endif