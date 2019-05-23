#include "website_handler.hpp"

Website_handler::Website_handler()
{
	cash = 0;
	users = new Repository_of_users();
	films = new Repository_of_films();
}

void Website_handler::print_ok()
{
	std::cout << "OK" << '\n';
}

void Website_handler::separator(std::string input)
{
	inputs.clear();
	for(int i = 0; i < input.size(); i++)
	{
		std::string word = "";
		while(input[i] != SPACE && i < input.size())
		{
			word += input[i];
			i++;
		}
		if(word != "")
			inputs.push_back(word);
	}
}

bool Website_handler::is_get()
{
	if(inputs[0] == GET)
		return true;
	return false;
}
bool Website_handler::is_put()
{
	if(inputs[0] == PUT)
		return true;
	return false;
}
bool Website_handler::is_post()
{
	if(inputs[0] == POST)
		return true;
	return false;
}
bool Website_handler::is_delete()
{
	if(inputs[0] == DELETE)
		return true;
	return false;
}
bool Website_handler::is_signup()
{
	if(inputs[1] == SIGNUP)
		return true;
	return false;
}
bool Website_handler::is_login()
{
	if(inputs[1] == LOGIN)
		return true;
	return false;
}
bool Website_handler::is_films()
{
	if(inputs[1] == FILMS)
		return true;
	return false;
}
bool Website_handler::is_money()
{
	if(inputs[1] == MONEY)
		return true;
	return false;
}
bool Website_handler::is_replies()
{
	if(inputs[1] == REPLIES)
		return true;
	return false;
}
bool Website_handler::is_followers()
{
	if(inputs[1] == FOLLOWERS)
		return true;
	return false;
}
bool Website_handler::is_buy()
{
	if(inputs[1] == BUY)
		return true;
	return false;
}
bool Website_handler::is_rate()
{
	if(inputs[1] == RATE)
		return true;
	return false;
}
bool Website_handler::is_comments()
{
	if(inputs[1] == COMMENTS)
		return true;
	return false;
}
bool Website_handler::is_published()
{
	if(inputs[1] == PUBLISHED)
		return true;
	return false;
}
bool Website_handler::is_purchased()
{
	if(inputs[1] == PURCHASED)
		return true;
	return false;
}
bool Website_handler::is_notifications_read()
{
	if(inputs[1] == NOTIFICATIONS && inputs[2] == READ)
		return true;
	return false;
}
bool Website_handler::is_notifications()
{
	if(inputs[1] == NOTIFICATIONS && inputs.size() == 2)
		return true;
	return false;
}

void Website_handler::processing_inputs()
{
	if(inputs.size() == 0)
		return;
	if(is_post())
	{
		post();
		print_ok();
	}
	else if(is_get())
	{
		get();
	}
	else if(is_put())
	{
		put();
		print_ok();
	}
	else if(is_delete())
	{
		_delete();
		print_ok();
	}
	else
		throw Bad_request();
}

void Website_handler::post()
{
	if(is_signup())
		signup();
	else if(is_login())
		login();
	else if(is_films())
		post_films();
	else if(is_money())
		money();
	else if(is_replies())
		replies();
	else if(is_followers())
		followers();
	else if(is_buy())
		buy();
	else if(is_rate())
		rate();
	else if(is_comments())
		comments();
	else
		throw Not_found();
}

void Website_handler::get()
{
	if(is_followers())
		show_followers();
	else if(is_published() || is_purchased() || (is_films() && inputs[3] != FILM_ID))
		show_films();
	else if(is_films())
	{
		show_details_of_film();
		recommend_films();
	}
	else if(is_notifications())
		show_notifications();
	else if(is_notifications_read())
		show_notifications_read();
	else
		throw Not_found();
}

void Website_handler::put()
{
	if(is_films())
		put_film();
	else
		throw Not_found();
}

void Website_handler::_delete()
{
	if(is_films())
		delete_film();
	else if(is_comments())
		delete_comment();
	else
		throw Not_found();
}


