#ifndef WEBSITE_HANDLER_HPP
#define WEBSITE_HANDLER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include "repository_of_users.hpp"
#include "repository_of_films.hpp"

#define F first
#define S second

const char SPACE = ' ';
const std::string ADMIN = "admin";
const std::string PUT_FILMS = "put_films";
const std::string GET = "GET";
const std::string POST = "POST";
const std::string DELETE_FILMS = "delete_films";
const std::string DELETE_COMMENTS = "delete_comments";
const std::string SIGNUP = "signup";
const std::string LOGIN = "login";
const std::string FILMS = "films";
const std::string MONEY = "money";
const std::string REPLIES = "replies";
const std::string FOLLOWERS = "followers";
const std::string BUY = "buy";
const std::string RATE = "rate";
const std::string COMMENTS = "comments";
const std::string PUBLISHED = "published";
const std::string PURCHASED = "purchased";
const std::string NOTIFICATIONS = "notifications";
const std::string READ = "read";
const std::string USERNAME = "username";
const std::string PASSWORD = "password";
const std::string AGE = "age";
const std::string EMAIL = "email";
const std::string PUBLISHER = "publisher";
const std::string NAME = "name";
const std::string YEAR = "year";
const std::string LENGTH = "length";
const std::string PRICE = "price";
const std::string SUMMARY = "summary";
const std::string DIRECTOR = "director";
const std::string AMOUNT = "amount";
const std::string FILM_ID = "film_id";
const std::string SCORE = "score";
const std::string USER_ID = "user_id";
const std::string CONTENT = "content";
const std::string COMMENT_ID = "comment_id";
const std::string LIMIT = "limit";
const std::string MIN_YEAR = "min_year";
const std::string MAX_YEAR = "max_year";
const std::string MIN_RATE = "min_rate";
const std::string LOGOUT = "logout";
const int PRECISION = 2;

bool cmp(std::pair<int, int> x, std::pair <int, int> y);

class Website_handler
{
public:
	Website_handler();
	~Website_handler();
	void separator(std::string);
	void processing_inputs();
	void add_money(int amount);
	
	bool is_get();
	bool is_put();
	bool is_post();
	bool is_delete();
	bool is_signup();
	bool is_login();
	bool is_films();
    bool is_put_films();
    bool is_delete_films();
	bool is_money();
	bool is_replies();
	bool is_followers();
	bool is_buy();
	bool is_rate();
	bool is_comments();
    bool is_delete_comments();
	bool is_published();
	bool is_purchased();
	bool is_notifications();
	bool is_notifications_read();
    bool is_logout();
    
	
	void get();
    void post();
	
	void signup();
	void login();
    void logout();
	void post_films();
	void money();
	void replies();
	void followers();
	void buy();
	void rate();
	void comments();
	
	void sort_by_id(std::vector<Film*>&);
	void sort_by_rate(std::vector<Film*>&);

	void show_followers();
    void get_money();
	void show_films();
	void show_details_of_film();
	void recommend_films(int film_id);
	void show_notifications();
	void show_notifications_read();

	void put_film();

	void delete_film();
	void delete_comment();
	
	void send_notif_buy_film(User* user, Publisher* publisher, Film* film);
	void send_notif_rate_film(User* user, Publisher* publisher, Film* film);
	void send_notif_to_following(User* user, User* publisher);
	void send_notif_add_comment(User*, Publisher*, Film*);
	void send_notif_reply_comment(User* owner, User* publisher);
	
	
	void print_notifications(std::vector<std::string> messages, int limit);
	void print_ok();
	void print_films(std::vector<Film*>);
	void print_details_of_film(Film* film);
	void print_comments(std::vector<Comment*> comments);
	void print_recommendation_films(std::vector<Film*> recommendation_films);
    
    void add_film_to_matrix();
    void update_matrix();
private:
	int cash;
	std::vector<std::string> inputs;
	Repository_of_films* films;
	Repository_of_users* users;
    std::vector<std::vector<int> > adjacency_matrix;
	User* login_user;
};
#endif
