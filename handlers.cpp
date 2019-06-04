#include "handlers.hpp"

using namespace std;

Response *PublisherHomeHandler::callback(Request *req) {
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<head>";
    body += "<style>";
    body += "ul {";
    body += "list-style-type: none;";
    body += "margin: 0;";
    body += "padding: 0;";
    body += "overflow: hidden;";
    body += "background-color: #333;";
    body += "}";
    
    body += "li {";
    body += "float: left;";
    body += "}";
    
    body += "li a {";
    body += "display: block;";
    body += "color: white;";
    body += "text-align: center;";
    body += "padding: 14px 16px;";
    body += "text-decoration: none;";
    body += "}";
    
    body += "li a:hover:not(.active) {";
    body += "background-color: #111;";
    body += "}";
    
    body += ".active {";
    body += "background-color: #4CAF50;";
    body += "}";

    
    body += "table {";
    body += "border-collapse: collapse;";
    body += "width: 100%;";
    body += "}";
    
    body += "th, td {";
    body += "padding: 8px;";
    body += "text-align: left;";
    body += "border-bottom: 1px solid #ddd;";
    body += "}";
    
    body += "tr:hover {background-color:#f5f5f5;}";
    body += "</style>";
    body += "</head>";
    body += "<body style=\"text-align: center;\">";
    
    body += "<ul>";
    body += "<li><a class=\"active\">Home</a></li>";
    body += "<li><a href=\"/post_film\">Post Film</a></li>";
    body += "<li><a href=\"/customer\">Available Films</a></li>";
    body += "<li><a href=\"/profile\">Profile</a></li>";
    body += "<li><a href=\"/detail\">Details Of Film</a></li>";
    body += "<li style=\"float:right\"><a href=\"/logout\">Exit</a></li>";
    body += "</ul>";
    
    string director = req->getBodyParam("director");

    body += "<h2>Published Films</h2>";
    body += "<form action=\"/publisher\" method=\"post\">";
    body += "Name of Director:";
    body += "<input type=\"text\" name=\"director\">";
    body += "<button type=\"submit\">Show</button><br>";
    body += "</form>";
    
    body += "<table>";
    body += "<tr>";
    body += "<th>Name</th>";
    body += "<th>Length</th>";
    body += "<th>Price</th>";
    body += "<th>Rate</th>";
    body += "<th>Year</th>";
    body += "<th>Director</th>";
    body += "</tr>";
    
    web->show_films(director, body);
    body += "</table>";
    body += "</body>";
    body += "</html>";
    res->setBody(body);
    return res;
}

Response *CustomerHomeHandler::callback(Request *req) {
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<head>";
    body += "<style>";
    body += "ul {";
    body += "list-style-type: none;";
    body += "margin: 0;";
    body += "padding: 0;";
    body += "overflow: hidden;";
    body += "background-color: #333;";
    body += "}";
    
    body += "li {";
    body += "float: left;";
    body += "}";
    
    body += "li a {";
    body += "display: block;";
    body += "color: white;";
    body += "text-align: center;";
    body += "padding: 14px 16px;";
    body += "text-decoration: none;";
    body += "}";
    
    body += "li a:hover:not(.active) {";
    body += "background-color: #111;";
    body += "}";
    
    body += ".active {";
    body += "background-color: #4CAF50;";
    body += "}";
    
    
    body += "table {";
    body += "border-collapse: collapse;";
    body += "width: 100%;";
    body += "}";
    
    body += "th, td {";
    body += "padding: 8px;";
    body += "text-align: left;";
    body += "border-bottom: 1px solid #ddd;";
    body += "}";
    
    body += "tr:hover {background-color:#f5f5f5;}";
    body += "</style>";
    body += "</head>";
    body += "<body style=\"text-align: center;\">";
    
    body += "<ul>";
    
    if(web->is_publisher())
    {
        body += "<li><a href=\"/publisher\">Home</a></li>";
        body += "<li><a href=\"/post_film\">Post Film</a></li>";
        body += "<li><a class=\"active\">Available Films</a></li>";
    }
    else
        body += "<li><a class=\"active\">Home</a></li>";
    
    body += "<li><a href=\"/profile\">Profile</a></li>";
    body += "<li><a href=\"/detail\">Details Of Film</a></li>";
    body += "<li style=\"float:right\"><a href=\"/logout\">Exit</a></li>";
    body += "</ul>";
    
    
    body += "<h2>Available Films</h2>";
    
    body += "<table>";
    body += "<tr>";
    body += "<th>Name</th>";
    body += "<th>Length</th>";
    body += "<th>Price</th>";
    body += "<th>Rate</th>";
    body += "<th>Year</th>";
    body += "<th>Director</th>";
    body += "</tr>";
    
    web->show_available_films(body);
    body += "</table>";
    body += "</body>";
    body += "</html>";
    res->setBody(body);
    return res;
}

