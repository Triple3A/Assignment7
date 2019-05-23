#include "film.hpp"

Film::Film(std::string _name, int _year, int _length, int _price, std::string _summary, std::string _director)
	: name(_name), year(_year), length(_length), price(_price), summary(_summary), director(_director) 
{
	rate = 0.0;
	comments = new Repository_of_comments();
};

void Film::set_id(int _id)
{
	id = _id;
}

int Film::get_id()
{
	return id;
}

void Film::set_publisher(Publisher* _publisher)
{
	publisher = _publisher;
}

int Film::get_price()
{
	return price;
}

Publisher* Film::get_publisher()
{
	return publisher;
}

bool Film::is_weak()
{
	if(rate < WEAK_RATE)
		return true;
	return false;
}

bool Film::is_normal()
{
	if(rate >= WEAK_RATE && rate < NORMAL_RATE)
		return true;
	return false;
}

bool Film::is_good()
{
	if(rate >= NORMAL_RATE)
		return true;
	return false;
}

int Film::calculate_price()
{
	if(is_weak())
		return price * 80 / 100;
	else if(is_normal())
		return price * 90 / 100;
	else 
		return price * 95 / 100;
}

std::string Film::get_name()
{
	return name;
}

void Film::add_score(float score)
{
	scores.push_back(score);
	calculate_rate();
}

void Film::calculate_rate()
{
	float sum = 0.0;
	for(int i = 0 ;i < scores.size(); i++)
	{
		sum += scores[i];
	}
	rate = sum / scores.size();
}

void Film::add_comment(Comment* comment)
{
	comments->add_comment(comment);
}

Comment* Film::search_comment(int comment_id)
{
	return comments->search_comment(comment_id);
}

void Film::delete_comment(int comment_id)
{
	comments->delete_comment(comment_id);
}

void Film::edit(std::string _name, std::string _year, std::string _length, std::string _price, std::string _summary, std::string _director)
{
	if(is_not_null(_name))
		name = _name;
	if(is_not_null(_year))
		year = std::stoi(_year);
	if(is_not_null(_summary))
		summary = _summary;
	if(is_not_null(_length))
		length = std::stoi(_length);
	if(is_not_null(_price))
		price = std::stoi(_price);
	if(is_not_null(_director))
		director = _director;
}

bool Film::is_not_null(std::string s)
{
	if(s == "")
		return false;
	return true;
}

std::string Film::get_summary()	
{
	return summary;
}
std::string Film::get_director()
{
	return director;
}
int Film::get_year()
{
	return year;
}
int Film::get_length()
{
	return length;
}
float Film::get_rate()
{
	return rate;
}