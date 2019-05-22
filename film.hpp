#ifndef FILM_H
#define FILM_H

#include <vector>
#include "publisher.hpp"
#include "repository_of_comments.hpp"

const float WEAK_RATE = 5.0;
const float NORMAL_RATE = 8.0;

class Publisher;
// class Comment;

class Film
{
public:
	Film(std::string _name, std::string _year, int _length, int _price, std::string _summary, std::string _director);
	// ~Film();
	void sold();
	void edit(std::vector<std::string> edits);
	int get_id();
	void set_id(int _id);
	int get_price();
	std::string get_name();
	void add_comment(Comment* comment);
	void add_score(float score);
	void calculate_rate();
	int calculate_price();
	float get_rate();
	bool is_weak();
	bool is_normal();
	bool is_good();
	void set_publisher(Publisher* _publisher);
	Publisher* get_publisher();
private:
	Publisher* publisher;
	Repository_of_comments* comments;
	int id;
	std::string name;
	std::string year;
	int length;
	int price;
	std::string summary;
	std::string director;
	std::vector<float> scores;
	int number_of_scores;
	float rate;
};
#endif