void Website_handler::signup()
{
	std::string email, username, password;
	int age;
	bool is_publisher = false;
	if(inputs[2] != "?")
		throw Bad_request();
	for(int i = 3; i < inputs.size() - 1; i++)
	{
		if(inputs[i] == EMAIL)
		{
			i++;
			email = inputs[i];
		}
		else if(inputs[i] == USERNAME)
		{
			i++;
			username = inputs[i];
		}
		else if(inputs[i] == PASSWORD)
		{
			i++;
			password = inputs[i];
		}
		else if(inputs[i] == AGE)
		{
			i++;
			age = std::stoi(inputs[i]);
		}
		else if(inputs[i] == PUBLISHER)
		{
			i++;
			if(inputs[i] == "true")
				is_publisher = true;
		}
		else
			throw Bad_request();
	}
	if(is_publisher)
		login_user = new Publisher(username, password, email, age, true);
	else
		login_user = new User(username, password, email, age, false);
	users->add_user(login_user);
	std::cout << login_user->get_id() << '\n';
}

void Website_handler::login()
{
	std::string username, password;
	if(inputs[2] != "?")
		throw Bad_request();
	for(int i = 3; i < inputs.size() - 1; i++)
	{
		if(inputs[i] == USERNAME)		
		{			
			i++;
			username = inputs[i];		
		}		
		else if(inputs[i] == PASSWORD)		
		{
			i++;			
			password = inputs[i];		
		}
		else
			throw Bad_request();
	}
	login_user = users->search_user(username, password);
	std::cout << login_user->get_id() << '\n';
}

void Website_handler::post_films()
{
	std::string name, summary, director;
	int length, price, year;
	if(inputs[2] != "?")
		throw Bad_request();
	if(!login_user->is_publisher())
		throw Permission_denied();
	for(int i = 3; i < inputs.size() - 1; i++)
	{
		if(inputs[i] == NAME)
		{
			i++;
			name = inputs[i];
		}
		else if(inputs[i] == YEAR)
		{
			i++;
			year = std::stoi(inputs[i]);
		}
		else if(inputs[i] == LENGTH)
		{
			i++;
			length = std::stoi(inputs[i]);
		}
		else if(inputs[i] == PRICE)
		{
			i++;
			price = std::stoi(inputs[i]);
		}
		else if(inputs[i] == SUMMARY)
		{
			i++;
			summary = inputs[i];
		}
		else if(inputs[i] == DIRECTOR)
		{
			i++;
			director = inputs[i];
		}
	else
		throw Bad_request();
	}
	Film* film = new Film(name, year, length, price, summary, director);
	films->add_film(film);
	login_user->post_film(film);
	std::cout << film->get_id() << '\n';
}

void Website_handler::money()
{
	int amount;
	if(inputs.size() == 2)
	{
		if(!login_user->is_publisher())
			throw Permission_denied();
		amount = login_user->get_money();
		cash -= amount;
	}
	else
	{
	if(inputs[2] != "?")
		throw Bad_request();
		for(int i = 3; i < inputs.size() - 1; i++)
		{
			if(inputs[i] == AMOUNT)
			{
				i++;
				amount = std::stoi(inputs[i]);
			}
		else
			throw Bad_request();
		}
		login_user->charge_money(amount);
	}
}

void Website_handler::buy()
{
	int film_id;
	if(inputs[2] != "?")
		throw Bad_request();
	for(int i = 3; i < inputs.size() - 1; i++)
	{
		if(inputs[i] == FILM_ID)
		{
			i++;
			film_id = std::stoi(inputs[i]);
		}
		else
			throw Bad_request();
	}
	Film* film = films->search_film_by_id(film_id);
	int price = film->get_price();
	cash += price;
	login_user->buy(film);
	Publisher* publisher = film->get_publisher();
	price = film->calculate_price();
	publisher->add_money(price);
	send_notif_buy_film(login_user, publisher, film);
}

void Website_handler::rate()
{
	float score;
	int film_id;
	if(inputs[2] != "?")
		throw Bad_request();
	for(int i = 3; i < inputs.size() - 1; i++)
	{
		if(inputs[i] == SCORE)
		{
			i++;
			score = std::stof(inputs[i]);
		}
		else if(inputs[i] == FILM_ID)
		{
			i++;
			film_id = std::stoi(inputs[i]);
		}
		else
			throw Bad_request();
	}
	Film* film = login_user->search_film(film_id);
	login_user->post_rate(film, score);
	send_notif_rate_film(login_user, film->get_publisher(), film);
}

void Website_handler::followers()
{
	int user_id;
	if(inputs[2] != "?")
		throw Bad_request();
	for(int i = 3; i < inputs.size() - 1; i++)
	{
		if(inputs[i] == USER_ID)
		{
			i++;
			user_id = std::stoi(inputs[i]);
		}
		else
			throw Bad_request();
	}
	User* publisher = users->search_publisher(user_id);
	publisher->add_follower(login_user);
	send_notif_to_following(login_user, publisher);
}

