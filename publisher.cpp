#include "publisher.hpp"

Publisher::Publisher(std::string _name, std::string _password, std::string _email, int _age, bool _publisher)
	: User(_name, _password, _email, _age, _publisher)
{
	cash = 0;
}

void Publisher::post_film(Film* film)
{
	published_films.push_back(film);
	film->set_publisher(this);
	send_notif_to_followers();
}

int Publisher::get_money()
{
	int last_cash = cash;
	cash = 0;
	return last_cash;
}

void Publisher::add_money(int amount)
{
	cash += amount;
}

void Publisher::add_follower(User* user)
{
	followers.push_back(user);
}

void Publisher::send_notif_to_followers()
{
	for(int i = 0; i < followers.size(); i++)
	{
		send_notif_to_follower(followers[i]);
	}
}

void Publisher::send_notif_to_follower(User* follower)
{
	std::string message;
	message = "Publisher " + name;
	message += " with id " + std::to_string(id);
	message += " register new film.";
	follower->add_unread_message(message);
}