Response *LoginHandler::callback(Request *req)
{
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    if (username == "root")
        throw Server::Exception("Remote root access has been disabled.");
    Response *res;
    web->login(username, password);
    if(web->is_publisher())
        res = Response::redirect("/publisher");
    else
        res = Response::redirect("/customer");
    res->setSessionId(to_string(web->get_id_of_login_user()));
    return res;
}

Response *SignupHandler::callback(Request *req)
{
    bool is_publisher = false;
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    string repass = req->getBodyParam("repassword");
    int age = stoi(req->getBodyParam("age"));
    string email = req->getBodyParam("email");
    if(req->getBodyParam("is_publisher") == "1")
        is_publisher = true;
    if(password != repass)
        throw Server::Exception("Please enter your password again.");
    web->signup(username, password, age, email, is_publisher);
    Response *res;
    if(web->is_publisher())
        res = Response::redirect("/publisher");
    else
        res = Response::redirect("/customer");
    res->setSessionId(to_string(web->get_id_of_login_user()));
    return res;
}

Response *PostFilmHandler::callback(Request *req)
{
    string name = req->getBodyParam("name");
    int price = stoi(req->getBodyParam("price"));
    int year = stoi(req->getBodyParam("year"));
    int length = stoi(req->getBodyParam("length"));
    string director = req->getBodyParam("director");
    string summary = req->getBodyParam("summary");
    web->post_films(name, price, year, length, director, summary);
    Response *res = Response::redirect("/publisher");
    return res;
}

Response *DeleteFilmHandler::callback(Request *req)
{
    int film_id = stoi(req->getQueryParam("film_id"));
    web->delete_film(film_id);
    Response *res = Response::redirect("/publisher");
    return res;
}


Response *ProfileHandler::callback(Request *req) {
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<head>";
    body += "<style>";
    body += "ul {";
    body += "list-style-type: none;";
    body += "margin: 0;";
    body += "padding: 0;";
    body += "overflow: hidden;";
    body += "background-color: #333;";
    body += "}";
    
    body += "li {";
    body += "float: left;";
    body += "}";
    
    body += "li a {";
    body += "display: block;";
    body += "color: white;";
    body += "text-align: center;";
    body += "padding: 14px 16px;";
    body += "text-decoration: none;";
    body += "}";
    
    body += "li a:hover:not(.active) {";
    body += "background-color: #111;";
    body += "}";
    
    body += ".active {";
    body += "background-color: #4CAF50;";
    body += "}";
    
    
    body += "table {";
    body += "border-collapse: collapse;";
    body += "width: 100%;";
    body += "}";
    
    body += "th, td {";
    body += "padding: 8px;";
    body += "text-align: left;";
    body += "border-bottom: 1px solid #ddd;";
    body += "}";
    
    body += "tr:hover {background-color:#f5f5f5;}";
    body += "</style>";
    body += "</head>";
    body += "<body style=\"text-align: center;\">";
    
    body += "<ul>";
    int amount;
    if(req->getBodyParam("money") == "")
        amount = 0;
    else
        amount = stoi(req->getBodyParam("money"));
    if(web->is_publisher())
    {
        body += "<li><a href=\"/publisher\">Home</a></li>";
        body += "<li><a href=\"/post_film\">Post Film</a></li>";
        body += "<li><a href=\"/customer\">Available Films</a></li>";
    }
    else
        body += "<li><a href=\"/customer\">Home</a></li>";
    body += "<li><a class=\"active\">Profile</a></li>";
    body += "<li><a href=\"/detail\">Details Of Film</a></li>";
    body += "<li style=\"float:right\"><a href=\"/logout\">Exit</a></li>";
    body += "</ul>";
    body += "<h2>Purchased Films</h2>";
    body += "<form action=\"/profile\" method=\"post\">";
    body += "Amount of money:";
    body += "<input type=\"number\" name=\"money\" value=\"0\" min=\"0\">";
    body += "<button type=\"submit\">Charge</button><br>";
    body += "</form>";
    
    body += "<table>";
    body += "<tr>";
    body += "<th>Name</th>";
    body += "<th>Length</th>";
    body += "<th>Price</th>";
    body += "<th>Rate</th>";
    body += "<th>Year</th>";
    body += "<th>Director</th>";
    body += "</tr>";
    web->money(amount);
    web->show_purchased_films(body);
    body += "</table>";
    body += "</body>";
    body += "</html>";
    res->setBody(body);
    return res;
}