void Website_handler::comments()
{
	int film_id;
	std::string content;
	if(inputs[2] != "?")
		throw Bad_request();
	for(int i = 3; i < inputs.size() - 1; i++)
	{
		if(inputs[i] == FILM_ID)
		{
			i++;
			film_id = std::stoi(inputs[i]);
		}
		else if(inputs[i] == CONTENT)
		{
			i++;
			content = inputs[i];
		}
		else
			throw Bad_request();
	}
	Film* film = login_user->search_film(film_id);
	Comment* comment = new Comment(content, login_user);
	film->add_comment(comment);
	std::cout << comment->get_id() << '\n';
	send_notif_add_comment(login_user, film->get_publisher(), film);
}

void Website_handler::replies()
{
	if(inputs[2] != "?")
		throw Bad_request();
	if(!login_user->is_publisher())
		throw Permission_denied();
	int film_id, comment_id;
	std::string content;
	for(int i = 3; i < inputs.size() - 1; i++)
	{
		if(inputs[i] == FILM_ID)
		{
			i++;
			film_id = std::stoi(inputs[i]);
		}
		else if(inputs[i] == COMMENT_ID)
		{
			i++;
			comment_id = std::stoi(inputs[i]);
		}
		else if(inputs[i] == CONTENT)
		{
			i++;
			content = inputs[i];
		}
		else
			throw Bad_request();
	}
	Film* film = login_user->search_published_film(film_id);
	Comment* comment = film->search_comment(comment_id);
	comment->add_reply(content);
	std::cout << comment->get_id() << '\n';
	std::cout << comment->get_owner()->get_id() << '\n';
 	send_notif_reply_comment(comment->get_owner(), login_user);
}

void Website_handler::send_notif_buy_film(User* user, Publisher* publisher, Film* film)
{
	std::string message;
	message = "User " + user->get_name();
	message += " with id " + std::to_string(user->get_id());
	message += " buy your film " + film->get_name();
	message += " with id " + std::to_string(film->get_id());
	message += ".";
	publisher->add_unread_message(message);
}

void Website_handler::send_notif_rate_film(User* user, Publisher* publisher, Film* film)
{
	std::string message;
	message = "User " + user->get_name();
	message += " with id " + std::to_string(user->get_id());
	message += " rate your film " + film->get_name();
	message += " with id " + std::to_string(film->get_id());
	message += ".";
	publisher->add_unread_message(message);
}

void Website_handler::send_notif_to_following(User* user, User* publisher)
{
	std::string message;
	message = "User " + user->get_name();
	message += " with id " + std::to_string(user->get_id());
	message += " follow you.";
	publisher->add_unread_message(message);
}

void Website_handler::send_notif_add_comment(User* user, Publisher* publisher, Film* film)
{
	std::string message;
	message = "User " + user->get_name();
	message += " with id " + std::to_string(user->get_id());
	message += " comment on your film " + film->get_name();
	message += " with id " + std::to_string(film->get_id());
	message += ".";
	publisher->add_unread_message(message);
}

void Website_handler::send_notif_reply_comment(User* owner, User* publisher)
{
	std::string message;
	message = "Publisher " + publisher->get_name();
	message += " with id " + std::to_string(publisher->get_id());
	message += " reply to your comment.";
	owner->add_unread_message(message);
}




void Website_handler::delete_film()
{
	if(inputs[2] != "?")
		throw Bad_request();
	int film_id;
	for(int i = 3; i < inputs.size() - 1; i++)
	{
		if(inputs[i] == FILM_ID)
		{
			i++;
			film_id = std::stoi(inputs[i]);
		}
		else
			throw Bad_request();
	}
	Film* film = films->search_film_by_id(film_id);
	if(film->get_publisher() != login_user)
		throw Permission_denied();
	films->delete_film(film_id);
	login_user->delete_film(film_id);
}

void Website_handler::delete_comment()
{
	if(inputs[2] != "?")
		throw Bad_request();
	int comment_id, film_id;
	for(int i = 3; i < inputs.size() - 1; i++)
	{
		if(inputs[i] == COMMENT_ID)
		{
			i++;
			comment_id = std::stoi(inputs[i]);
		}
		else if(inputs[i] == FILM_ID)
		{
			i++;
			film_id = std::stoi(inputs[i]);
		}
		else
			throw Bad_request();
	}
	Film* film = films->search_film_by_id(film_id);
	film->delete_comment(comment_id);
}




