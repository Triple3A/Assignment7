#include "website_handler.hpp"

Website_handler::Website_handler(MyServer* _server)
    : server(_server)
{
	cash = 0;
	users = new Repository_of_users();
	films = new Repository_of_films();
    User* admin = new User(ADMIN, ADMIN, "", 0, false);
    users->add_user(admin);
	login_user = NULL;
}

Website_handler::~Website_handler()
{
	delete[] users;
	delete[] films;
}

void Website_handler::print_ok()
{
	std::cout << "OK" << '\n';
}

bool cmp(std::pair<int, int> x, std::pair <int, int> y)
{
    if (x.F == y.F) return x.S < y.S;
    return x.F > y.F;
    
}

void Website_handler::run()
{
    server->setNotFoundErrPage("../APHTTP/static/404.html");
    server->get("/login", new ShowPage("../Phase3/login.html"));
    server->post("/login", new LoginHandler(this));
    server->get("/signup", new ShowPage("../Phase3/signup.html"));
    server->post("/signup", new SignupHandler(this));
    server->get("/up", new ShowPage("../APHTTP/static/upload_form.html"));
    server->post("/up", new UploadHandler());
    server->get("/rand", new RandomNumberHandler());
    server->get("/home.png", new ShowImage("../APHTTP/static/home.png"));
    server->get("/", new ShowPage("../Phase3/home.html"));
    server->get("/colors", new ColorHandler("../APHTTP/template/colors.html"));
    server->run();
}

int Website_handler::get_id_of_login_user()
{
    return login_user->get_id();
}



void Website_handler::signup(std::string username, std::string password, int age, std::string email, bool is_publisher)
{
//    if(login_user != NULL)
//        throw Bad_request();
    User* user;
	if(is_publisher)
		user = new Publisher(username, password, email, age, true);
	else
		user = new User(username, password, email, age, false);
	users->add_user(user);
    login_user = user;
}

void Website_handler::login(std::string username, std::string password)
{
//    if(login_user != NULL)
//        throw Bad_request();
	login_user = users->search_user(username, password);
    retrun login_user->get_id();
}

void Website_handler::logout()
{
    if(inputs.size() != 2)
        throw Bad_request();
    login_user = NULL;
}

void Website_handler::post_films()
{
	std::string name, summary, director;
	int length, price, year;
	if(inputs[2] != "?")
		throw Bad_request();
	if(inputs.size() != 15)
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
    add_film_to_matrix();
}

void Website_handler::add_film_to_matrix()
{
    for(int i = 0; i < adjacency_matrix.size(); i++)
    {
        adjacency_matrix[i].push_back(0);
    }
    std::vector<int> row(adjacency_matrix.size() + 1, 0);
    adjacency_matrix.push_back(row);
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
		if(inputs.size() != 5)
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
	if(inputs.size() != 5)
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
    login_user->buy(film);
    film->purchased();
	int price = film->get_price();
	cash += price;
	Publisher* publisher = film->get_publisher();
	price = film->calculate_price();
	publisher->add_money(price);
	send_notif_buy_film(login_user, publisher, film);
    update_matrix();
}

void Website_handler::rate()
{
	float score;
	int film_id;
	if(inputs[2] != "?")
		throw Bad_request();
	if(inputs.size() != 7)
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
	if(inputs.size() != 5)
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
	if(inputs.size() != 7)
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
	send_notif_add_comment(login_user, film->get_publisher(), film);
}

void Website_handler::replies()
{
	if(inputs[2] != "?")
		throw Bad_request();
	if(inputs.size() != 9)
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
	if(inputs.size() != 5)
		throw Bad_request();
	if(!login_user->is_publisher())
		throw Permission_denied();
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
}

void Website_handler::delete_comment()
{
	if(inputs[2] != "?")
		throw Bad_request();
	if(inputs.size() != 7)
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



void Website_handler::get_money()
{
    if(inputs.size() != 2)
        throw Bad_request();
    if(login_user->get_id() == 1)
        std::cout << cash << '\n';
    else
        std::cout << login_user->get_account() << '\n';
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
	if(inputs.size() != 2)
		throw Bad_request();
	std::vector<std::string> messages = login_user->get_and_read_unread_messages();
	print_notifications(messages, messages.size());
}

void Website_handler::show_notifications_read()
{
	if(inputs[3] != "?")
		throw Bad_request();
	if(inputs.size() != 6)
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
	if(inputs.size() != 5)
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
    recommend_films(film_id);
}

void Website_handler::print_details_of_film(Film* film)
{
	std::cout << "Details of Film " << film->get_name() << '\n';
	std::cout << "Id = " << film->get_id() << '\n';
	std::cout << "Director = " << film->get_director() << '\n';
	std::cout << "Length = " << film->get_length() << '\n';
	std::cout << "Year = " << film->get_year() << '\n';
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

void Website_handler::recommend_films(int film_id)
{
    std::vector<std::pair<int, int> > all_films;
    for (int i = 0; i < adjacency_matrix[film_id - 1].size(); i++)
    {
        all_films.push_back({adjacency_matrix[film_id - 1][i], i + 1});
    }
    std::sort(all_films.begin(), all_films.end(), cmp);
	std::vector<Film*> recommendation_films;
	for(int i = 0; i < all_films.size(); i++)
	{
		if(login_user->is_purchased(films->search_film_by_id(all_films[i].S)))
			continue;
        recommendation_films.push_back(films->search_film_by_id(all_films[i].S));
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



void Website_handler::update_matrix()
{
    for(int i = 0; i < adjacency_matrix.size(); i++)
    {
        Film* film1 = films->search_film_by_id(i + 1);
        for(int j = 0; j < adjacency_matrix[i].size(); j++)
        {
            if(i == j)
            {
                adjacency_matrix[i][j] = 0;
                continue;
            }
            
            Film* film2 = films->search_film_by_id(j + 1);
            adjacency_matrix[i][j] = std::min(film1->get_num_of_purchased(), film2->get_num_of_purchased());
        }
    }
}
