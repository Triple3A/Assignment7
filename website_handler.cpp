#include "website_handler.hpp"

Website_handler::Website_handler(MyServer* _server)
    : server(_server)
{
	cash = 0;
	users = new Repository_of_users();
	films = new Repository_of_films();
	login_user = NULL;
}

Website_handler::~Website_handler()
{
	delete[] users;
	delete[] films;
}

bool Website_handler::is_publisher()
{
    return login_user->is_publisher();
}

bool cmp(std::pair<int, int> x, std::pair <int, int> y)
{
    if (x.F == y.F) return x.S < y.S;
    return x.F > y.F;
    
}

void Website_handler::run()
{
    server->setNotFoundErrPage("static/404.html");
    server->get("/login", new ShowPage("static/logincss.html"));
    server->post("/login", new LoginHandler(this));
    server->get("/signup", new ShowPage("static/signupcss.html"));
    server->post("/signup", new SignupHandler(this));
    server->get("/post_film", new ShowPage("static/post_filmcss.html"));
    server->post("/post_film", new PostFilmHandler(this));
    server->get("/logout", new ShowPage("static/home.html"));
    server->post("/logout", new LogoutHandler(this));
    server->get("/", new ShowPage("static/home.html"));
    server->get("/customer", new CustomerHomeHandler(this));
    server->get("/publisher", new PublisherHomeHandler(this));
    server->post("/publisher", new PublisherHomeHandler(this));
    server->get("/profile", new ProfileHandler(this));
    server->post("/profile", new ProfileHandler(this));
    server->post("/delete" , new DeleteFilmHandler(this));
    server->get("/detail", new DetailFilmHandler(this));
    server->post("/detail", new DetailFilmHandler(this));
    server->post("/buy" , new BuyFilmHandler(this));
    server->post("/rate" , new RateFilmHandler(this));
    server->post("/comment" , new CommentFilmHandler(this));
    server->run();
}

int Website_handler::get_id_of_login_user()
{
    return login_user->get_id();
}



void Website_handler::signup(std::string username, std::string password, int age, std::string email, bool is_publisher)
{
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
	login_user = users->search_user(username, password);
}

void Website_handler::logout()
{
    login_user = NULL;
}

