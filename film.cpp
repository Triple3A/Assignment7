#include "film.hpp"

Film::Film(std::string _name, std::string _year, int _length, int _price, std::string _summary, std::string _director)
	: name(_name), year(_year), length(_length), price(_price), summary(_summary), director(_director) 
{
	rate = 0.0;
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
	if(this->is_weak())
		return price * 80 / 100;
	else if(this->is_normal())
		return price * 90 / 100;
	else 
		return price * 95 / 100;
}

std::string Film::get_name()
{
	return name;
}