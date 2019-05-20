#ifndef FILM_H
#define FILM_H

#include <vector>
#include "publisher.hpp"
// #include "comment.hpp"

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
	// void add_comment(Comment* comment);
	void add_score(float score);
	int get_number_of_scores();
	void calculate_rate();
	bool is_weak();
	bool is_normal();
	bool is_good();
	void set_publisher(User* _publisher);
private:
	User* publisher;
	// Repository_of_comments* comments;
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