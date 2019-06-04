#ifndef WEBSITE_HANDLER_HPP
#define WEBSITE_HANDLER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include "repository_of_users.hpp"
#include "repository_of_films.hpp"
#include "server/server.hpp"
#include "my_server.hpp"


#define F first
#define S second

bool cmp(std::pair<int, int> x, std::pair <int, int> y);


class Website_handler
{
public:
	Website_handler(MyServer* _server);
    ~Website_handler();
	void run();
	void add_money(int amount);
    
    bool is_publisher();
    
    int get_id_of_login_user();
	
	
    void signup(std::string username, std::string password, int age, std::string email, bool is_publisher);
	void login(std::string username, std::string password);
    void logout();
	void post_films(std::string name, int price, int year, int length, std::string director, std::string summary);
	void money(int amount);
	void buy(int film_id);
	void rate(int film_id, float score);
	void comments(int film_id, std::string content);
	
	void sort_by_id(std::vector<Film*>&);

    void show_films(std::string director, std::string& body);
    void show_available_films(std::string& body);
    void show_purchased_films(std::string& body);
	void show_details_of_film(int film_id, std::string& body);
    void show_comments(int film_id, std::string& body);
	void recommend_films(int film_id, std::string& body);


	void delete_film(int film_id);
	
    void print_films(std::vector<Film*>, std::string& body);
    void print_purchased_films(std::vector<Film*> _films, std::string& body);
	void print_details_of_film(Film* film, std::string& body);
	void print_comments(std::vector<Comment*> comments, std::string& body);
	void print_recommendation_films(std::vector<Film*> recommendation_films, std::string& body);
    
    void add_film_to_matrix();
    void update_matrix();
private:
	int cash;
    MyServer *server;
	Repository_of_films* films;
	Repository_of_users* users;
    std::vector<std::vector<int> > adjacency_matrix;
	User* login_user;
};
#include "handlers.hpp"

#endif
