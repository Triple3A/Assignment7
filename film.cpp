#include "film.hpp"

Film::Film(std::string _name, std::string _year, int _length, int _price, std::string _summary, std::string _director)
	: name(_name), year(_year), length(_length), price(_price), summary(_summary), director(_director) {};

void Film::set_id(int _id)
{
	id = _id;
}

int Film::get_id()
{
	return id;
}

void Film::set_publisher(User* _publisher)
{
	publisher = _publisher;
}
