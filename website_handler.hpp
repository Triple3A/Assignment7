#ifndef WEBSITE_HANDLER_HPP
#define WEBSITE_HANDLER_HPP

#include <iostream>
#include <vector>
#include <string>
#include "repository_of_users.hpp"
// #include "repository_films.hpp"

const char SPACE = ' ';
const std::string PUT = "PUT";
const std::string GET = "GET";
const std::string POST = "POST";
const std::string DELETE = "DELETE";
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
const std::string USERNAME = "username";
const std::string PASSWORD = "password";
const std::string AGE = "age";
const std::string EMAIL = "email";

class Website_handler
{
public:
	Website_handler();
	// ~Website_handler();
	std::string get_input();
	void separator(std::string);
	void processing_inputs();
	// void read_files();
	// void add_to_files();
	void add_money(int amount);
	
	bool is_get();
	bool is_put();
	bool is_post();
	bool is_delete();
	bool is_signup();
	bool is_login();
	bool is_films();
	bool is_money();
	bool is_replies();
	bool is_followers();
	bool is_buy();
	bool is_rate();
	bool is_comments();
	bool is_published();
	bool is_purchased();
	bool is_notifications();
	
	// void put();
	// void get();
	void post();
	// void _delete();
	
	void signup();
	// void login();
	// void films();
	// void money();
	// void replies();
	// void followers();
	// void buy();
	// void rate();
	// void comments();
	//
	// void get_followers();
	// void published();
	// void get_films();
	// void purchased();
	// void notifications();
	//
	// void put_film();
	//
	// void delete_film();
	// void delete_comment();
private:
	int cash;
	std::vector<std::string> inputs;
	// Repository_of_films* films;
	Repository_of_users* users;
	User* login_user;
};
#endif