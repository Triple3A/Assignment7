#ifndef FILM_H
#define FILM_H

#include <vector>
#include "comment.hpp"

class Comment;

class Film
{
public:
	Film(int _id, std::string _name, std::string _year, int _length, int _price, std::string _summary, std::string _director);
	~Film();
	void sold();
	void edit(std::vector<string> edits);
	int get_id();
	void add_comment(Comment* comment);
	void add_score(float score);
	int get_number_of_scores();
	void calculate_rate();
	bool is_weak();
	bool is_normal();
	bool is_good();
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