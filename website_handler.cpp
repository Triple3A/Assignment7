#include "website_handler.hpp"

Website_handler::Website_handler()
{
	users = new Repository_of_users();
}

std::string Website_handler::get_input()
{
	std::string input;
	getline(std::cin, input);
	return input;
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
bool Website_handler::is_notifications()
{
	if(inputs[1] == NOTIFICATIONS)
		return true;
	return false;
}

void Website_handler::processing_inputs()
{
	if(is_post())
	{
		post();
	}
	// else if(is_get())
	// {
	// 	get();
	// }
	// else if(is_put())
	// {
	// 	put();
	// }
	// else if(is_delete())
	// {
	// 	_delete();
	// }
	// else
	// 	throw Bad_request();
}

void Website_handler::post()
{
	if(is_signup())
		signup();
	// else if(is_login())
	// 	login();
	// else if(is_films())
	// 	films();
	// else if(is_money())
	// 	money();
	// else if(is_replies())
	// 	replies();
	// else if(is_followers())
	// 	followers();
	// else if(is_buy())
	// 	buy();
	// else if(is_rate())
	// 	rate();
	// else if(is_comments())
	// 	comments();
	// else
	// 	throw Not_found();
}

// void Website_handler::get()
// {
// 	if(is_followers())
// 		get_followers();
// 	else if(is_published())
// 		published();
// 	else if(is_films())
// 		get_films();
// 	else if(is_purchased())
// 		purchased();
// 	else if(is_notifications())
// 		notifications();
// 	// else
// 	// 	throw Not_found();
// }

// void Website_handler::put()
// {
// 	if(is_films())
// 		put_film();
// 	// else
// 	// 	throw Not_found();
// }
//
// void Website_handler::_delete()
// {
// 	if(is_films())
// 		delete_film();
// 	else if(is_comments())
// 		delete_comment();
// 	// else
// 	// 	throw Not_found();
// }


void Website_handler::signup()
{
	std::string email, username, password;
	int age;
	bool is_publisher = false;
	// if(inputs[2] != "?")
	// 	throw Bad_request();
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
		else if(inputs[i] == PUBLISHED)
		{
			i++;
			if(inputs[i] == "true")
				is_publisher = true;
		}
		// else
//	throw Bad_request();
	}
	User* user = new User(username, password, email, age, is_publisher);
	users->add_user(user);
	login_user = user;
	std::cout << user->get_id() << '\n';
	std::cout << "OK" << '\n';
}