void Website_handler::put_film()
{
	if(inputs[2] != "?")
		throw Bad_request();
	int film_id;
	std::string name = "", year = "", summary = "", director = "", length = "", price = "";
	for(int i = 3; i < inputs.size() - 1; i++)
	{
		if(inputs[i] == FILM_ID)
		{
			i++;
			film_id = std::stoi(inputs[i]);
		}
		else if(inputs[i] == NAME)
		{
			i++;
			name = inputs[i];
		}
		else if(inputs[i] == YEAR)
		{
			i++;
			year = inputs[i];
		}
		else if(inputs[i] == LENGTH)
		{
			i++;
			length = inputs[i];
		}
		else if(inputs[i] == PRICE)
		{
			i++;
			price = inputs[i];
		}
		else if(inputs[i] == SUMMARY)
		{
			i++;
			summary = inputs[i];
		}
		else if(inputs[i] == DIRECTOR)
		{
			i++;
			director = inputs[i];
		}
		else
			throw Bad_request();
	}
	Film* film = films->search_film_by_id(film_id);
	if(film->get_publisher() != login_user)
		throw Permission_denied();
	film->edit(name, year, length, price, summary, director);
}





void Website_handler::show_followers()
{
	if(inputs.size() > 2)
		throw Bad_request();
	std::cout << "List of Followers" << '\n';
	std::cout << "#. User Id | User Username | User Email" << '\n';
	std::vector<User*> followers = login_user->get_followers();
	for(int i = 0; i < followers.size(); i++)
	{
		for(int j = 0; j < i; j++)
		{
			if(followers[j]->get_id() > followers[i]->get_id())
				std::swap(followers[i], followers[j]);
		}
	}
	for(int i = 0; i < followers.size(); i++)
	{
		std::cout << i + 1 << ". ";
		std::cout << followers[i]->get_id() << " | ";
		std::cout << followers[i]->get_name() << " | ";
		std::cout << followers[i]->get_email() << '\n';
	}
}

void Website_handler::show_notifications()
{
	std::vector<std::string> messages = login_user->get_and_read_unread_messages();
	print_notifications(messages, messages.size());
}

void Website_handler::show_notifications_read()
{
	if(inputs[3] != "?")
		throw Bad_request();
	int limit;
	for(int i = 4; i < inputs.size() - 1; i++)
	{
		if(inputs[i] == LIMIT)
		{
			i++;
			limit = std::stoi(inputs[i]);
		}
		else
			throw Bad_request();
	}
	std::vector<std::string> messages = login_user->get_read_messages();
	if(limit > messages.size())
		throw Bad_request();
	print_notifications(messages, limit);
}

void Website_handler::print_notifications(std::vector<std::string> messages, int limit)
{
	int min = messages.size() - limit;
	std::cout << "#. Notification Message" << '\n';
	for(int i = messages.size() - 1; i >= min; i--)
	{
		std::cout << messages.size() - i << ". ";
		std::cout << messages[i] << '\n';
	}
}

void Website_handler::show_films()
{
	if(inputs[2] != "?")
		throw Bad_request();
	std::string name = "", price = "", min_year = "", max_year = "", director = "", min_rate = "";
	for(int i = 3; i < inputs.size() - 1; i++)
	{
		if(inputs[i] == NAME)
		{
			i++;
			name = inputs[i];
		}
		else if(inputs[i] == PRICE)
		{
			i++;
			price = inputs[i];
		}
		else if(inputs[i] == MIN_YEAR)
		{
			i++;
			min_year = inputs[i];
		}
		else if(inputs[i] == MAX_YEAR)
		{
			i++;
			max_year = inputs[i];
		}
		else if(inputs[i] == DIRECTOR)
		{
			i++;
			director = inputs[i];
		}
		else if(inputs[i] == MIN_RATE)
		{
			i++;
			min_rate = inputs[i];
		}
		else 
			throw Bad_request();
	}
	std::vector<Film*> _films;
	if(is_purchased())
		_films = login_user->get_purchased(name, price, min_year, max_year, director);
	else if(is_published())
	{
		if(login_user->is_publisher())
			_films = login_user->get_published_films(name, price, min_year, max_year, director, min_rate);
		else 
			throw Permission_denied();
	}
	else if(is_films())
		_films = films->get_films(name, price, min_year, max_year, director, min_rate);
	sort_by_id(_films);
	print_films(_films);
}





