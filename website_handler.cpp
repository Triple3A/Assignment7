#include "website_handler.hpp"

std::string Website_Handler::get_input()
{
	std::string input;
	getline(cin, input);
	return input;
}

void Website_Handler::seperator(std::string input)
{
	delete(inputs);
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

bool Website_Handler::is_get()
{
	if(inputs[0] == GET)
		return true;
	return false;
}
bool Website_Handler::is_put()
{
	if(inputs[0] == PUT)
		return true;
	return false;
}
bool Website_Handler::is_post()
{
	if(inputs[0] == POST)
		return true;
	return false;
}
bool Website_Handler::is_delete()
{
	if(inputs[0] == DELETE)
		return true;
	return false;
}
bool Website_Handler::is_signup()
{
	if(inputs[1] == SIGNUP)
		return true;
	return false;
}
bool Website_Handler::is_login()
{
	if(inputs[1] == LOGIN)
		return true;
	return false;
}
bool Website_Handler::is_films()
{
	if(inputs[1] == FILMS)
		return true;
	return false;
}
bool Website_Handler::is_money()
{
	if(inputs[1] == MONEY)
		return true;
	return false;
}
bool Website_Handler::is_replies()
{
	if(inputs[1] == REPLIES)
		return true;
	return false;
}
bool Website_Handler::is_followers()
{
	if(inputs[1] == FOLLOWERS)
		return true;
	return false;
}
bool Website_Handler::is_buy()
{
	if(inputs[1] == BUY)
		return true;
	return false;
}
bool Website_Handler::is_rate()
{
	if(inputs[1] == RATE)
		return true;
	return false;
}
bool Website_Handler::is_comments()
{
	if(inputs[1] == COMMENTS)
		return true;
	return false;
}
bool Website_Handler::is_published()
{
	if(inputs[1] == PUBLISHED)
		return true;
	return false;
}
bool Website_Handler::is_purchased()
{
	if(inputs[1] == PURCHASED)
		return true;
	return false;
}
bool Website_Handler::is_notifications()
{
	if(inputs[1] == NOTIFICATIONS)
		return true;
	return false;
}

void Website_Handler::processing_inputs()
{
	if(is_put())
	{
		put();
	}
	else if(is_get())
	{
		get();
	}
	else if(is_post())
	{
		post();
	}
	else if(is_delete())
	{
		_delete();
	}
	else
		throw Bad_request();
}

void Website_Handler::post()
{
	if(is_signup())
		signup();
	else if(is_login())
		login();
	else if(is_films())
		films();
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

void Website_Handler::get()
{
	if(is_followers())
		get_followers();
	else if(is_published())
		published();
	else if(is_films())
		get_films();
	else if(is_purchased())
		purchased();
	else if(is_notifications())
		notifications();
	else 
		throw Not_found();
}

void Website_Handler::put()
{
	if(is_films())
		put_film();
	else 
		throw Not_found();
}

void Website_Handler::_delete()
{
	if(is_films())
		delete_film();
	else if(is_comments())
		delete_comment();
	else 
		throw Not_found();
}