Response *LogoutHandler::callback(Request *req)
{
    web->logout();
    Response *res = Response::redirect("/");
    return res;
}

Response *DetailFilmHandler::callback(Request *req)
{
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string body;

    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<head>";
    body += "<style>";
    body += "ul {";
        body += "list-style-type: none;";
    body += "margin: 0;";
    body += "padding: 0;";
    body += "overflow: hidden;";
        body += "background-color: #333;";
    body += "}";

    body += "li {";
        body += "float: left;";
    body += "}";

    body += "li a {";
    body += "display: block;";
    body += "color: white;";
        body += "text-align: center;";
    body += "padding: 14px 16px;";
        body += "text-decoration: none;";
    body += "}";

    body += "li a:hover:not(.active) {";
        body += "background-color: #111;";
    body += "}";

    body += ".active {";
        body += "background-color: #4CAF50;";
    body += "}";

    body += "table {";
        body += "border-collapse: collapse;";
    body += "width: 100%;";
    body += "}";

    body += "th, td {";
    body += "padding: 8px;";
        body += "text-align: left;";
        body += "border-bottom: 1px solid #ddd;";
    body += "}";

    body += "tr:hover {background-color:#f5f5f5;}";
    body += "</style>";
    body += "</head>";
    body += "<body style=\"text-align: center;\">";

    body += "<ul>";
    if(web->is_publisher())
    {
        body += "<li><a href=\"/publisher\">Home</a></li>";
        body += "<li><a href=\"/post_film\">Post Film</a></li>";
        body += "<li><a href=\"/customer\">Available Films</a></li>";
    }
    else
        body += "<li><a href=\"/customer\">Home</a></li>";
    body += "<li><a href=\"/profile\">Profile</a></li>";
    body += "<li><a class=\"active\">Details Of Film</a></li>";
    body += "<li style=\"float:right\"><a href=\"/logout\">Exit</a></li>";
    body += "</ul>";
    body += "<br>";
    int film_id;
    if(req->getBodyParam("film_id") == "")
    {
        if(req->getQueryParam("film_id") == "")
            film_id = 0;
        else
            film_id = stoi(req->getQueryParam("film_id"));
    }
    else
        film_id = stoi(req->getBodyParam("film_id"));
    body += "<form action=\"/detail\" method=\"post\">";
    body += "Search Film by id:";
    body += "<input type=\"number\" name=\"film_id\" min=\"1\">";
    body += "<button type=\"submit\">Show</button><br>";
    body += "</form>";
    body += "<h2>Details of film " + req->getBodyParam("film_id") + "</h2>";
    body += "<table>";
    body += "<tr>";
    body += "<th>Name</th>";
    body += "<th>Length</th>";
    body += "<th>Price</th>";
    body += "<th>Rate</th>";
    body += "<th>Year</th>";
    body += "<th>Director</th>";
    body += "<th>Summary</th>";
    body += "</tr>";
    web->show_details_of_film(film_id, body);    
    body += "</table>";
    body += "<br>";
    web->show_comments(film_id, body);
    body += "<br><br>";
    body += "<h2>Recommandation Films</h2>";
    body += "<table>";
    body += "<tr>";
    body += "<th>Name</th>";
    body += "<th>Length</th>";
    body += "<th>Director</th>";
    body += "</tr>";
    web->recommend_films(film_id, body);
    body += "</table>";
    body += "</body>";
    body += "</html>";
    res->setBody(body);
    return res;
}

Response *BuyFilmHandler::callback(Request *req)
{
    int film_id = stoi(req->getQueryParam("film_id"));
    web->buy(film_id);
    std::string direct = "/detail?film_id=" + to_string(film_id);
    Response *res = Response::redirect(direct);
    return res;
}

Response *RateFilmHandler::callback(Request *req)
{
    int film_id = stoi(req->getQueryParam("film_id"));
    float score = stof(req->getBodyParam("score"));
    web->rate(film_id, score);
    std::string direct = "/detail?film_id=" + to_string(film_id);
    Response *res = Response::redirect(direct);
    return res;
}

Response *CommentFilmHandler::callback(Request *req)
{
    int film_id = stoi(req->getQueryParam("film_id"));
    string comment = req->getBodyParam("comment");
    if(comment != "")
        web->comments(film_id, comment);
    std::string direct = "/detail?film_id=" + to_string(film_id);
    Response *res = Response::redirect(direct);
    return res;
}