void Website_handler::sort_by_id(std::vector<Film*>& _films)
{
	for(int i = 0; i < _films.size(); i++)
		for(int j = 0; j < i; j++)
			if(_films[j]->get_id() > _films[i]->get_id())
				std::swap(_films[i], _films[j]);
}

void Website_handler::print_films(std::vector<Film*> _films)
{
	std::cout << "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director" << '\n';
	for(int i = 0; i < _films.size(); i++)
	{
		std::cout << i + 1 << ". ";
		std::cout << _films[i]->get_id() << " | ";
		std::cout << _films[i]->get_name() << " | ";
		std::cout << _films[i]->get_length() << " | ";
		std::cout << _films[i]->get_price() << " | ";
		std::cout << std::setprecision(PRECISION) << _films[i]->get_rate() << " | ";
		std::cout << _films[i]->get_year() << " | ";
		std::cout << _films[i]->get_director() << '\n';
	}
}

void Website_handler::show_details_of_film()
{
	if(inputs[2] != "?")
		throw Bad_request();
	int film_id;
	for(int i = 3; i < inputs.size() - 1; i++)
	{
		if(inputs[i] == FILM_ID)
		{
			i++;
			film_id = std::stoi(inputs[i]);
		}
		else
			throw Bad_request();
	}
	Film* film = films->search_film_by_id(film_id);
	print_details_of_film(film);
	std::vector<Comment*> comments = film->get_comments();
	print_comments(comments);
}

void Website_handler::print_details_of_film(Film* film)
{
	std::cout << "Details of Film " << film->get_name() << '\n';
	std::cout << "Id = " << film->get_id() << '\n';
	std::cout << "Director = " << film->get_director() << '\n';
	std::cout << "Length = " << film->get_length() << '\n';
	std::cout << "Year = " << film->get_id() << '\n';
	std::cout << "Summary = " << film->get_summary() << '\n';
	std::cout << "Rate = " << std::setprecision(PRECISION) << film->get_rate() << '\n';
	std::cout << "Price = " << film->get_price() << '\n';
	std::cout << '\n';
}

void Website_handler::print_comments(std::vector<Comment*> comments)
{
	std::cout << "Comments" << '\n';
	for(int i = 0; i < comments.size(); i++)
	{
		std::cout << comments[i]->get_id() << ". " << comments[i]->get_content() << '\n';
		std::vector<std::string> replies = comments[i]->get_replies();
		for(int j = 0; j < replies.size(); j++)
		{
			std::cout << comments[i]->get_id() << "." << j + 1 << ". ";
			std::cout << replies[j] << '\n';
		}
	}
	std::cout << '\n';
}

void Website_handler::recommend_films()
{
	std::vector<Film*> all_films = films->get_all_films();
	sort_by_rate(all_films);
	std::vector<Film*> recommendation_films;
	for(int i = 0; i < all_films.size(); i++)
	{
		if(login_user->is_purchased(all_films[i]))
			continue;
		recommendation_films.push_back(all_films[i]);
	}
	print_recommendation_films(recommendation_films);
}

void Website_handler::print_recommendation_films(std::vector<Film*> recommendation_films)
{
	std::cout << "Recommendation Film\n";
	std::cout << "#. Film Id | Film Name | Film Length | Film Director\n";
	for(int i = 0; i < recommendation_films.size(); i++)
	{
		if(i > 3)
			return;
		std::cout << i + 1 << ". ";
		std::cout << recommendation_films[i]->get_id() << " | ";
		std::cout << recommendation_films[i]->get_name() << " | ";
		std::cout << recommendation_films[i]->get_length() << " | ";
		std::cout << recommendation_films[i]->get_director() << '\n';
	}
}

void Website_handler::sort_by_rate(std::vector<Film*>& _films)
{
	for(int i = 0; i < _films.size(); i++)
		for(int j = 0; j < i; j++)
		{
			if(_films[j]->get_rate() < _films[i]->get_rate())
				std::swap(_films[i], _films[j]);
			else if(_films[j]->get_rate() == _films[i]->get_rate())
				if(_films[j]->get_id() > _films[i]->get_id())
					std::swap(_films[i], _films[j]);
		}
}