void Website_handler::post_films(std::string name, int price, int year, int length, std::string director, std::string summary)
{
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

void Website_handler::money(int amount)
{
    login_user->charge_money(amount);
}

void Website_handler::buy(int film_id)
{
    Film* film = films->search_film_by_id(film_id);
    login_user->buy(film);
    film->purchased();
    int price = film->get_price();
    cash += price;
    Publisher* publisher = film->get_publisher();
    price = film->calculate_price();
    publisher->add_money(price);
    update_matrix();
}

void Website_handler::rate(int film_id, float score)
{
    Film* film = login_user->search_film(film_id);
    login_user->post_rate(film, score);
}


void Website_handler::comments(int film_id, std::string content)
{
    Film* film = login_user->search_film(film_id);
    Comment* comment = new Comment(content, login_user);
    film->add_comment(comment);
}


void Website_handler::delete_film(int film_id)
{
    login_user->delete_film(film_id);
    films->delete_film(film_id);
}

void Website_handler::show_films(std::string director, std::string& body)
{
    std::vector<Film*> _films;
    _films = login_user->get_published_films(director);
    sort_by_id(_films);
    print_films(_films, body);
}

void Website_handler::show_available_films(std::string& body)
{
    std::vector<Film*> _films;
    _films = films->user_can_buy(login_user);
    sort_by_id(_films);
    print_purchased_films(_films, body);
}

void Website_handler::show_purchased_films(std::string& body)
{
    std::vector<Film*> _films;
    _films = login_user->get_purchased();
    sort_by_id(_films);
    print_purchased_films(_films, body);
}


void Website_handler::sort_by_id(std::vector<Film*>& _films)
{
    for(int i = 0; i < _films.size(); i++)
        for(int j = 0; j < i; j++)
            if(_films[j]->get_id() > _films[i]->get_id())
                std::swap(_films[i], _films[j]);
}

void Website_handler::print_purchased_films(std::vector<Film*> _films, std::string& body)
{
    for(int i = 0; i < _films.size(); i++)
    {
        body += "<tr>";
        body += "<td>" + _films[i]->get_name() + "</td>";
        body += "<td>" + std::to_string(_films[i]->get_length()) + "</td>";
        body += "<td>" + std::to_string(_films[i]->get_price()) + "</td>";
        body += "<td>" + std::to_string(_films[i]->get_rate()) + "</td>";
        body += "<td>" + std::to_string(_films[i]->get_year()) + "</td>";
        body += "<td>" + _films[i]->get_director() + "</td>";
        body += "</tr>";
    }
}

void Website_handler::print_films(std::vector<Film*> _films, std::string& body)
{
    for(int i = 0; i < _films.size(); i++)
    {
        std::string film_id = std::to_string(_films[i]->get_id());
        body += "<form action = \"/delete?film_id=" + film_id + "\" method = \"post\">";
        body += "<tr>";
        body += "<td>" + _films[i]->get_name() + "</td>";
        body += "<td>" + std::to_string(_films[i]->get_length()) + "</td>";
        body += "<td>" + std::to_string(_films[i]->get_price()) + "</td>";
        body += "<td>" + std::to_string(_films[i]->get_rate()) + "</td>";
        body += "<td>" + std::to_string(_films[i]->get_year()) + "</td>";
        body += "<td>" + _films[i]->get_director() + "</td>";
        body += "<td><button type=\"submit\">Delete Film</button></td>";
        body += "</tr>";
        body += "</form>";
    }
}

void Website_handler::show_details_of_film(int film_id, std::string& body)
{
    if(film_id == 0)
        return;
    Film* film = films->search_film_by_id(film_id);
    print_details_of_film(film, body);
}

void Website_handler::show_comments(int film_id, std::string& body)
{
    if(film_id == 0)
        return;
    Film* film = films->search_film_by_id(film_id);
    std::vector<Comment*> comments = film->get_comments();
    print_comments(comments, body);
}

void Website_handler::print_details_of_film(Film* film, std::string& body)
{
    body += "<tr>";
    body += "<td>" + film->get_name() + "</td>";
    body += "<td>" + std::to_string(film->get_length()) + "</td>";
    body += "<td>" + std::to_string(film->get_price()) + "</td>";
    body += "<td>" + std::to_string(film->get_rate()) + "</td>";
    body += "<td>" + std::to_string(film->get_year()) + "</td>";
    body += "<td>" + film->get_director() + "</td>";
    body += "<td>" + film->get_summary() + "</td>";
    std::string film_id = std::to_string(film->get_id());
    if(login_user->get_account() >= film->get_price() && !login_user->is_purchased(film))
    {
        body += "<form action=\"/buy?film_id=" + film_id + "\" method=\"post\">";
        body += "<button type=\"submit\">Buy</button><br>";
        body += "</form>";
    }
    if(login_user->is_purchased(film))
    {
        body += "<form action=\"/comment?film_id=" + film_id + "\" method=\"post\">";
        body += "Comment:";
        body += "<input type=\"text\" name=\"comment\">";
        body += "<button type=\"submit\">Add</button><br>";
        body += "</form>";
        body += "<form action=\"/rate?film_id=" + film_id + "\" method=\"post\">";
        body += "Rate this film:";
        body += "<input type=\"number\" name=\"score\" min=\"1\" max=\"10\" step=\"0.01\">";
        body += "<button type=\"submit\">Rate</button><br>";
        body += "</form>";
    }
    body += "</tr>";
}

void Website_handler::print_comments(std::vector<Comment*> comments, std::string& body)
{
    body += "<h3 style=\"text-align: left;\">Comments:</h3>";
    for(int i = 0; i < comments.size(); i++)
    {
        body += "<p style=\"text-align: left;\">    " + std::to_string(i + 1) + ". " + comments[i]->get_content() + "</p>";
    }
    std::cout << '\n';
}

void Website_handler::recommend_films(int film_id, std::string& body)
{
    if(film_id == 0)
        return;
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
        if(all_films[i].S == film_id)
            continue;
        recommendation_films.push_back(films->search_film_by_id(all_films[i].S));
    }
    print_recommendation_films(recommendation_films, body);
}

void Website_handler::print_recommendation_films(std::vector<Film*> recommendation_films, std::string& body)
{
    for(int i = 0; i < recommendation_films.size(); i++)
    {
        if(i > 3)
            return;
        std::string film_id = std::to_string(recommendation_films[i]->get_id());
        body += "<tr>";
        body += "<td><a href=\"/detail?film_id=" + film_id + "\">" + recommendation_films[i]->get_name() + "</a></td>";
        body += "<td>" + std::to_string(recommendation_films[i]->get_length()) + "</td>";
        body += "<td>" + recommendation_films[i]->get_director() + "</td>";
        body += "</tr>";
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
